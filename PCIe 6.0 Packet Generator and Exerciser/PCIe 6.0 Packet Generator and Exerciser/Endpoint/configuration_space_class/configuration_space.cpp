#include "configuration_space.h"
#include "..\register_class\register.h"

/**
 * @brief ConfigurationSpace Constructor for initializing all of the configuration space registers
 *        with some predefined values
*/
ConfigurationSpace::ConfigurationSpace() :head_(nullptr), tail_(nullptr), size_(0)
{
    for (int i = 0; i < 17; i++)
    {
        switch (i)
        {
        case 0:
            push(0, Vendor_ID, HARDWARE_INITIALIZED, 0, 0); // Vendor ID is set to zero till we get another value from Siemens
            break;
        case 1:
            push(0, Device_ID, HARDWARE_INITIALIZED, 0, 0); // Device ID is set to zero till we get another value from Siemens
            break;
        case 2:
            push(3, Command, READ_WRITE, 3, 0xFFFFFABC);
            break;
        case 3:
            push(17, Status, READ_WRITE, 17, 0xFFFF5EFF);
            break;
        case 4:
            push(0, Revision_ID, HARDWARE_INITIALIZED, 0, 0);
            break;
        case 5:
            push(524416, Class_Code, READ_ONLY, 524416, 0);
            break;
        case 6:
            push(0, Header_Type, READ_ONLY, 0, 0);
            break;
        case 7:
            // Will contain the base address of a  1GB block of Prefetchable MMIO which supports 64-Bits address
            push(12, BAR0, READ_ONLY_READ_WRITE, 12, 0x3FFFFFFF); 
            break;
        case 8:
            // Will contain the base address of the same 1GB block of Prefetchable MMIO which supports 64-Bits address
            push(0, BAR1, READ_ONLY_READ_WRITE, 0, 0x000000);
            break;
        case 9:
            // Will contain the base address of a 64MB block of Non-prefetchable MMIO which supports 32-Bits address
            push(0, BAR2, READ_ONLY_READ_WRITE, 0, 0x03FFFFFF);
            break;
        case 10:
            // Will contain the base address of a 4KB block of IO space
            push(1, BAR3, READ_ONLY_READ_WRITE, 1, 0x00000FFF);
            break;
        case 11:
            // Not used
            push(0, BAR4, READ_ONLY_READ_WRITE, 0, 0);
            break;
        case 12:
            // Not used
            push(0, BAR5, READ_ONLY_READ_WRITE, 0, 0);
            break;
        case 13:
            push(0, Subsystem_Vendor_ID, HARDWARE_INITIALIZED, 0, 0);
            break;
        case 14:
            push(0, Subsystem_ID, HARDWARE_INITIALIZED, 0, 0);
            break;
        case 15:
            push(0, Expansion_ROM_Base_Address, READ_WRITE, 0, 0x000007FE);
            break;
        case 16:
            push(0, Capabilities_Pointer, READ_ONLY, 0, 0);
            break;
        }
    }
}

/**
    * @brief ConfigurationSpace desructor for deleting all nodes in the linked list to avoid memory leaks
*/
/*ConfigurationSpace::~ConfigurationSpace()
{
    Register * current = head_;
    Register* next;

    while (current)
    {
        size_--;

        next = current->getNext();

        delete current;

        current = next;
    }
}
*/

/**
    * @brief Getting a specific Register value stored in it
    * @param registerNumber -> the Register index 
    * @return unsigned int -> the Register value
*/
unsigned int ConfigurationSpace::getRegisterValue(int registerNumber)
{
    // check if the index is out of bounds
    if (registerNumber < 0 || registerNumber >= size_)
    {
        /* Cpl with UR */
        return 0;
    }

    // traverse the linked list to find the node at the specified index
    Register * current = head_;

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getNext();
    }

    return current->getRegisterValue();
}

/**
    * @brief Getting a specific register name
    * @param registerNumber -> Register index
    * @return Register_Name (enum) -> Register name
*/
Register_Name ConfigurationSpace::getRegisterName(int registerNumber)
{
    // check if the index is out of bounds
    if (registerNumber < 0 || registerNumber >= size_)
    {
        /* Cpl with UR */
        return Empty;
    }

    // traverse the linked list to find the node at the specified index
    Register* current = head_;

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getNext();
    }

    return current->getRegisterName();
}

/**
    * @brief Getting a specific register type
    * @param registerNumber -> Register index
    * @return Register_Type (enum) -> Register type
*/
Register_Type ConfigurationSpace::getRegisterType(int registerNumber)
{
    // check if the index is out of bounds
    if (registerNumber < 0 || registerNumber >= size_)
    {
        /* Cpl with UR */
        return EMPTY;
    }

    // traverse the linked list to find the node at the specified index
    Register* current = head_;

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getNext();
    }

    return current->getRegisterType();
}

/**
    * @brief Pushing a new node into our linked list which represents our Configuration Space
    *        (Each Node represents a Register)
    * @param v -> the Register value
    * @param n -> the Register name (Vendor_ID, Command, ...)
    * @param t -> the Register type (RO, RW, HwI)
*/
void ConfigurationSpace::push(unsigned int v, Register_Name n, Register_Type t, unsigned int i,unsigned int m)
{
    Register* newRegister = new Register(v, n, t, i, m);

    // add the new node to the end of the linked list
    if (tail_ != nullptr)
    {
        tail_->setNext(newRegister);
    }

    tail_ = newRegister;

    if (head_ == nullptr)
    {
        head_ = newRegister;
    }

    size_++;
}

/**
 * @brief Setting a specific Register value, checking if the Register is Read Only or Hardware Initialized, the function will return 0,
 *        otherwise it will set the value (and will not affect any Read only, Hardware Initialized, or resrved Bits) and return 1.
 * 
 * @param registerNumber -> the Register index
 * @param value -> the value to be set
 * @return int -> 1 if the value was set, 0 otherwise
 */
int ConfigurationSpace::setRegister(int registerNumber, unsigned int value)
{ 
    /* 
       Check if the index is out of bounds, or 
       The Register is a BAR (Base Address Register) with read only bits (not used by the endpoint to request for memory or IO space)
       so the root complex can't write to it, so we will return 0
    */
    if (registerNumber < 0 || registerNumber >= size_ || registerNumber == 11 || registerNumber == 12)
        return 0; // Cpl with UR

    // Traverse the linked list to find the node at the specified index
    Register * current = head_;
    Register * command = head_;
    command = command->getNext()->getNext();

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getNext();
    }

    // The Register is either Read Only, or Hardware Initialized
    if (current->getRegisterType() == 0 || current->getRegisterType() == 1)
        return 0; // Cpl with UR

    switch (registerNumber)
    {
    case 2: // Command Register
        current->setRegisterValue((current->getRegisterValue() & (current->getMask())) | (value & ~(current->getMask()))) ;
        break;
    case 3: // Status Register
        // You can't write to the Signaled System Error bit and the SERR# Enable bit in the Command Register is = 0
        if((value & 0x00004000) && !(command->getRegisterValue() & 0x00000100))
            value &= 0xFFFFBFFF;

        // You can't write to the Master Data Parity Error bit and the Parity Error Response bit in the Command Register is = 0
        if((value & 0x00000100) && !(command->getRegisterValue() & 0x00000040))
            value &= 0xFFFFFEFF;

        // Then we can write to the Status Register
        current->setRegisterValue((current->getRegisterValue() & (current->getMask())) | (value & ~(current->getMask())));
        break;
    case 7: // BAR0
        current->setRegisterValue((current->getRegisterValue() & (current->getMask())) | (value & ~(current->getMask())));
        break;
    case 8: // BAR1
        current->setRegisterValue((current->getRegisterValue() & (current->getMask())) | (value & ~(current->getMask())));
        break;
    case 9: // BAR2
        current->setRegisterValue((current->getRegisterValue() & (current->getMask())) | (value & ~(current->getMask())));
        break;
    case 10: // BAR3
        current->setRegisterValue((current->getRegisterValue() & (current->getMask())) | (value & ~(current->getMask())));
        break;
    case 15: // Expansion ROM Base Address Register
        if(command->getRegisterValue() & 0x00000002) // if the Memory space is enabled, so you can write in the bits (0, 11->31)
        {
            current->setRegisterValue((current->getRegisterValue() & (current->getMask())) | (value & ~(current->getMask())));
        }
        else // if the Memory space is disabled, so you can't write in this register
        {
            return 0; // Cpl with UR
        }
        break;
    }

    return 1;
}

/**
 * @brief Getting the size of the linked list (Configuration Space)
 * 
 * @return int -> size of the linked list
 */
int ConfigurationSpace::getSize()
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
    status = status->getNext()->getNext()->getNext();

    status->setRegisterValue((status->getRegisterValue() & 0xFFFFDFFF) | 0x00002000);
}