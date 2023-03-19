#pragma once

class MemoryRequestHandler {
    public:
        virtual ~MemoryRequestHandler() {}
        virtual TLP handleTlp(TLP* packet, MemoryMap* memoryMap) = 0;
};
