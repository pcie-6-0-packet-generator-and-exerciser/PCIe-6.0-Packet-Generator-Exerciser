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
    if (registerNumber < 0 || registerNumber >= configuration->getNumberOfRegisters() || registerNumber == 11 || registerNumber == 12)
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

    /* 1st we get the register value and we mask it, where:
    the bits which aren't Read Write bits (stay the same), and the bits we need to write in, we make clear them (make them = 0).

    2nd we get the data to be written in our register and we also mask it, where:
    the bits which aren't targetting Read Write bits (make them = 0), and the bits which we will use to write, we keep them as they are.

    3rd we make an OR operation. */

    if (registerNumber == 3) // The Status Register
    {
        // You can't write to the Signaled System Error bit and the SERR# Enable bit in the Command Register is = 0
        if ((data & 0x00004000) && !(command->getRegisterValue() & 0x00000100))
            data &= 0xFFFFBFFF;

        // You can't write to the Master Data Parity Error bit and the Parity Error Response bit in the Command Register is = 0
        if ((data & 0x00000100) && !(command->getRegisterValue() & 0x00000040))
            data &= 0xFFFFFEFF;

        // Then we can write to the Status Register
        current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
    }

    else if (registerNumber == 15)
    {
        if (configuration->isMemorySpaceEnabled()) // if the Memory space is enabled, so you can write in the bits (0, 11->31)
        {
            current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
        }
        else // if the Memory space is disabled, so you can't write in this register
        {
            configuration->setReceivedMasterAbortBit(); // Setting the Received Master Abort Bit in the Status Register as we received an Unsupported Request (UR)
            return 0; // Cpl with UR
        }
    }

    else
    {
        current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));
    }

    return 1; // The Write is done Successfully
}

unsigned int ConfigurationWriteVisitor::visitPcieCapabilityStructure(PCIECapability * capability)
{
    if (registerNumber < 0 || (registerNumber - 17) >= capability->getNumberOfRegisters() || (registerNumber != 21 && registerNumber != 22))
        return 0; // Cpl with UR

    /* Traversing the linked list till we get the specified Register to write in */
    Register* current = capability->getHead();

    for (int i = 0; i < registerNumber - 17; i++) // -17 because this structure's 1st Register starts after 17 Configuration Space Registers  
    {
        current = current->getRegisterNext();
    }

    /* 1st we get the register value and we mask it, where:
    the bits which aren't Read Write bits (stay the same), and the bits we need to write in, we make clear them (make them = 0).

    2nd we get the data to be written in our register and we also mask it, where:
    the bits which aren't targetting Read Write bits (make them = 0), and the bits which we will use to write, we keep them as they are.
    
    3rd we make an OR operation. */

    current->setRegisterValue((current->getRegisterValue() & (current->getRegisterMask())) | (data & ~(current->getRegisterMask())));

    return 1; // The Write is done Successfully
}


//set data + set register number
unsigned int ConfigurationWriteVisitor::visitType1ConfigSpace(Type1Config* t1)
{
    if (registerNumber < 0 || registerNumber >= t1->getNumberOfRegisters())
        return 0; // Cpl with UR

    /* Traversing the linked list till we get the specified Register to write in */
    Register* current = t1->getHead();

    for (int i = 0; i < registerNumber; i++)
        current = current->getRegisterNext();

    // The Register is either Read Only, or Hardware Initialized
    if (current->getRegisterType() == 0 || current->getRegisterType() == 1)
        return 0; // Cpl with UR

    current->setRegisterValue(data);
}