#pragma once
#include <memory>
#include "tlp_packet_handler.h"

class PcieController {
public:
    PcieController();
    void setPacketHandler(TlpPacketHandler* handler);
    void handleTlp(TLP packet);
    void handleCompletion(TLP packet);
private:
    std::unique_ptr<MemoryMap> memoryMap_;
    TlpPacketHandler* packetHandler_;
};