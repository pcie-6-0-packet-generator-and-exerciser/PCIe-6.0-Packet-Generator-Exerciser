#include "pcie_capability.h"

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
    /* To be used after making the PCIE Capability structure */
    //return visitor->visitPcieCapabilityStructure(this);

    return 0;
}
