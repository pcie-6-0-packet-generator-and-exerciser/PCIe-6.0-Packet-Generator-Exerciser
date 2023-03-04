#include "pcie_controller.h"

PCIeController::PCIeController(ConfigurationSpace* configSpace, MemoryMap* memoryMap, EndpointApp* endpointApp)
    : configSpace_(configSpace), memoryMap_(memoryMap), endpointApp_(endpointApp)
{
    // Create handlers for each TLP type
    handlers_[TLP_MEM_READ_REQ] = new MemoryReadHandler();
    handlers_[TLP_MEM_WRITE_REQ] = new MemoryWriteHandler();
    handlers_[TLP_CFG_READ_REQ] = new ConfigReadHandler();
    handlers_[TLP_CFG_WRITE_REQ] = new ConfigWriteHandler();
}

void PCIeController::sendPacket(Packet* packet)
{
    // TODO: send the packet over PCIe link
}

Packet* PCIeController::receivePacket()
{
    // TODO: receive the packet from the PCIe link
    // and parse the packet header to determine the TLP type

    // Get the appropriate handler for the TLP type
    uint8_t tlpType = 0; // TODO: get TLP type from packet header
    TlpPacketHandler* handler = handlers_[tlpType];

    // Call the handler's handleTlp method
    handler->handleTlp(packet);

    // TODO: return response packet if needed
    return nullptr;
}
