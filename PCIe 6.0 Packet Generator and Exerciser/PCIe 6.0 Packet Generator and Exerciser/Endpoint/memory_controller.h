#pragma once

#include <memory>
#include "memory_request_handler.h"
#include "memory_map.h"

class MemoryController {
public:
    MemoryController(MemoryMap* memoryMap);
    void setPacketHandler(MemoryRequestHandler* handler);
    TLP handleTlp(TLP* packet);

private:
    std::unique_ptr<MemoryMap> memoryMap_;
    MemoryRequestHandler* packetHandler_;
};