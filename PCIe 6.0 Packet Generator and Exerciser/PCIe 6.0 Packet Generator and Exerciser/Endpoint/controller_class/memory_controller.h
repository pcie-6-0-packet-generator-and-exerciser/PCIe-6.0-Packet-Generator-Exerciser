#pragma once

#include <memory>
#include "../../utils/tlp.h"
#include "../endpoint_app/memory_request_handler.h"

class MemoryController {
public:
    explicit MemoryController(std::unique_ptr<MemoryMap> memoryMap);
    void setPacketHandler(std::unique_ptr<MemoryRequestHandler> handler);
    TLP handleTlp(TLP packet);

private:
    std::unique_ptr<MemoryMap> memoryMap_;
    std::unique_ptr<MemoryRequestHandler> packetHandler_;
};