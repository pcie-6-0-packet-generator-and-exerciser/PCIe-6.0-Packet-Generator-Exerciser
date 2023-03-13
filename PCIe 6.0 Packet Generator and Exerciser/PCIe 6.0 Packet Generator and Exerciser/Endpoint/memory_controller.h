#pragma once

#include <memory>
#include "memory_request_handler.h"
#include "memory_map.h"

class MemoryController {
public:
    MemoryController(std::unique_ptr<MemoryMap> memoryMap);
    void setPacketHandler(MemoryRequestHandler* handler);
    void handleTlp(TLP* packet);

private:
    std::unique_ptr<MemoryMap> memoryMap_;
    MemoryRequestHandler* packetHandler_;
};