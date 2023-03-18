#include "configuration.h"

Configuration::Configuration():head_(nullptr), tail_(nullptr), size_(0) {}

Register* Configuration::getHead()
{
    return nullptr;
}

void Configuration::pushRegister(unsigned int value, Register_Name name, Register_Type type, int registerLengthInBytes, unsigned int initialValue, unsigned int mask)
{
    Register* newRegister = new Register(value, name, type, registerLengthInBytes, initialValue, mask);

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

int Configuration::getRegisterLengthInBytes(int registerNumber)
{
    // traverse the linked list to find the node at the specified index
    Register* current = head_;

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getRegisterNext();
    }

    return current->getRegisterLengthInBytes();
}

/**
 * @brief Returning the Device ID as it's needed in the construction of Completion TLPs
 * 
 * @return 
*/
unsigned int Configuration::getDeviceID()
{
    return head_->getRegisterNext()->getRegisterNext()->getRegisterValue();
}