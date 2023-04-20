#include "../memory_mapper/memory_mapper.h"
#include "../../utils/tlp.h"
#include "../endpoint_app/memory_request_handler.h"

using namespace boost;


class MemoryReadHandler : public MemoryRequestHandler {
public:

    void setMemoryMap(MemoryMap* memoryMap) override {
        memoryMap_ = memoryMap;
    }

    TLP handleMemoryRead(TLP* packet, TLPType packetType) override {

        uint32_t address = 0;

        auto firstDWenableBytes = dynamic_cast<OHCA1*>(packet->header->OHCVector[0])->firstDWBE.to_ulong();
        auto lastDWenableBytes = dynamic_cast<OHCA1*>(packet->header->OHCVector[0])->lastDWBE.to_ulong();

        // Calculate the start and end indices of the enabled portion of the data payload
        int startIndex = firstDWenableBytes * 4;
        int endIndex = (lastDWenableBytes + 1) * 4 - 1;

        // Extract the memory address from the packet header
        if (packetType == TLPType::MemRead32) {
            address = dynamic_cast<AddressRouting32Bit*>(packet->header->nonBase)->address;
        }
        else if (packetType == TLPType::MemRead64) {
            address = dynamic_cast<AddressRouting64Bit*>(packet->header->nonBase)->address;
        }
        uint32_t* data_uint = 0;
        data_uint = memoryMap_->read(address, data_uint);
        dynamic_bitset<> data(32, *data_uint);

        for (int i = startIndex; i <= endIndex; i++) {
            // Extract the i-th bit from the data payload and add it to the data_uint
            data.set(static_cast<boost::dynamic_bitset<unsigned long, std::allocator<unsigned long>>::size_type>(i) - startIndex, data[i]);
        }

        // need to return the Completion TLP to be pushed into the Completion Queue in the Endpoint App Class
        TLP completionTLP;
        completionTLP.header = new TLPHeader();
        completionTLP.header->TLPtype = TLPType::CplD;
        completionTLP.header->nonBase = packet->header->nonBase;
        completionTLP.header->OHCVector = packet->header->OHCVector;
        completionTLP.dataPayload = data;

        return completionTLP;
    }


    void handleMemoryWrite(TLP* packet, TLPType packetType) override {

    }

private:
    MemoryMap* memoryMap_;

};