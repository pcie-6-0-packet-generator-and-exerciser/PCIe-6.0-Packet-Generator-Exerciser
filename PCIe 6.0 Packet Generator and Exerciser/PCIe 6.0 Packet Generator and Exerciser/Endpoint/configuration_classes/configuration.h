#pragma once

//#include "..\configuration_visitor_classes\configuration_visitor.h"
#include "..\register_class\register.h"

class ConfigurationVisitor;

class Configuration
{
protected:
    Register * head_;
    Register * tail_;
    int size_;

public:
    Configuration();

    virtual unsigned int accept(shared_ptr<ConfigurationVisitor> visitor) = 0; // Pure virtual function

    void pushRegister(unsigned int value, Register_Name name, Register_Type type, unsigned int initialValue, unsigned int mask);

    Register * getHead();

    int getSize();
};
