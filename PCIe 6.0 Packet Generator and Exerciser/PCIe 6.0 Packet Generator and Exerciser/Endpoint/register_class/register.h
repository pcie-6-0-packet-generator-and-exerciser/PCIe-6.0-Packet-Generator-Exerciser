#pragma once

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
    Register* next_;

public:
    Register(unsigned int v, Register_Name n, Register_Type t);

    void setRegisterValue(unsigned int v);

    void setRegisterName(Register_Name n);

    void setRegisterType(Register_Type t);

    void setNext(Register* n);

    unsigned int getRegisterValue();

    Register_Name getRegisterName();

    Register_Type getRegisterType();

    Register* getNext();
};