#include "../endpoint_app/memory_request_handler.h"

using namespace boost;

MemoryRequestHandler::MemoryRequestHandler(MemoryMap* memoryMap) {
	this->memoryMap = memoryMap;
}

TLP* MemoryRequestHandler::handleMemoryRead(TLP* packet, TLPType packetType) {

    long long address = 0;
    int tag = 0;
    if (packetType == TLPType::MemRead32) {
        address = dynamic_cast<AddressRouting32Bit*>(packet->header->nonBase)->address;
        tag = dynamic_cast<AddressRouting32Bit*>(packet->header->nonBase)->tag;
    }
    else if (packetType == TLPType::MemRead64) {
        address = dynamic_cast<AddressRouting64Bit*>(packet->header->nonBase)->address;
        tag = dynamic_cast<AddressRouting64Bit*>(packet->header->nonBase)->tag;
    }
    int requesterId = packet->header->nonBase->requestID;
    int completerId = 0;
    long long dataPayloadLengthInDw = packet->header->lengthInDoubleWord == 0 ? 1024 : packet->header->lengthInDoubleWord;
    boost::dynamic_bitset<> dataPayloadLengthInDwBitset(dataPayloadLengthInDw * 32);
    // Set all bits in dataPayloadLengthInDwBitset to 1
    dataPayloadLengthInDwBitset.set();

    bitset<4> firstDWenableBytes = dynamic_cast<OHCA1*>(packet->header->OHCVector[0])->firstDWBE;
    boost::dynamic_bitset<> firstDWenableBytes32(dataPayloadLengthInDw * 32, firstDWenableBytes.to_ulong());
    bitset<4> lastDWenableBytes = dynamic_cast<OHCA1*>(packet->header->OHCVector[0])->lastDWBE;
    boost::dynamic_bitset<> lastDWenableBytes32(dataPayloadLengthInDw * 32, lastDWenableBytes.to_ulong());

    //for (long long i = 0; i < dataPayloadLengthInDw; i++) {
      //  if (firstDWenableBytes[i] == 0) {
        //    for (int j = 0; j < 8; j++) {
          //      dataPayloadLengthInDwBitset[i * 32 + j] = 0;
            //}
        //}
    //}

    //for (long long i = dataPayloadLengthInDw - 1; i >= 0; i--) {
      //  if (lastDWenableBytes[i] == 0) {
        //    for (int j = 0; j < 8; j++) {
          //      dataPayloadLengthInDwBitset[i * 32 + 31 - j] = 0;
            //}
        //}
    //}

    // Extract the data payload from the memory map
    boost::dynamic_bitset<> data = memoryMap->read(address, dataPayloadLengthInDw, firstDWenableBytes, lastDWenableBytes);

    
    // Extract the destination and completer segments
    int destinationSegment = 0;
    int completerSegment = 0;

    // lowerAddressOHC is a bitset of size 2 related to the FirstByteEnable bits
    std::bitset<2> lowerAddressOHC;
    std::bitset<5> lowerAddressHeaderBase;

    // Assign lower address based on firstDWenableBytes
    if (firstDWenableBytes == std::bitset<4>("0000")) {
        lowerAddressOHC = std::bitset<2>("00");
    }
    else if (firstDWenableBytes == std::bitset<4>("0001")) {
        lowerAddressOHC = std::bitset<2>("00");
    }
    else if (firstDWenableBytes == std::bitset<4>("0010")) {
        lowerAddressOHC = std::bitset<2>("01");
    }
    else if (firstDWenableBytes == std::bitset<4>("0100")) {
        lowerAddressOHC = std::bitset<2>("10");
    }
    else if (firstDWenableBytes == std::bitset<4>("1000")) {
        lowerAddressOHC = std::bitset<2>("11");
    }
    else {
        // Handle unsupported case
        // You can assign a default value or throw an exception, depending on your requirements
        lowerAddressOHC = std::bitset<2>("00");
    }

    TLP* completion = new TLP();
    // createCplDTlp() takes as parameters: int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddressOHC, std::bitset<5> lowerAddressHeaderBase, OHCA5::CPLStatus cplStatus)
    TLP* completion_packet = completion->createCplDTlp(
        dataPayloadLengthInDw, // dataPayloadLengthInDW
        data,// dataPayload
        tag, // tag
        completerId, // completerId
		0, // byteCount
		0, // busNumber
		0, // deviceNumber
		0, // functionNumber
        destinationSegment, // destinationSegment
        completerSegment, // completerSegment
        lowerAddressOHC,
        lowerAddressHeaderBase,
		OHCA5::CPLStatus::True // cplStatus
    );
    return completion_packet;
}





void MemoryRequestHandler::handleMemoryWrite(TLP* packet, TLPType packetType) {

    long long address = 0;

    long long dataPayloadLengthInDw = packet->header->lengthInDoubleWord == 0 ? 1024 : packet->header->lengthInDoubleWord;
    boost::dynamic_bitset<> dataPayloadLengthInDwBitset(dataPayloadLengthInDw * 32);
    dataPayloadLengthInDwBitset.set();

    bitset<4> firstDWenableBytes = dynamic_cast<OHCA1*>(packet->header->OHCVector[0])->firstDWBE;
    boost::dynamic_bitset<> firstDWenableBytes32(dataPayloadLengthInDw * 32, firstDWenableBytes.to_ulong());
    bitset<4> lastDWenableBytes = dynamic_cast<OHCA1*>(packet->header->OHCVector[0])->lastDWBE;
    boost::dynamic_bitset<> lastDWenableBytes32(dataPayloadLengthInDw * 32, lastDWenableBytes.to_ulong());

    for (long long i = 0; i < dataPayloadLengthInDw; i++) {
        if (firstDWenableBytes[i] == 0) {
            for (int j = 0; j < 8; j++) {
                dataPayloadLengthInDwBitset[i * 32 + j] = 0;
            }
        }
    }

    for (long long i = dataPayloadLengthInDw - 1; i >= 0; i--) {
        if (lastDWenableBytes[i] == 0) {
            for (int j = 0; j < 8; j++) {
                dataPayloadLengthInDwBitset[i * 32 + 31 - j] = 0;
            }
        }
    }

    // Extract the data payload from the packet based on the start and end indices
    boost::dynamic_bitset<> data = packet->dataPayload;

    // Extract the memory address from the packet header
    if (packetType == TLPType::MemWrite32) {
        address = dynamic_cast<AddressRouting32Bit*>(packet->header->nonBase)->address;
    }
    else if (packetType == TLPType::MemWrite64) {
        address = dynamic_cast<AddressRouting64Bit*>(packet->header->nonBase)->address;
    }
    else {
		// Handle unsupported case
		// You can assign a default value or throw an exception, depending on your requirements
		address = 0;
	}

    memoryMap->write(address, dataPayloadLengthInDwBitset, data);
}
