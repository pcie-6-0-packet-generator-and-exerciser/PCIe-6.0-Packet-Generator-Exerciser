#include "memory_map.h"

MemoryMap::MemoryMap(uint64_t prefetchableBar0, uint32_t nonPrefetchableBar2, uint16_t ioBar3)
    : prefetchableBar0_(prefetchableBar0), nonPrefetchableBar2_(nonPrefetchableBar2), ioBar3_(ioBar3)
{

}

bool MemoryMap::read(uint64_t address, uint32_t* data)
{
    return true;
    // to be implemented 
}

bool MemoryMap::write(uint64_t address, uint32_t data)
{
    // to be implemented 
    return true;

}

boost::dynamic_bitset<> MemoryMap::readBlock(uint64_t address, uint64_t length)
{
    // Initialize empty dynamic bitset for result
     // to be implemented 
    boost::dynamic_bitset<> result;
    return result;
}

bool MemoryMap::writeBlock(uint64_t address, const boost::dynamic_bitset<>& data)
{
    // to be implemented 
    return true;
}
