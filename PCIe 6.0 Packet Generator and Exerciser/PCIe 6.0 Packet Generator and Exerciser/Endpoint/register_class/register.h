#pragma once

#include <memory>
#include "..\..\utils\tlp.h"
#include "boost/dynamic_bitset.hpp"

using namespace std;

enum Register_Type
{
    HARDWARE_INITIALIZED,
    READ_ONLY,
    READ_WRITE,

    // Special type for BARs, because their lower bits are Read only, while their upper bits are Read Write
    READ_ONLY_READ_WRITE,
    EMPTY
};

enum Register_Name
{
    Vendor_ID,
    Device_ID,
    Command,
    Status,
    Revision_ID,
    Class_Code,
    Header_Type,
    BAR0,
    BAR1,
    BAR2,
    BAR3,
    BAR4,
    BAR5,
    Subsystem_Vendor_ID,
    Subsystem_ID,
    Expansion_ROM_Base_Address,
    Capabilities_Pointer,
    Interrupt_PIN,
    Empty
};

class Register
{
private:
    unsigned int value_;
    Register_Name name_;
    Register_Type type_;

    /* This value will be put in the Hardware Initialized (HwInit) and Read Only (RO) bits of the registers
       And to know what does these values mean (mapping each bit to a specific functionality or state),
       have a look on the document called Configuration-Space-Enumerations
       It will be the same value put in the value_ only at the begining, then the value_ will be changed by the configuration writes
       while the initialValue_ will remain the same
    */
    unsigned int initialValue_; 

    /* This mask will be used only by Read Write Registers so that when a configuration write comes, we only take the bits which
       we can write in (RW-bits), and ignore other bits (because a Read Write register contains RW bits, RO bits, and HwInit bits and 
       we don't want to write in either RO, or HwInit bits)
       It will be = 0 for HwInit and RO registers (as we can't write in them)
    */
    unsigned int mask_;

    Register* next_;

public:
    Register(unsigned int value, Register_Name name, Register_Type type, unsigned int initialValue, unsigned int mask);

    void setRegisterValue(unsigned int v);

    void setRegisterNext(Register* n);

    Register_Name getRegisterName();

    Register_Type getRegisterType();

    unsigned int getRegisterValue(); // For getting the current register value

    unsigned int getRegisterInitialValue(); // For getting the initial register value

    unsigned int getRegisterMask();

    Register* getRegisterNext();
};