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

/* To be used after making the PCIE Capability structure */

/*unsigned int ConfigurationReadVisitor::visitPcieCapabilityStructure(PCIECapability* capability)
{
    // traverse the linked list to find the node at the specified index
    Register * current = capability->getHead();

    for (int i = 0; i < registerNumber; i++)
    {
        current = current->getRegisterNext();
    }

    return current->getRegisterValue();
}*/
