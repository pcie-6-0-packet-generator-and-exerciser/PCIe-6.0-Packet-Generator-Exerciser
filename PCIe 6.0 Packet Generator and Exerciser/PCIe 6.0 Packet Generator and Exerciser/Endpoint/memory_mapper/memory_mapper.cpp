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
    boost::dynamic_bitset<> middlePayload, lastDoubleWord , updatedLastDoubleWord, temp;

    if (requiredToRead > 2) {
        middlePayload = get_bits(dataPayload, 1 * 32, requiredToRead * 32 - 1 * 32);
        lastDoubleWord = get_bits(dataPayload, (requiredToRead - 1 ) * 32 , requiredToRead * 32);
        int onesCounter2 = 0;
        updatedLastDoubleWord = lastDoubleWord;

        for (int i = 0; i < 4; i++) {
            if (lastByteEnable[i] == 1) {
                onesCounter2++;
            }
        }
        updatedLastDoubleWord.resize(onesCounter2 * 8);
        //temp.resize(onesCounter2 * 8);
        for (size_t i = 0; i < 4; i++) {
			// for each bit in the last byte enable
            if (lastByteEnable[i] == 1) {
                updatedLastDoubleWord |= ((get_bits(lastDoubleWord, i * 8, (i * 8) + 7)) << (i*8));
				//temp = temp << (i * 8);
				//newPayload = newPayload | temp;
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
    // 1101 // 24 bits

    updatedFirstDoubleWord.resize(onesCounter * 8); // 24 bits
    //temp.resize(onesCounter * 8); // 24bits

    for (size_t i = 0; i < firstByteEnable.size(); i++) {
        // for each bit in the first byte enable
        if (firstByteEnable[i] == 1) {
            temp = get_bits(firstDoubleWord, i * 8, (i * 8) + 7);
            temp.resize(updatedFirstDoubleWord.size());
            updatedFirstDoubleWord |= (temp << (i * 8));
            //temp = temp << (8);   //          11110000
            //updatedFirstDoubleWord = updatedFirstDoubleWord | temp;
        }
    }

    int totalSize = updatedFirstDoubleWord.size() + middlePayload.size() + updatedLastDoubleWord.size();

    boost::dynamic_bitset<> resultPayload(totalSize);
    updatedFirstDoubleWord.resize(totalSize);
    middlePayload.resize(totalSize);
    updatedLastDoubleWord.resize(totalSize);

    resultPayload |= (updatedLastDoubleWord << (totalSize - updatedLastDoubleWord.size())) ;
    resultPayload |= (middlePayload << (updatedFirstDoubleWord.size()));
    resultPayload |= updatedFirstDoubleWord;

    return resultPayload;
}




// int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4>lastDWBE
void MemoryMap::write(uint64_t address, long long requiredDataLengthToWrite, boost::dynamic_bitset<> payload, std::bitset<4> firstByteEnable, std::bitset<4> lastByteEnable) 
{ 
    
    int writeIndex = address * 32;
    int dataTobeWrittenIndex = 0;
    // determine exactly the data to be written according to the byte enables 
    boost::dynamic_bitset<> dataToBeWritten = payload;

    // first byte enable
    for (size_t i = 0; i < firstByteEnable.size(); i++) {
		// for each bit in the first byte enable
        if (firstByteEnable[i] == 1) {

            for (int j = 0; j < 8; j++) {
				memory[writeIndex] = dataToBeWritten[i * 8 + j];
				writeIndex++;
                dataTobeWrittenIndex++;
			}
        }
        else {
            dataTobeWrittenIndex += 8;
        }
	}
    while (writeIndex < ((address + requiredDataLengthToWrite) * 32) - 32 ) {
        memory[writeIndex + address * 32] = dataToBeWritten[dataTobeWrittenIndex];
    }
	// last byte enable
    for (size_t i = 0; i < lastByteEnable.size(); i++) {
        if(dataTobeWrittenIndex >= dataToBeWritten.size())
			break;
		// for each bit in the last byte enable
        if (lastByteEnable[i] == 1) {
            for (int j = 0; j < 8; j++) {
                memory[writeIndex] = dataToBeWritten[i * 8 + j + dataTobeWrittenIndex];
                writeIndex++;
                dataTobeWrittenIndex++;
            }
        }
        else {
            dataTobeWrittenIndex += 8;
        }
	}

}

