#pragma once

#include <memory>
#include <vector>
#include "./controller_class/configuration_controller.h"
#include "memory_map.h"
#include "../utils/tlp.h"
#include "memory_controller.h"

class EndpointApp {
public:
    EndpointApp();
    void receivePacket(TLP* packet);
    void sendPacket(TLP packet);
private:
    // Add BAR variables
    uint64_t prefetchableBar0_;
    uint32_t nonPrefetchableBar2_;
    uint16_t ioBar3_;
    std::unique_ptr<MemoryController> memoryController_;
    std::unique_ptr<ConfigurationController> configurationController_;
    std::unique_ptr<MemoryMap> memoryMap_;
};