#include "memory_controller.h"

MemoryController::MemoryController(MemoryMap* memoryMap)
    : memoryMap_(memoryMap) ,packetHandler_(nullptr)
{

}


void MemoryController::setPacketHandler(MemoryRequestHandler* handler) {
    packetHandler_ = handler;
}

// get the packet from the endpoint app and pass it to the packet handler
TLP MemoryController::handleTlp(TLP* packet) {
    return packetHandler_->handleTlp(packet, memoryMap_.get());
}