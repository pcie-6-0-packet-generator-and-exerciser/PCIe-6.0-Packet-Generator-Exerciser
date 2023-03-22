#pragma once
#include <cstdint>
#include <vector>

class MemoryMap {
public:
    MemoryMap(uint64_t prefetchableBar0, uint32_t nonPrefetchableBar2, uint16_t ioBar3);
    bool read(uint64_t address, uint32_t* data);
    bool write(uint64_t address, uint32_t data);

    private:
        std::vector<uint32_t> prefetchableBar0_;
        std::vector<uint32_t> nonPrefetchableBar2_;
        std::vector<uint32_t> ioBar3_;
};