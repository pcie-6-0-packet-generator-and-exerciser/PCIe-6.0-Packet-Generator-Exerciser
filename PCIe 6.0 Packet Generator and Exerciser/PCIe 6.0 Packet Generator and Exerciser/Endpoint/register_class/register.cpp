#include "register.h"

Register::Register(unsigned int v, Register_Name n, Register_Type t):value_(v), name_(n), type_(t){}

void Register:: setRegisterValue(unsigned int v)
{
    value_ = v;
}

void Register::Register::setRegisterName(Register_Name n)
{
    name_ = n;
}

void Register::setRegisterType(Register_Type t)
{
    type_ = t;
}

void Register::setNext(Register* n)
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

Register* Register::getNext()
{
    return next_;
}