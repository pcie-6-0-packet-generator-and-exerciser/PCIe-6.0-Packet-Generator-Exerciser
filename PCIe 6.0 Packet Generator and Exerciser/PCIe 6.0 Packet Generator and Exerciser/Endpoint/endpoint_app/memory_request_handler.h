#pragma once
#include "../memory_mapper/memory_mapper.h"
#include "../../utils/tlp.h"

class MemoryRequestHandler {
public:
    virtual ~MemoryRequestHandler() {}
    virtual TLP handleTlp(TLP* packet) = 0;
    virtual void setMemoryMap(MemoryMap* memoryMap) = 0;
};


