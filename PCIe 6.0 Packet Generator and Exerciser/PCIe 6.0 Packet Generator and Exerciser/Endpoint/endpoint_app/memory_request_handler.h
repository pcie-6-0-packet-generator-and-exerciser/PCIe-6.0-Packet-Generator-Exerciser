#pragma once
#include "../memory_mapper/memory_mapper.h"
#include "../../utils/tlp.h"

class MemoryRequestHandler {

private:
    /* They are shared (not unique) because they will be passed functions so that they can visit our Configuration Space and
       PCIE Capability classes, and they aren't weak because they are owned by this class, so their life time should
       be only end when the class's life time ends. */
    MemoryMap* memoryMap;

public:
    MemoryRequestHandler(MemoryMap* memoryMap);
    TLP* handleMemoryRead(TLP* tlp, TLPType type);
    void handleMemoryWrite(TLP* tlp, TLPType type);
};


