#pragma once
#include "configuration_space.h"
#include "memory_map.h"
#include "endpoint_app.h"
#include "packet.h"
#include "memory_request.h"
#include "config_request.h"

class PCIeController {
public:
    PCIeController(ConfigurationSpace* configSpace, MemoryMap* memoryMap, EndpointApp* endpointApp);

    void sendPacket(Packet* packet);
    Packet* receivePacket();

    void handleMemoryRead(MemoryRequest* request);
    void handleMemoryWrite(MemoryRequest* request);

    void handleConfigRead(ConfigRequest* request);
    void handleConfigWrite(ConfigRequest* request);

private:
    ConfigurationSpace* configSpace_;
    MemoryMap* memoryMap_;
    EndpointApp* endpointApp_;
};

