#include "pcie_controller.h"

PcieController::PcieController() : packetHandler_(nullptr) {}

void PcieController::setPacketHandler(TlpPacketHandler* handler) {
    packetHandler_ = handler;
}

// get the packet from the endpoint app and pass it to the packet handler
void PcieController::handleTlp(TLP packet) {
    packetHandler_->handleTlp(packet);
}

// get the completion from the packet handler and pass it to the endpoint app
void PcieController::handleCompletion(TLP completion) {
    // Handle the completion
    
}