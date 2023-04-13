#pragma once
#include "../memory_mapper/memory_mapper.h"
#include "../../utils/tlp.h"

class MemoryRequestHandler {
public:
    virtual ~MemoryRequestHandler() {}
    virtual TLP handleMemoryRead(TLP* packet, TLPType packetType) = 0;
    virtual void handleMemoryWrite(TLP* packet, TLPType packetType) = 0;
    virtual void setMemoryMap(MemoryMap* memoryMap) = 0;
};


