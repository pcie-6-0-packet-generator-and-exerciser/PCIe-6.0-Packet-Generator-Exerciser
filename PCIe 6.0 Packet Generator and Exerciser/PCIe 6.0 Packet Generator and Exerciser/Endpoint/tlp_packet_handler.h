#pragma once

#include "../utils/tlp.h"

class TlpPacketHandler {
public:
    virtual ~TlpPacketHandler() {}
    virtual void handleTlp(TLP packet) = 0;
};
