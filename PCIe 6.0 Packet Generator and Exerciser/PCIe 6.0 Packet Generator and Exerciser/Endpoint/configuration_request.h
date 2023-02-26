#pragma once

#ifndef CONFIG_REQUEST_H
#define CONFIG_REQUEST_H

#include <cstdint>

enum class ConfigAccessType {
	READ, WRITE
};

class ConfigRequest {
public:
	ConfigRequest(ConfigAccessType accessType, uint32_t offset, uint32_t length, uint8_t* data = nullptr) : 
		accessType_(accessType), offset_(offset), length_(length), data_(data) {}

	ConfigAccessType getAccessType() const { return accessType_; }
	uint32_t getOffset() const { return offset_; }
	uint32_t getLength() const { return length_; }
	uint8_t* getData() const { return data_; }

	private:
		ConfigAccessType accessType_;
		uint32_t offset_;
		uint32_t length_;
		uint8_t* data_;
};

#endif // !CONFIG_REQUEST_H

