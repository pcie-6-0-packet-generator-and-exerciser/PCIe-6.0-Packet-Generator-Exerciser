#include "memory_request.h"

MemoryRequest::MemoryRequest(MemoryAccessType accessType, uint64_t address, uint32_t length, uint8_t* data) : 
	accessType_(accessType), address_(address), length_(length), data_(data) {}


MemoryAccessType MemoryRequest::getAccessType() const { return accessType_; }

uint64_t MemoryRequest::getAddress() const { return address_; }

uint32_t MemoryRequest::getLength() const { return length_; }

uint8_t* MemoryRequest::getData() const { return data_; }

