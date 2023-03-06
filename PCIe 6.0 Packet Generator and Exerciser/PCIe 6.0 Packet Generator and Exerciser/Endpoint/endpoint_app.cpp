
#include "endpoint_app.h"


EndpointApp::EndpointApp() {
    pcieController_ = std::make_unique<PcieController>();
    memoryMap_ = std::make_unique<MemoryMap>();
    configurationSpace_ = std::make_unique<ConfigurationSpace>();
}

//EndpointApp::~EndpointApp() {}

// get the packet from the layers and pass it to the pcie Controller

void EndpointApp::receivePacket(TLP packet) {
    pcieController_->handleTlp(packet);
}

// get the completion from the pcie controller and pass it to the layers
void EndpointApp::sendPacket(TLP packet) {
}