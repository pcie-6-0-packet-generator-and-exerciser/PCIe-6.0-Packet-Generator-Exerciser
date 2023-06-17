#include "memory_mapper.h"
#include <boost/dynamic_bitset/dynamic_bitset.hpp>
#include <bitset>
#include "../../utils/bitset_utils.h"


MemoryMap* MemoryMap::memoryMap = nullptr;

MemoryMap* MemoryMap::constructMemoryMap() {
	if (memoryMap == nullptr)
		memoryMap = new MemoryMap();
	return memoryMap;
}

MemoryMap::MemoryMap()
{
	// Initialize the memory map
	// 1 GB of memory Set all the bits to 0 
	memory = boost::dynamic_bitset<>((1024 * 1024 * 1024), 0);
    
}

boost::dynamic_bitset<> MemoryMap::read(uint64_t address, long long requiredToRead , std::bitset<4> firstByteEnable, std::bitset<4> lastByteEnable) {
	

    // we can shift the memory map to the right by the address
	// and then perform AND operation with the requiredToRead bitset
	// to extract the data payload
    // requiredToRead = 1DW == 32 Bites
	boost::dynamic_bitset<> dataPayload = get_bits(memory, address * 32, ((address + requiredToRead) * 32) - 1);
    boost::dynamic_bitset<> newPayload, temp;

    if (requiredToRead > 2) {
        newPayload = get_bits(dataPayload, 1 * 32, requiredToRead * 32 - 1 * 32);
        boost::dynamic_bitset lastDoubleWord = get_bits(dataPayload, (requiredToRead - 1 ) * 32 , requiredToRead * 32);
        int onesCounter2 = 0;
        boost::dynamic_bitset updatedLastDoubleWord = lastDoubleWord;

        for (int i = 0; i < 4; i++) {
            if (lastByteEnable[i] == 1) {
                onesCounter2++;
            }
        }
        updatedLastDoubleWord.resize(onesCounter2 * 8);
        temp.resize(onesCounter2 * 8);
        for (size_t i = 0; i < 4; i++) {
			// for each bit in the last byte enable
            if (lastByteEnable[i] == 1) {
				temp = get_bits(lastDoubleWord, i * 8, (i * 8) + 7);
				temp = temp << (i * 8);
				newPayload = newPayload | temp;
			}
		}
    }

    boost::dynamic_bitset firstDoubleWord = get_bits(dataPayload, 0, 31); // first 32 bits
    boost::dynamic_bitset updatedFirstDoubleWord = firstDoubleWord;
    int onesCounter = 0;

    for (int i = 0; i < 4; i++) {
        if (firstByteEnable[i] == 1) {
			onesCounter++;
		}
	}

    updatedFirstDoubleWord.resize(onesCounter * 8);
    temp.resize(onesCounter * 8);

    for (size_t i = 0; i < firstByteEnable.size(); i++) {
        // for each bit in the first byte enable
        if (firstByteEnable[i] == 1) {
            temp = get_bits(firstDoubleWord, i * 8, (i * 8) + 7);
            temp = temp << (i * 8);
            updatedFirstDoubleWord = updatedFirstDoubleWord | temp;
        }
    }

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

