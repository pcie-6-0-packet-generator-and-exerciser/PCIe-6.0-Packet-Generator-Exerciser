#pragma once
#include "../memory_mapper/memory_mapper.h"
#include "../../utils/tlp.h"

class MemoryRequestHandler {
    public:
        virtual ~MemoryRequestHandler() {}
        virtual TLP handleTlp(TLP* packet, MemoryMap* memoryMap) = 0;
};
