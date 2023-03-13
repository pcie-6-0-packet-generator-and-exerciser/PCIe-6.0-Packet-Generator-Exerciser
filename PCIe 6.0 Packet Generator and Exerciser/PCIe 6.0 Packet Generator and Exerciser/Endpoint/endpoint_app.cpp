#include "endpoint_app.h"

EndpointApp::EndpointApp(uint64_t hostMemorySize, uint64_t deviceMemorySize) {
    memoryMap_ = std::make_unique<MemoryMap>(hostMemorySize, deviceMemorySize);
    memoryController_ = std::make_unique<MemoryController>(std::move(memoryMap_));
    configurationController_ = std::make_unique<ConfigurationController>();
}


void EndpointApp::receivePacket(TLP* packet) {
    if (packet->header->TLPtype == TLPType::MemRead32 || packet->header->TLPtype == TLPType::MemRead64
        || packet->header->TLPtype == TLPType::MemWrite32 || packet->header->TLPtype == TLPType::MemWrite64) {
        memoryController_->handleTlp(packet);
    }
    else if (packet->header->TLPtype == TLPType::ConfigRead0 || packet->header->TLPtype == TLPType::ConfigRead1
            || packet->header->TLPtype == TLPType::ConfigWrite0 || packet->header->TLPtype == TLPType::ConfigWrite1) {
        configurationController_->handleConfigurationRequest(packet);
    }
    else {
        // If TLP type is not recognized, do nothing and return
        return;
    }
}

void EndpointApp::sendPacket(TLP* packet) {
    // Implementation of sending packets
}
