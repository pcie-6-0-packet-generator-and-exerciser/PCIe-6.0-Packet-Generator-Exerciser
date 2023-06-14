#pragma once

#include "..\configuration_classes\configuration_space.h"
#include "..\configuration_classes\pcie_capability.h"
#include "..\..\type1_config_space\type1_config.h"

class ConfigurationSpace;
class PCIECapability;
class Type1Config;

class ConfigurationVisitor
{
    protected:
        int registerNumber;

    public:
        ConfigurationVisitor();

        virtual unsigned int visitConfigurationSpace(ConfigurationSpace * configuration) = 0; // Pure virtual function
        
        virtual unsigned int visitPcieCapabilityStructure(PCIECapability * capability) = 0; // Pure virtual function

        virtual unsigned int visitType1ConfigSpace(Type1Config* t1) = 0;

        void setRegisterNumber(int registerNumber);
};