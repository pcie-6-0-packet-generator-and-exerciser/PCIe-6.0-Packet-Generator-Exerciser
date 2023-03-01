#pragma once

#include <cstdint>
#include <vector>
#include "PCIeController.h"
#include "MemoryMap.h"
#include "ConfigurationSpace.h"
#include "MemoryRequest.h"
#include "ConfigurationRequest.h"

class EndpointApp {
public:
    EndpointApp() {};
    ~EndpointApp() {};

    void sendPacket(const uint8_t* data, uint32_t length);
    void receivePacket(uint8_t* data, uint32_t length);
    uint32_t handleMemoryRead(MemoryRequest* request);
    uint32_t handleMemoryWrite(MemoryRequest* request);
    uint32_t handleConfigRead(ConfigurationRequest* request);
    uint32_t handleConfigWrite(ConfigurationRequest* request);

private:
    PCIeController* controller_;
    MemoryMap* memoryMap_;
    ConfigurationSpace* configSpace_;
    std::vector<uint8_t> bar0Memory_;
    std::vector<uint8_t> bar1Memory_;
    std::vector<uint8_t> bar2Memory_;
    std::vector<uint8_t> bar3Memory_;
};
