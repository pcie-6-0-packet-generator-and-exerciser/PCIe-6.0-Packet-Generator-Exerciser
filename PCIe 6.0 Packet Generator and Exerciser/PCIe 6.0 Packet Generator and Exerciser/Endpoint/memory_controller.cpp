#include "memory_controller.h"

MemoryController::MemoryController(std::unique_ptr<MemoryMap> memoryMap) : memoryMap_(std::move(memoryMap)), packetHandler_(nullptr) {
}


void MemoryController::setPacketHandler(MemoryRequestHandler* handler) {
    packetHandler_ = handler;
}

// get the packet from the endpoint app and pass it to the packet handler
void MemoryController::handleTlp(TLP* packet) {
    packetHandler_->handleTlp(packet, memoryMap_.get());
}