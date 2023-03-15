#pragma once

#include "configuration.h"
#include "..\configuration_visitor_classes\configuration_visitor.h"

class PCIECapability : public Configuration
{
private:
    static PCIECapability * pcieCapability;

    PCIECapability();   
    
    ~PCIECapability();

public:
    static PCIECapability * constructPCIECapability();

    unsigned int accept(shared_ptr<ConfigurationVisitor> visitor) override;

    void setUnsupportedRequestDetectedBit();
};