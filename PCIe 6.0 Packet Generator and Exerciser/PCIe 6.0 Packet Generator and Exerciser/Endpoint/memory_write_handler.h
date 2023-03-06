#pragma once

#include "tlp_packet_handler.h"

class MemoryWriteHandler : public TlpPacketHandler {
public:
    void handleTlp(TLP packet) override;
};
