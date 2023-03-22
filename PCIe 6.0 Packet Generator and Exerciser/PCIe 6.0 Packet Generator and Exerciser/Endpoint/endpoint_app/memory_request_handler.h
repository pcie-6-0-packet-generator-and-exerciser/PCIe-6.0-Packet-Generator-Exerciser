#pragma once
#include "../memory_mapper/memory_mapper.h"
#include "../../utils/tlp.h"

class MemoryRequestHandler {
public:
    virtual ~MemoryRequestHandler() {}
    virtual TLP handleTlp(TLP* packet) = 0;
    virtual void setMemoryMap(MemoryMap* memoryMap) = 0;
};

// those will be put in another separate files in another PR ......

class MemoryReadHandler : public MemoryRequestHandler {
public:
    void setMemoryMap(MemoryMap* memoryMap) override {
        memoryMap_ = memoryMap;
    }
    TLP handleTlp(TLP* packet) override {
        // implementation for handling Memory Read TLPs
        TLP response;
        return response;
    }
private:
    MemoryMap* memoryMap_;
};

class MemoryWriteHandler : public MemoryRequestHandler {
public:
    void setMemoryMap(MemoryMap* memoryMap) override {
        memoryMap_ = memoryMap;
    }
    TLP handleTlp(TLP* packet) override {
        // implementation for handling Memory Write TLPs
        TLP response;
        return response;
    }
private:
    MemoryMap* memoryMap_;
};
