#include "EndpointApp.h"

EndpointApp::EndpointApp(PCIeController* controller, MemoryMap* memoryMap, ConfigurationSpace* configSpace)
    : controller_(controller), memoryMap_(memoryMap), configSpace_(configSpace)
{
    // Initialize BAR 0 memory
    uint64_t bar0Size = configSpace_->getBarSize(0);
    if (bar0Size) {
        bar0Memory_.resize(bar0Size);
        memoryMap_->addMemoryRegion(bar0Size, bar0Memory_.data(), 0, true);
        configSpace_->setBar(0, MemoryMap::kType32Bit, 0, true);
    }

    // Initialize BAR 1 memory
    uint64_t bar1Size = configSpace_->getBarSize(1);
    if (bar1Size) {
        bar1Memory_.resize(bar1Size);
        memoryMap_->addMemoryRegion(bar1Size, bar1Memory_.data(), 0, true);
        configSpace_->setBar(1, MemoryMap::kType32Bit, 0, true);
    }

    // Initialize BAR 2 memory
    uint64_t bar2Size = configSpace_->getBarSize(2);
    if (bar2Size) {
        bar2Memory_.resize(bar2Size);
        memoryMap_->addMemoryRegion(bar2Size, bar2Memory_.data(), 0, true);
        configSpace_->setBar(2, MemoryMap::kType32Bit, 0, true);
    }

    // Initialize BAR 3 memory
    uint64_t bar3Size = configSpace_->getBarSize(3);
    if (bar3Size) {
        bar3Memory_.resize(bar3Size);
        memoryMap_->addMemoryRegion(bar3Size, bar3Memory_.data(), 0, true);
        configSpace_->setBar(3, MemoryMap::kType32Bit, 0, true);
    }
}

void EndpointApp::sendPacket(const uint8_t* data, uint32_t length) {
    // code to send a packet using the PCIeController
}

void EndpointApp::receivePacket(uint8_t* data, uint32_t length) {
    // code to receive a packet using the PCIeController
}

uint32_t EndpointApp::handleMemoryRead(MemoryRequest* request) {
    return controller_->handleMemoryRead(request);
}

uint32_t EndpointApp::handleMemoryWrite(MemoryRequest* request) {
    return controller_->handleMemoryWrite(request);
}

uint32_t EndpointApp::handleConfigRead(ConfigurationRequest* request) {
    return controller_->handleConfigRead(request);
}

uint32_t EndpointApp::handleConfigWrite(ConfigurationRequest* request) {
    return controller_->handleConfigWrite(request);
}
