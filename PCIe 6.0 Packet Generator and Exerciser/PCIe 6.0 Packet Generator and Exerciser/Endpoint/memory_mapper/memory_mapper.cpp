#include "memory_mapper.h"

MemoryMap::MemoryMap(uint64_t prefetchableBar0, uint32_t nonPrefetchableBar2, uint16_t ioBar3)
	: prefetchableBar0_(prefetchableBar0 / sizeof(uint32_t)), nonPrefetchableBar2_(nonPrefetchableBar2 / sizeof(uint32_t)),
	ioBar3_(ioBar3 / sizeof(uint32_t)) {
	// Constructor implementation
}

uint32_t* MemoryMap::read(uint64_t address, uint32_t* data) {
	if (address < prefetchableBar0_.size()) {
		*data = prefetchableBar0_[address];
		return data;
	}
	else if (address >= nonPrefetchableBar2_.size() && address < nonPrefetchableBar2_.size() + prefetchableBar0_.size()) {
		*data = nonPrefetchableBar2_[address - nonPrefetchableBar2_.size()];
		return data;
	}
	else if (address >= ioBar3_.size() && address < ioBar3_.size() + prefetchableBar0_.size() + nonPrefetchableBar2_.size()) {
		// Handle I/O reads
		return data;
	}
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