#pragma once

#include "configuration.h"

class ConfigurationVisitor;

class PCIECapability : public Configuration
{
private:
    static PCIECapability * pcieCapability;

    PCIECapability();   
    
    ~PCIECapability();

public:
    static PCIECapability * constructPCIECapability();

    unsigned int accept(shared_ptr<ConfigurationVisitor> visitor) override;
};