#include "configuration_write_visitor.h"

ConfigurationWriteVisitor::ConfigurationWriteVisitor():data(0){}

void ConfigurationWriteVisitor::setData(unsigned int d)
{
    data = d;
}

/**
 * @brief Visiting the Configuration Sapce to write inside a specific Register
 * 
 * @param configuration -> A pointer to the Configuration Space to visit 
 * @return unsigned int -> A value to tell us whether the Configuration Write request is done successfully (return 1), otherwise (return 0)
 */
unsigned int ConfigurationWriteVisitor::visitConfigurationSpace(ConfigurationSpace * configuration)
{
    /* 
       Check if the index is out of bounds, or 
       The Register is a BAR (Base Address Register) with read only bits (not used by the endpoint to request for memory or IO space)
       so the root complex can't write to it, so we will return 0
    */
    if (registerNumber < 0 || registerNumber >= configuration->getSize() || registerNumber == 11 || registerNumber == 12)
    {
        configuration->setReceivedMasterAbortBit(); // Setting the Received Master Abort Bit in the Status Register as we received an Unsupported Request (UR)
        return 0; // Cpl with UR
    }

    // Traverse the linked list to find the Command Register
    Register * current = configuration->getHead();
    Register * command = configuration->getHead();
    command = command->getRegisterNext()->getRegisterNext();

    
    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getRegisterNext();
    }

    // The Register is either Read Only, or Hardware Initialized
    if (current->getRegisterType() == 0 || current->getRegisterType() == 1)
    {
        configuration->setReceivedMasterAbortBit(); // Setting the Received Master Abort Bit in the Status Register as we received an Unsupported Request (UR)
        return 0; // Cpl with UR
    }

    // In case the sent Register Number belongs to a Read Write Register, then you can modify its value
    switch (registerNumber)
    {
    case 2: // Command Register
        current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask()))) ;
        break;

    case 3: // Status Register
        // You can't write to the Signaled System Error bit and the SERR# Enable bit in the Command Register is = 0
        if((data & 0x00004000) && !(command->getRegisterValue() & 0x00000100))
            data &= 0xFFFFBFFF;

        // You can't write to the Master Data Parity Error bit and the Parity Error Response bit in the Command Register is = 0
        if((data & 0x00000100) && !(command->getRegisterValue() & 0x00000040))
            data &= 0xFFFFFEFF;

        // Then we can write to the Status Register
        current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
        break;

    case 7: // BAR0
        current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
        break;

    case 8: // BAR1
        current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
        break;

    case 9: // BAR2
        current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
        break;

    case 10: // BAR3
        current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
        break;

    case 15: // Expansion ROM Base Address Register
        if(configuration->isMemorySpaceEnabled()) // if the Memory space is enabled, so you can write in the bits (0, 11->31)
        {
            current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
        }
        else // if the Memory space is disabled, so you can't write in this register
        {
            configuration->setReceivedMasterAbortBit(); // Setting the Received Master Abort Bit in the Status Register as we received an Unsupported Request (UR)
            return 0; // Cpl with UR
        }
        break;
    }

    return 1; // The Write is done Successfully
}

/* To be used after making the PCIE Capability structure */
/*unsigned int ConfigurationWriteVisitor::visitPcieCapabilityStructure(PCIECapability * capability)
{
    return 0;
}*/