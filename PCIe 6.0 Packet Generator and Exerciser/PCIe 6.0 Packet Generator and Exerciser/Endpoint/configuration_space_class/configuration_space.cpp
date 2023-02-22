/**
 * @brief ConfigurationSpace Constructor for initializing all of the configuration space registers
 *        with some predefined values
*/
ConfigurationSpace::ConfigurationSpace() :head_(nullptr), tail_(nullptr), size_(0)
{
    for (int i = 0; i < 18; i++)
    {
        switch (i)
        {
        case 0:
            push(0, Vendor_ID, HARDWARE_INITIALIZED);
            break;
        case 1:
            push(0, Device_ID, HARDWARE_INITIALIZED);
            break;
        case 2:
            push(1811, Command, READ_WRITE);
            break;
        case 3:
            push(1, Status, READ_WRITE);
            break;
        case 4:
            push(0, Revision_ID, HARDWARE_INITIALIZED);
            break;
        case 5:
            push(328967, Class_Code, READ_ONLY);
            break;
        case 6:
            push(128, Header_Type, READ_ONLY);
            break;
        case 7:
            push((unsigned int)1073741836, BAR0, READ_ONLY_READ_WRITE);
            break;
        case 8:
            push(0, BAR1, READ_ONLY_READ_WRITE);
            break;
        case 9:
            push((unsigned int)67108864, BAR2, READ_ONLY_READ_WRITE);
            break;
        case 10:
            push((unsigned int)65537, BAR3, READ_ONLY_READ_WRITE);
            break;
        case 11:
            push(0, BAR4, READ_ONLY_READ_WRITE);
            break;
        case 12:
            push(0, BAR5, READ_ONLY_READ_WRITE);
            break;
        case 13:
            push(0, Subsystem_Vendor_ID, HARDWARE_INITIALIZED);
            break;
        case 14:
            push(0, Subsystem_ID, HARDWARE_INITIALIZED);
            break;
        case 15:
            push(0, Expansion_ROM_Base_Address, READ_WRITE);
            break;
        case 16:
            push(0, Capabilities_Pointer, READ_ONLY);
            break;
        case 17:
            push(0, Interrupt_PIN, READ_ONLY);
            break;
        }
    }
}

/**
    * @brief ConfigurationSpace desructor for deleting all nodes in the linked list to avoid memory leaks
*/
~ConfigurationSpace()
{
    Register * current = head;
    Register* next;

    while (current)
    {
        size--;

        next = current->getNext();

        delete current;

        current = next;
    }
}

/**
    * @brief Getting a specific Register value stored in it
    * @param registerNumber -> the Register index 
    * @return unsigned int -> the Register value
*/
unsigned int getRegisterValue(int registerNumber)
{
    // check if the index is out of bounds
    if (registerNumber < 0 || registerNumber >= size)
    {
        /* Cpl with UR */
        return 0;
    }

    // traverse the linked list to find the node at the specified index
    Register * current = head;

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
Register_Name getRegisterName(int registerNumber)
{
    // check if the index is out of bounds
    if (registerNumber < 0 || registerNumber >= size)
    {
        /* Cpl with UR */
        return Empty;
    }

    // traverse the linked list to find the node at the specified index
    Register* current = head;

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
Register_Type getRegisterType(int registerNumber)
{
    // check if the index is out of bounds
    if (registerNumber < 0 || registerNumber >= size)
    {
        /* Cpl with UR */
        return EMPTY;
    }

    // traverse the linked list to find the node at the specified index
    Register* current = head;

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getNext();
    }

    return current->getRegisterType();
}