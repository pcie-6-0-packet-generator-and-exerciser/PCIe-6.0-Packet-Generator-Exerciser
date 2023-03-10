#include "configuration_space.h"

/* Making out Configuration Space pointer = nullptr initially */
ConfigurationSpace * ConfigurationSpace::configurationSpace = nullptr;

/**
 * @brief ConfigurationSpace Constructor for initializing all of the configuration space registers
 *        with some predefined values, and to know the meaning of these values in details, you can
 *        have a look on Configuration-Space-Enumerations.pdf
*/
ConfigurationSpace::ConfigurationSpace()
{
    pushRegister(0, Vendor_ID, HARDWARE_INITIALIZED, 0, 0); // Vendor ID is set to zero till we get another value from Siemens

    pushRegister(0, Device_ID, HARDWARE_INITIALIZED, 0, 0); // Device ID is set to zero till we get another value from Siemens

    pushRegister(0, Command, READ_WRITE, 3, 0xFFFFFABC);

    pushRegister(17, Status, READ_WRITE, 17, 0xFFFF5EFF);

    pushRegister(0, Revision_ID, HARDWARE_INITIALIZED, 0, 0);

    pushRegister(557056, Class_Code, READ_ONLY, 524416, 0);

    pushRegister(0, Header_Type, READ_ONLY, 0, 0);

    // Will contain the base address of a  1GB block of Prefetchable MMIO which supports 64-Bits address
    pushRegister(12, BAR0, READ_ONLY_READ_WRITE, 12, 0x3FFFFFFF); 

    // Will contain the base address of the same 1GB block of Prefetchable MMIO which supports 64-Bits address
    pushRegister(0, BAR1, READ_ONLY_READ_WRITE, 0, 0x000000);

    // Will contain the base address of a 64MB block of Non-prefetchable MMIO which supports 32-Bits address
    pushRegister(0, BAR2, READ_ONLY_READ_WRITE, 0, 0x03FFFFFF);

    // Will contain the base address of a 4KB block of IO space
    pushRegister(1, BAR3, READ_ONLY_READ_WRITE, 1, 0x00000FFF);
    // Not used
    pushRegister(0, BAR4, READ_ONLY_READ_WRITE, 0, 0);
    // Not used
    pushRegister(0, BAR5, READ_ONLY_READ_WRITE, 0, 0);

    pushRegister(0, Subsystem_Vendor_ID, HARDWARE_INITIALIZED, 0, 0);

    pushRegister(0, Subsystem_ID, HARDWARE_INITIALIZED, 0, 0);

    pushRegister(0, Expansion_ROM_Base_Address, READ_WRITE, 0, 0x000007FE);

    pushRegister(0, Capabilities_Pointer, READ_ONLY, 0, 0);
}

/**
 * @brief Making the Only available Configuration Space (Singleton Class)
 * 
 * @return shared_ptr<ConfigurationSpace> -> a pointer to our only one Configuration Space
 */
ConfigurationSpace * ConfigurationSpace::constructConfigurationSpace()
{
    if(configurationSpace == nullptr)
        configurationSpace = new ConfigurationSpace();

    return configurationSpace;
}

/**
    * @brief ConfigurationSpace desructor for deleting all nodes in the linked list to avoid memory leaks
*/
ConfigurationSpace::~ConfigurationSpace()
{
    Register * current = head_;
    Register* next;

    while (current)
    {
        size_--;

        next = current->getRegisterNext();

        delete current;

        current = next;
    }
}

/**
 * @brief This function is for accepting a visit from a configuration read or write visitor to either read from the configuration space
 *        or write to it
 * 
 * @param visitor -> either a configuration read or write visitor
 * @return unsigned int -> the value read from the configuration space or zero in case of writing to the configuration space
 */
unsigned int ConfigurationSpace::accept(shared_ptr<ConfigurationVisitor> visitor)
{
    return visitor->visitConfigurationSpace(this);
}

/**
 * @brief Getting the size of the linked list (Configuration Space)
 * 
 * @return int -> size of the linked list
 */
int ConfigurationSpace::getNumberOfRegisters()
{
    return size_;
}

/**
 * @brief Setting the Master Abort bit in the Status Register when we receive an Unsupported Request
 *        so a completion with UR will be sent to the requester, and this bit will be set to 1
 */
void ConfigurationSpace::setReceivedMasterAbortBit()
{
    Register * status = head_;
    status = status->getRegisterNext()->getRegisterNext()->getRegisterNext();

    status->setRegisterValue((status->getRegisterValue() & 0xFFFFDFFF) | 0x00002000);
}

/**
 * @brief This function is be used by the memory class to know whether it can serve any access (read or write) request or not
 * 
 * @return int -> whether the Memory Space is enabled or not
 */
int ConfigurationSpace::isMemorySpaceEnabled()
{
    // Traverse the linked list to find the Command Register
    Register * current = head_;
    Register * command = head_;
    command = command->getRegisterNext()->getRegisterNext();

    // If the Memory Space Enable bit (bit number 2) is set to 1, then return 1, otherwise return 0
    return (command->getRegisterValue() & 0x00000002);
}

/**
 * @brief This function is be used by the IO class to know whether it can serve any access (read or write) request or not
 * 
 * @return int -> whether the IO Space is enabled or not
 */
int ConfigurationSpace::isIOSpaceEnabled()
{
    // Traverse the linked list to find the Command Register
    Register * current = head_;
    Register * command = head_;
    command = command->getRegisterNext()->getRegisterNext();

    // If the IO Space Enable bit (bit number 1) is set to 1, then return 1, otherwise return 0
    return (command->getRegisterValue() & 0x00000001);
}