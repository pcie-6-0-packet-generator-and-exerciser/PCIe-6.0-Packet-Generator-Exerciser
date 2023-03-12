#include "pcie_capability.h"

class ConfigurationVisitor;

PCIECapability * PCIECapability::pcieCapability = nullptr;

PCIECapability::PCIECapability()
{
}

PCIECapability::~PCIECapability()
{
}

PCIECapability* PCIECapability::constructPCIECapability()
{
    if(pcieCapability == nullptr)
        pcieCapability = new PCIECapability();

    return pcieCapability;
}

unsigned int PCIECapability::accept(shared_ptr<ConfigurationVisitor> visitor)
{
    //return visitor->visitPcieCapabilityStructure(this);
    return 0;
}
