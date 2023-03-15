#pragma once

#include "../utils/tlp.h"

class MemoryMap;

class MemoryRequestHandler {
public:
    virtual ~MemoryRequestHandler() {}
    virtual TLP handleTlp(TLP* packet, MemoryMap* memoryMap) = 0;
};