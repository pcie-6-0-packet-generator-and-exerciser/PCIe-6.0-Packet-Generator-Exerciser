#include "configuration_visitor.h"

ConfigurationVisitor::ConfigurationVisitor(): registerNumber(0){}

void ConfigurationVisitor::setRegisterNumber(int num)
{
    registerNumber = num;
}