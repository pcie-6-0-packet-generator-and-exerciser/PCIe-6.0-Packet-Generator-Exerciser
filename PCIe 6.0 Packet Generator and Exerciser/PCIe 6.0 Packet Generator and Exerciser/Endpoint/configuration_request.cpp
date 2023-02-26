#include "configuration_request.h"

ConfigRequest::	ConfigRequest(ConfigAccessType accessType, uint32_t offset, uint32_t length, uint8_t* data = nullptr) : 
	accessType_(accessType), offset_(offset), length_(length), data_(data) {}

ConfigAccessType ConfigRequest::getAccessType() const { return accessType_; }

uint32_t ConfigRequest::getOffset() const { return offset_; }

uint32_t ConfigRequest::getLength() const { return length_; }

uint8_t* ConfigRequest::getData() const { return data_; }
