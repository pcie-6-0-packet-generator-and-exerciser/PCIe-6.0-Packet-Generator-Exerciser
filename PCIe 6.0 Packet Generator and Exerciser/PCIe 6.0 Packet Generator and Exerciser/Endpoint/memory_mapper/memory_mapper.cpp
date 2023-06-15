#include "memory_mapper.h"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <bitset>


MemoryMap* MemoryMap::memoryMap = nullptr;

MemoryMap* MemoryMap::constructMemoryMap() {
	if (memoryMap == nullptr)
		memoryMap = new MemoryMap();
	return memoryMap;
}

MemoryMap::MemoryMap()
{
	// Initialize the memory map
	// 1 GB of memory
	memory = boost::dynamic_bitset<>(1024 * 1024 * 1024);
}

boost::dynamic_bitset<> MemoryMap::read(uint64_t address, boost::dynamic_bitset<> requiredToRead) {
	

    // we can shift the memory map to the right by the address
	// and then perform AND operation with the requiredToRead bitset
	// to extract the data payload

	boost::dynamic_bitset<> dataPayload = memory >> address * 32;
	dataPayload.resize(requiredToRead.size());
    // Use requiredToReadBitset to perform OR operation with the memory map
	dataPayload |= requiredToRead;

    return dataPayload;

}


bool MemoryMap::write(uint64_t address, boost::dynamic_bitset<> requiredBytesToWriteAt, boost::dynamic_bitset<> dataToBeWritten) {
    size_t startBit = address * 32;
    size_t endBit = startBit + (requiredBytesToWriteAt.size());

    boost::dynamic_bitset<> dataPayload = memory;

    // Preserve the existing memory data outside the write range
    for (size_t i = startBit; i < endBit; i++) {
        if (requiredBytesToWriteAt[i] == 0) {
            dataPayload[i] = memory[i];
        }
    }

    // Update the dataPayload with the new values to be written
    size_t dataIndex = 0;
    for (size_t i = startBit; i < endBit; i++) {
        if (requiredBytesToWriteAt[dataIndex] == 1) {
            dataPayload[i] = dataToBeWritten[dataIndex];
            dataIndex++;
        }
    }

    memory = dataPayload;
    return true;
}

