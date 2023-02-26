#ifndef MEMORY_REQUEST_H
#define MEMPORY_REQUEST_H

#include <cstdint>

enum class MemoryAccessType {
	READ, WRITE
};

class MemoryRequest {
public:
	MemoryRequest(MemoryAccessType accessType, uint64_t address, uint32_t length, uint8_t* data = nullptr) : 
		accessType_(accessType), address_(address), length_(length), data_(data) {}
	MemoryAccessType getAccessType() const { return accessType_; }
	uint64_t getAddress() const { return address_; }
	uint32_t getLength() const { return length_; }
	uint8_t* getData() const { return data_; }
	private:
		MemoryAccessType accessType_;
		uint64_t address_;
		uint32_t length_;
		uint8_t* data_;
};


#endif // MEMORY_REQUEST_H

