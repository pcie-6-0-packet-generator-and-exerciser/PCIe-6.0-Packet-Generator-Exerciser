#include "configuration.h"

Configuration::Configuration():head_(nullptr), tail_(nullptr), size_(0) {}

Register* Configuration::getHead()
{
    return nullptr;
}

void Configuration::pushRegister(unsigned int value, Register_Name name, Register_Type type, unsigned int initialValue, unsigned int mask)
{
    Register* newRegister = new Register(value, name, type, initialValue, mask);

    // add the new node to the end of the linked list
    if (tail_ != nullptr)
    {
        tail_->setRegisterNext(newRegister);
    }

    tail_ = newRegister;

    if (head_ == nullptr)
    {
        head_ = newRegister;
    }

    size_++;
}

int Configuration::getSize()
{
    return size_;
}