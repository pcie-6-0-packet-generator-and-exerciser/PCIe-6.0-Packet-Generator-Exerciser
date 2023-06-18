#pragma once
#include <cstdint>
#include <vector>
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <bitset>


class MemoryMap {
public:
    static MemoryMap* constructMemoryMap();
    boost::dynamic_bitset<> read(uint64_t address, long long requiredToRead, std::bitset<4> firstByteEnable, std::bitset<4> lastByteEnable);
    void write(uint64_t address, long long requiredDataLengthToWrite, boost::dynamic_bitset<> payload, std::bitset<4> firstByteEnable, std::bitset<4> lastByteEnable);

    private:
        static MemoryMap* memoryMap;
        MemoryMap();          
        boost::dynamic_bitset<> memory;

};