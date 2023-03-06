#pragma once

#include <memory>
#include <vector>
#include "./configuration_space_class/configuration_space.h"
#include "pcie_controller.h"
#include "tlp_packet_handler.h"
#include "memory_map.h"
#include "../utils/tlp.h"

class EndpointApp {
public:
    EndpointApp();
    //~EndpointApp();
    void receivePacket(TLP packet);
    void sendPacket(TLP packet);
private:
    std::unique_ptr<PcieController> pcieController_;
    std::unique_ptr<MemoryMap> memoryMap_;
    std::unique_ptr<ConfigurationSpace> configurationSpace_;
};