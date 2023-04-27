#include "../memory_mapper/memory_mapper.h"
#include "../../utils/tlp.h"
#include "../endpoint_app/memory_request_handler.h"
#include "../../utils/ohc.h"

using namespace boost;


class MemoryWriteHandler : public MemoryRequestHandler {
public:
    void setMemoryMap(MemoryMap* memoryMap) override {
        memoryMap_ = memoryMap;
    }

    void handleMemoryWrite(TLP* packet, TLPType packetType) override {
        uint32_t data_uint = 0;
        long long address = 0;

        bitset<4> firstDWenableBytes = dynamic_cast<OHCA1*>(packet->header->OHCVector[0])->firstDWBE;
        bitset<4> lastDWenableBytes = dynamic_cast<OHCA1*>(packet->header->OHCVector[0])->lastDWBE;

        // Convert the DWEN bitsets to integers
        int firstDWenable = static_cast<int>(firstDWenableBytes.to_ulong());
        int lastDWenable = static_cast<int>(lastDWenableBytes.to_ulong());

        // Calculate the start and end indices of the enabled portion of the data payload
        int startIndex = firstDWenable * 4;
        int endIndex = (lastDWenable + 1) * 4 - 1;

        // Extract the data payload from the packet based on the start and end indices
        boost::dynamic_bitset<> data = packet->dataPayload;

        // Iterate over the range of indices between the startIndex and endIndex
        for (int i = startIndex; i <= endIndex; i++) {
            // Extract the i-th bit from the data payload and add it to the data_uint
            data_uint |= (data[i] << (i - startIndex));
        }

        // Extract the memory address from the packet header
        if (packetType == TLPType::MemWrite32) {
            address = dynamic_cast<AddressRouting32Bit*>(packet->header->nonBase)->address;
        }
        else if (packetType == TLPType::MemWrite64) {
            address = dynamic_cast<AddressRouting64Bit*>(packet->header->nonBase)->address;
        }

        memoryMap_->write(address, data_uint);
    }
    TLP* handleMemoryRead(TLP* packet, TLPType packetType) override {
        return 0;
    }

private:
    MemoryMap* memoryMap_;
};
