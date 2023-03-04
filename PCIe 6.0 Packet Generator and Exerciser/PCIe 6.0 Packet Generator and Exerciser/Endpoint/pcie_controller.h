#pragma once
#include <unordered_map>
#include "configuration_space.h"
#include "memory_map.h"
#include "endpoint_app.h"
#include "packet.h"
#include "tlp_packet_handler.h"

class PCIeController {
public:
    PCIeController(ConfigurationSpace* configSpace, MemoryMap* memoryMap, EndpointApp* endpointApp);

    void sendPacket(Packet* packet);
    Packet* receivePacket();

private:
    std::unordered_map<uint8_t, TlpPacketHandler*> handlers_;
    ConfigurationSpace* configSpace_;
    MemoryMap* memoryMap_;
    EndpointApp* endpointApp_;
};


