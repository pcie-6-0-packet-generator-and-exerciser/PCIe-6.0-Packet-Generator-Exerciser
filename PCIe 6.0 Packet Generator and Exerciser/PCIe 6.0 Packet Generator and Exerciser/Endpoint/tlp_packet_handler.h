#pragma once

#include "../utils/tlp.h"
#include "memory_map.h"
#include "configuration_space_class/configuration_space.h"

class TlpPacketHandler {
public:
    virtual ~TlpPacketHandler() {}
    virtual void handleTlp(TLP packet) = 0;
    virtual void setMemoryMap(MemoryMap* memoryMap) = 0;
    virtual void setConfigurationSpace(ConfigurationSpace* configurationSpace) = 0;
};
