#pragma once

#include "configuration_visitor.h"

class ConfigurationSpace;
class PCIECapability;

class ConfigurationWriteVisitor: public ConfigurationVisitor
{
    private:
        unsigned int data;

    public:
        ConfigurationWriteVisitor();
        
        void setData(unsigned int data);

        unsigned int visitConfigurationSpace(ConfigurationSpace * configuration) override;

        unsigned int visitPcieCapabilityStructure(PCIECapability * capability) override;    
};