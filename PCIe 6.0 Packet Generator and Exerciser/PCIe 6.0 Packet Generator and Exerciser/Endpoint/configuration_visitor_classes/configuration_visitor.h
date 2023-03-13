#pragma once

#include "..\configuration_classes\configuration_space.h"
#include "..\configuration_classes\pcie_capability.h"

class ConfigurationSpace;
class PCIECapability;

class ConfigurationVisitor
{
    protected:
        int registerNumber;

    public:
        ConfigurationVisitor();

        virtual unsigned int visitConfigurationSpace(ConfigurationSpace * configuration) = 0; // Pure virtual function
        
        //virtual unsigned int visitPcieCapabilityStructure(PCIECapability * capability) = 0; // Pure virtual function

        void setRegisterNumber(int registerNumber);
};