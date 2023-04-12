#include "../memory_mapper/memory_mapper.h"
#include "../../utils/tlp.h"
#include "../endpoint_app/memory_request_handler.h"


class MemoryReadHandler : public MemoryRequestHandler {
public:
    void setMemoryMap(MemoryMap* memoryMap) override {
        memoryMap_ = memoryMap;
    }
    TLP handleMemoryRead(TLP* packet, TLPType packetType) override {
        // implementation for handling Memory Read TLPs
        TLP response;
        return response;
    }
    void handleMemoryWrite(TLP* packet, TLPType packetType) override {

    }
private:
    MemoryMap* memoryMap_;
};