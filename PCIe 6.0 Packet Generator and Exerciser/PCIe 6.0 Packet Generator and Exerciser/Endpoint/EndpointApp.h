#pragma once

#include <cstdint>
#include <vector>
#include "PCIeController.h"
#include "MemoryMap.h"
#include "ConfigurationSpace.h"

class EndpointApp {
public:
    EndpointApp(PCIeController* controller, MemoryMap* memoryMap, ConfigurationSpace* configSpace) :
        controller_(controller),
        memoryMap_(memoryMap),
        configSpace_(configSpace) {}

    ~EndpointApp() {};

    void receiveTlpPacket(TlpPacket packet);

private:
    PCIeController* controller_;
    MemoryMap* memoryMap_;
    ConfigurationSpace* configSpace_;
};
