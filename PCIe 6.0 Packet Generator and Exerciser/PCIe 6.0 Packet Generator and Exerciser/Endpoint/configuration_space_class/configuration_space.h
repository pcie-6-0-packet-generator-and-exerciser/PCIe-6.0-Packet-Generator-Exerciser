#pragma once
#include "..\register_class\register.h"

class ConfigurationSpace
{
private:
    Register * head_;
    Register * tail_;
    int size_;

    /* Create a new node to store the value */
    void push(unsigned int v, Register_Name n, Register_Type t);

public:
    ConfigurationSpace();

    /* Delete all nodes in the linked list by the destructor to avoid memory leaks */
    ~ConfigurationSpace();

    unsigned int getRegisterValue(int registerNumber);

    Register_Name getRegisterName(int registerNumber);

    Register_Type getRegisterType(int registerNumber);
};