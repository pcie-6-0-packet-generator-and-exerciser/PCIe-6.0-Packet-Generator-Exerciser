#pragma once

#include "configuration_visitor.h"

class ConfigurationReadVisitor: public ConfigurationVisitor
{
public:
    unsigned int visitConfigurationSpace(ConfigurationSpace * configuration) override;
    
    unsigned int visitPcieCapabilityStructure(PCIECapability * capability) override;
};