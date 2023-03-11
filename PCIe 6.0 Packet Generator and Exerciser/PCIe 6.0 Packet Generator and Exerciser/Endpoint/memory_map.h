#pragma once

#include <cstdint>
#include <vector>
#include <boost/dynamic_bitset.hpp>

class MemoryMap {
public:
    MemoryMap(uint64_t hostMemorySize, uint64_t deviceMemorySize);

    bool read(uint64_t address, uint32_t* data);
    bool write(uint64_t address, uint32_t data);

    boost::dynamic_bitset<> readBlock(uint64_t address, uint64_t length);
    bool writeBlock(uint64_t address, const boost::dynamic_bitset<>& data);

private:
    std::vector<uint32_t> hostMemory_;
    std::vector<uint32_t> deviceMemory_;
    uint64_t hostMemorySize_;
    uint64_t deviceMemorySize_;
};
