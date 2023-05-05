#include "memory_mapper.h"

MemoryMap::MemoryMap(uint64_t prefetchableBar0Size, uint32_t nonPrefetchableBar2Size, uint16_t ioBar3Size)
	: prefetchableBar0_(prefetchableBar0Size), nonPrefetchableBar2_(nonPrefetchableBar2Size),
	ioBar3_(ioBar3Size) {
	// Constructor implementation
}

uint32_t MemoryMap::read(uint64_t address, uint32_t* data) {
	if (address < prefetchableBar0_.size()) {
		*data = prefetchableBar0_[address];
		return *data;
	}
	if (address >= prefetchableBar0_.size() && address < prefetchableBar0_.size() + nonPrefetchableBar2_.size()) {
		*data = nonPrefetchableBar2_[address - prefetchableBar0_.size()];
		return *data;
	}
	else if (address >= prefetchableBar0_.size() + nonPrefetchableBar2_.size() && address < prefetchableBar0_.size() + nonPrefetchableBar2_.size() + ioBar3_.size()) {
		// Handle I/O reads
		return 0;
	}
	// Return an error value if the address is out of range
	return 0xDEADBEEF;
}


bool MemoryMap::write(uint64_t address, uint32_t data) {
	if (address < prefetchableBar0_.size()) {
		prefetchableBar0_[address] = data;
		return true;
	}
	else if (address >= nonPrefetchableBar2_.size() && address < nonPrefetchableBar2_.size() + prefetchableBar0_.size()) {
		nonPrefetchableBar2_[address - nonPrefetchableBar2_.size()] = data;
		return true;
	}
	else if (address >= ioBar3_.size() && address < ioBar3_.size() + prefetchableBar0_.size() + nonPrefetchableBar2_.size()) {
		// Handle I/O writes (not supported in our scope)
		return false;
	}
	return false;
}