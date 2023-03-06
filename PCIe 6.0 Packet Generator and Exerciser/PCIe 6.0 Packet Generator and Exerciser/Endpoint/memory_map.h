#pragma once

#include <cstdint>

class MemoryMap {
public:
    virtual ~MemoryMap() {}
    virtual void write(uint64_t address, const uint8_t* data, uint32_t length);
    virtual void read(uint64_t address, uint8_t* data, uint32_t length);
};
