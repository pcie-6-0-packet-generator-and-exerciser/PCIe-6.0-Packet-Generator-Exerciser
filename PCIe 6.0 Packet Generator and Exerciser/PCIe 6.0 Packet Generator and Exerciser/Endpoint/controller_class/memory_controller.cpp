#include "memory_controller.h"
#include "../memory_mapper/memory_mapper.h"

MemoryController::MemoryController(std::unique_ptr<MemoryMap> memoryMap)
    : memoryMap_(std::move(memoryMap)), packetHandler_(nullptr)
{
    // constructor implementation
}

void MemoryController::setPacketHandler(std::unique_ptr<MemoryRequestHandler> handler)
{
    packetHandler_ = std::move(handler);
}

TLP MemoryController::handleTlp(TLP packet)
{
    return packetHandler_->handleTlp(&packet, memoryMap_.get());
}