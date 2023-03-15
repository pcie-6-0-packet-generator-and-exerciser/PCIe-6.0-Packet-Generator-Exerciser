#include "pcie_capability.h"

PCIECapability * PCIECapability::pcieCapability = nullptr;

/**
 * @brief PCIE Capabilities Structure Constructor for initializing all of the needed Registers
 *        with some predefined values, and to know the meaning of these values in details, you can
 *        have a look on Configuration-Space-Enumerations.pdf
*/
PCIECapability::PCIECapability()
{
    /* Notice that any Read Only Register will have 0 in its mask (as it won't be written in) */

    pushRegister(1, PCI_Express_Capabilities_ID, READ_ONLY, 1, 1, 0); // Stores the Capabilities ID assigned by the PCI-SIG (it will be 0x1 as this is the default value till it's given to me)

    pushRegister(128, Next_Cap_Pointer, READ_ONLY, 1, 128, 0); // 128 is its default value as well

    pushRegister(3, PCI_Express_Capabilities_Register, READ_ONLY, 2, 3, 0);

    pushRegister(0, Device_Capabilities, READ_ONLY, 4, 0, 0);

    pushRegister(1, Device_Control, READ_WRITE, 2, 1, 0x11110600);

    pushRegister(0, Device_Status, READ_WRITE, 2, 0, 0x11111110);
}

/**
    * @brief ConfigurationSpace desructor for deleting all nodes in the linked list to avoid memory leaks
*/
PCIECapability::~PCIECapability()
{
    Register* current = head_;
    Register* next;

    while (current)
    {
        size_--;

        next = current->getRegisterNext();

        delete current;

        current = next;
    }
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

void PCIECapability::setUnsupportedRequestDetectedBit()
{
    Register* deviceStatus = tail_; // going to the Device Status Register (the last Register)

    /* Setting the bit number 19 to tell that there is a detected Unsupported Request */
    deviceStatus->setRegisterValue((deviceStatus->getRegisterValue() & 0xFFF3FFFF) | 0x00080000);
}
