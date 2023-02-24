#include "pcie_controller.h"

PCIeController::PCIeController(ConfigurationSpace* configSpace, MemoryMap* memoryMap, EndpointApp* endpointApp) :
    configSpace_(configSpace), memoryMap_(memoryMap), endpointApp_(endpointApp) {}

void PCIeController::sendPacket(Packet* packet) {
    // TODO: implement packet sending logic
}

Packet* PCIeController::receivePacket() {
    // TODO: implement packet receiving logic
    return nullptr;
}

void PCIeController::handleMemoryRead(MemoryRequest* request) {
    // TODO: implement memory read handling logic
}

void PCIeController::handleMemoryWrite(MemoryRequest* request) {
    // TODO: implement memory write handling logic
}

void PCIeController::handleConfigRead(ConfigRequest* request) {
    // TODO: implement config read handling logic
}

void PCIeController::handleConfigWrite(ConfigRequest* request) {
    // TODO: implement config write handling logic
}
