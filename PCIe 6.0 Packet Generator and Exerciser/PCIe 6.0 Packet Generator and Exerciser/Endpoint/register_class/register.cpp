#include "register.h"

/**
 * @brief A Constructor for initializing all of the Register attributes (which some of them won't be accessible again)
 * 
 * @param v -> Register value
 * @param n -> Register name
 * @param t -> Register type
 * @param i -> Register initial value
 * @param m -> Register mask which is used so that no Read Only or Hardware Initialized bits are corrupted
 */
Register::Register(unsigned int v, Register_Name n, Register_Type t, unsigned int i, unsigned int m):value_(v), name_(n), type_(t), initialValue_(i), mask_(m), next_(nullptr){}

void Register::setRegisterValue(unsigned int v)
{
    value_ = v;
}

void Register::setRegisterNext(Register* n)
{
    next_ = n;
}

unsigned int Register::getRegisterValue()
{
    return value_;
}

Register_Name Register::getRegisterName()
{
    return name_;
}

Register_Type Register::getRegisterType()
{
    return type_;
}

Register* Register::getRegisterNext()
{
    return next_;
}

/**
 * @brief This function returns the initial value before any made configurations so that we can know the initial status of the register
 * 
 * @return unsigned int -> initial value put by the Endpoint Vendor
 */
unsigned int Register::getRegisterInitialValue()
{
    return initialValue_;
}

unsigned int Register::getRegisterMask()
{
    return mask_;
}