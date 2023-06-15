#include "type1_config.h"

class ConfigurationVisitor;

/* Making out Configuration Space pointer = nullptr initially */

Type1Config* Type1Config::t1 = nullptr;

/**
 * @brief Type1ConfigSpace Constructor for initializing all of the type 1 configuration space registers
 *        with some predefined values defined in the NCB_PCI_Express_Base_6.0.pdf .
*/
Type1Config::Type1Config()
{
    pushRegister(0, Vendor_ID, HARDWARE_INITIALIZED, 2, 0, 0); // Vendor ID is set to zero till we get another value from Siemens

    pushRegister(0, Device_ID, HARDWARE_INITIALIZED, 2, 0, 0); // Device ID is set to zero till we get another value from Siemens

    pushRegister(0, Command, READ_WRITE, 2, 3, 0xFFFFFABC);

    pushRegister(17, Status, READ_WRITE, 2, 17, 0xFFFF5EFF);

    pushRegister(0, Revision_ID, HARDWARE_INITIALIZED, 1, 0, 0);

    pushRegister(557056, Class_Code, READ_ONLY, 3, 524416, 0);

    pushRegister(0, Header_Type, READ_ONLY, 1, 0, 0);

    pushRegister(0, BAR0, READ_ONLY_READ_WRITE, 4, 0, 0);

    pushRegister(0, BAR1, READ_ONLY_READ_WRITE, 4, 0, 0);

    pushRegister(0, IO_BASE, READ_WRITE, 1, 0, 0);

    pushRegister(0, IO_LIMIT, READ_WRITE, 1, 0, 0);

    pushRegister(0, SECONDARY_STATUS, READ_WRITE, 2, 0, 0);

    pushRegister(0, MEMORY_BASE, READ_WRITE, 2, 0, 0);

    pushRegister(0, MEMORY_LIMIT, READ_WRITE, 2, 0, 0);

    pushRegister(0, PREFETCHABLE_MEMORY_BASE, READ_WRITE, 2, 0, 0);

    pushRegister(0, PREFETCHABLE_MEMORY_LIMIT, READ_WRITE, 2, 0, 0);

    pushRegister(0, PREFETCHABLE_BASE_UPPER32, READ_WRITE, 4, 0, 0);

    pushRegister(0, PREFETCHABLE_LIMIT_UPPER32, READ_WRITE, 4, 0, 0);

    pushRegister(0, IO_BASE_UPPER16, READ_WRITE, 2, 0, 0);

    pushRegister(0, IO_LIMIT_UPPER16, READ_WRITE, 2, 0, 0);

    pushRegister(0, Capabilities_Pointer, READ_ONLY, 1, 0, 0);

    pushRegister(0, Expansion_ROM_Base_Address, READ_WRITE, 4, 0, 0x000007FE);
}

/**
    * @brief ConfigurationSpace desructor for deleting all nodes in the linked list to avoid memory leaks
*/
Type1Config::~Type1Config()
{
    Register* current = head_;
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
 * @brief Making the Only available Configuration Space (Singleton Class)
 *
 * @return shared_ptr<ConfigurationSpace> -> a pointer to our only one Configuration Space
 */
Type1Config* Type1Config::constructType1ConfigSpace()
{
    if (t1 == nullptr)
        t1 = new Type1Config();

    return t1;
}

unsigned int Type1Config::accept(shared_ptr<ConfigurationVisitor> visitor)
{
    return visitor->visitType1ConfigSpace(this);
}

boost::dynamic_bitset<> Type1Config::convertToBitSet(unsigned int uintValue)
{
    boost::dynamic_bitset<> bitset; // 32 bits in an unsigned int

    if (uintValue == 0)
        bitset.push_back(0);

    while (uintValue != 0)
    {
        bitset.push_back(uintValue & 1);
        uintValue >>= 1;
    }

    return bitset;
}

unsigned int Type1Config::convertToUnsignedInt(boost::dynamic_bitset<> data)
{
    unsigned int uintValue = static_cast<unsigned int>(data.to_ulong());

    return uintValue;
}

boost::dynamic_bitset<> Type1Config::readType1Reg(int registerNumber)
{
    /* In case of invalid register number */
    if (registerNumber < 0 || registerNumber > 21)
    {
        boost::dynamic_bitset<> data;
        return data;
    }

    Register* current = t1->getHead();

    for (int i = 0; i < registerNumber; i++)
        current = current->getRegisterNext();

    unsigned int readData = current->getRegisterValue();

    return convertToBitSet(readData);
}

int Type1Config::writeType1Reg(int registerNumber, boost::dynamic_bitset<> data)
{
    /* In case of invalid register number */
    if (registerNumber < 0 || registerNumber > 21)
        return 0;

    unsigned int writtenData = convertToUnsignedInt(data);
    Register* current = t1->getHead();

    for (int i = 0; i < registerNumber; i++)
        current = current->getRegisterNext();

    /* In case of writting in a Read only or Hardware Initialized Registers */
    if (current->getRegisterType() == 0 || current->getRegisterType() == 1)
        return 0;

    current->setRegisterValue(writtenData);

    return 1;
}