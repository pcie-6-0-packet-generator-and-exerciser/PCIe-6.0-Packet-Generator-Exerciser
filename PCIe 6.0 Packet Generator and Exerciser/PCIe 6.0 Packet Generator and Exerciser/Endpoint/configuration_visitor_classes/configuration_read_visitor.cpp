#include "configuration_read_visitor.h"

/**
    * @brief Visiting the Configuration Sapce to get a specific Register's value stored in it
    * @param configuration -> A pointer to the Configuration Space to visit 
    * @return unsigned int -> the Register value
*/
unsigned int ConfigurationReadVisitor::visitConfigurationSpace(ConfigurationSpace * configuration)
{
    // traverse the linked list to find the node at the specified index
    Register * current = configuration->getHead();

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getRegisterNext();
    }

    return current->getRegisterValue();
}

unsigned int ConfigurationReadVisitor::visitPcieCapabilityStructure(PCIECapability* capability)
{
    // traverse the linked list to find the node at the specified index
    Register * current = capability->getHead();

    for (int i = 0; i < (registerNumber - 17); i++)
    {
        current = current->getRegisterNext();
    }

    return current->getRegisterValue();
}

unsigned int ConfigurationReadVisitor::visitType1ConfigSpace(Type1Config* t1)
{
    // traverse the linked list to find the node at the specified index
    Register* current = t1->getHead();

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getRegisterNext();
    }

    return current->getRegisterValue();
}
