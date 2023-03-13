#include "memory_map.h"

MemoryMap::MemoryMap(uint64_t hostMemorySize, uint64_t deviceMemorySize)
    : hostMemorySize_(hostMemorySize), deviceMemorySize_(deviceMemorySize)
{
    // Resize host memory to specified size
    hostMemory_.resize(hostMemorySize_ / 4);

    // Resize device memory to specified size
    deviceMemory_.resize(deviceMemorySize_ / 4);
}

bool MemoryMap::read(uint64_t address, uint32_t* data)
{
    // Check if address is in host memory range
    if (address < hostMemorySize_) {
        *data = hostMemory_[address / 4];
        return true;
    }
    // Check if address is in device memory range
    else if (address >= 0x80000000 && address < (0x80000000 + deviceMemorySize_)) {
        *data = deviceMemory_[(address - 0x80000000) / 4];
        return true;
    }
    // Address is out of range
    else {
        return false;
    }
}

bool MemoryMap::write(uint64_t address, uint32_t data)
{
    // Check if address is in host memory range
    if (address < hostMemorySize_) {
        hostMemory_[address / 4] = data;
        return true;
    }
    // Check if address is in device memory range
    else if (address >= 0x80000000 && address < (0x80000000 + deviceMemorySize_)) {
        deviceMemory_[(address - 0x80000000) / 4] = data;
        return true;
    }
    // Address is out of range
    else {
        return false;
    }
}

boost::dynamic_bitset<> MemoryMap::readBlock(uint64_t address, uint64_t length)
{
    // Initialize empty dynamic bitset for result
    boost::dynamic_bitset<> result;

    // Check if address is in host memory range
    if (address < hostMemorySize_) {
        // Calculate end address
        uint64_t endAddress = address + length;

        // Check if end address is within host memory range
        if (endAddress <= hostMemorySize_) {
            // Resize result bitset to specified length
            result.resize(length * 8);

            // Copy data from host memory to bitset
            for (uint64_t i = 0; i < length; i++) {
                uint32_t data = hostMemory_[(address / 4) + i];
                for (int j = 0; j < 4; j++) {
                    result[(i * 8) + (3 - j)] = (data >> (j * 8)) & 0xff;
                }
            }

            return result;
        }
        // Block extends beyond host memory range
        else {
            return boost::dynamic_bitset<>();
        }
    }
    // Check if address is in device memory range
    else if (address >= 0x80000000 && address < (0x80000000 + deviceMemorySize_)) {
        // Calculate end address
        uint64_t endAddress = address + length;

        // Check if end address is within device memory range
        if (endAddress <= (0x80000000 + deviceMemorySize_)) {
            // Resize result bitset to specified length
            result.resize(length * 8);

            // Copy data from device memory to bitset
            for (uint64_t i = 0; i < length; i++) {
                uint32_t data = deviceMemory_[(address - 0x80000000) / 4 + i];
                for (int j = 0; j < 4; j++) {
                    result[(i * 8) + (3 - j)] = (data >> (j * 8)) & 0xff;
                }
            }

            return result;
        }
        // Block extends beyond device memory range
        else {
            return boost::dynamic_bitset<>();
        }
    }
    // Address is out of range
    else {
        return boost::dynamic_bitset<>();
    }
}

bool MemoryMap::writeBlock(uint64_t address, const boost::dynamic_bitset<>& data)
{
    uint64_t length = data.size() / 8; // Calculate the length in bytes

    // Check if address is in host memory range
    if (address < hostMemorySize_) {
        // Calculate end address
        uint64_t endAddress = address + length;

        // Check if end address is within host memory range
        if (endAddress <= hostMemorySize_) {
            // Copy data from bitset to host memory
            for (uint64_t i = 0; i < length; i++) {
                uint32_t word = 0;
                for (int j = 0; j < 4; j++) {
                    word |= data[(i * 8) + (3 - j)] << (j * 8);
                }
                hostMemory_[(address / 4) + i] = word;
            }

            return true;
        }
        // Block extends beyond host memory range
        else {
            return false;
        }
    }
    // Check if address is in device memory range
    else if (address >= 0x80000000 && address < (0x80000000 + deviceMemorySize_)) {
        // Calculate end address
        uint64_t endAddress = address + length;

        // Check if end address is within device memory range
        if (endAddress <= (0x80000000 + deviceMemorySize_)) {
            // Copy data from bitset to device memory
            for (uint64_t i = 0; i < length; i++) {
                uint32_t word = 0;
                for (int j = 0; j < 4; j++) {
                    word |= data[(i * 8) + (3 - j)] << (j * 8);
                }
                deviceMemory_[(address - 0x80000000) / 4 + i] = word;
            }

            return true;
        }
        // Block extends beyond device memory range
        else {
            return false;
        }
    }
    // Address is out of range
    else {
        return false;
    }
}
