#include "memory_controller.h"
#include "../memory_mapper/memory_mapper.h"
#include "../memory_handlers/memory_read_handler.cpp"
#include "../memory_handlers/memory_write_handler.cpp"

MemoryController::MemoryController(std::unique_ptr<MemoryMap> memoryMap)
    : memoryMap_(std::move(memoryMap)), packetHandler_(nullptr)
{
}

void MemoryController::setPacketHandler(std::unique_ptr<MemoryRequestHandler> handler)
{
    packetHandler_ = std::move(handler);
}

TLP MemoryController::handleMemoryReadRequests(TLP packet)
{
    if (packet.header->TLPtype == TLPType::MemRead32 || packet.header->TLPtype == TLPType::MemRead64)
    {
        auto readHandler = std::make_unique<MemoryReadHandler>();
        readHandler->setMemoryMap(memoryMap_.get());
        packetHandler_ = std::move(readHandler);
        return packetHandler_->handleMemoryRead(&packet, packet.header->TLPtype);
    }
    else
    {
        // Handle unsupported TLP types
        return TLP();
    }
}

void MemoryController::handleMemoryWriteRequests(TLP packet) {
    if (packet.header->TLPtype == TLPType::MemWrite32 || packet.header->TLPtype == TLPType::MemWrite64)
    {
        auto writeHandler = std::make_unique<MemoryWriteHandler>();
        writeHandler->setMemoryMap(memoryMap_.get());
        packetHandler_ = std::move(writeHandler);
        return packetHandler_->handleMemoryWrite(&packet, packet.header->TLPtype);
    }

}