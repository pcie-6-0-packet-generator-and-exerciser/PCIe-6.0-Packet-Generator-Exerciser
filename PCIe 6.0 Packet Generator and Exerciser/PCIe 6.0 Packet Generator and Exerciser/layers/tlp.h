#pragma once
#include <bitset>
#include "../utils/dllp.h"
#include "../utils/tlp_header.h"
#define MAX_DATA_PAYLOAD_LENGTH 1024 * 32
#define FC_UNIT_SIZE 4

class TLP {
public:
	TLPHeader header;
	boost::dynamic_bitset<> dataPayload;
	Dllp::CreditType creditConsumedType;
	int headerConsumption;
	int dataConsumption;

	TLP() {
		// default constructor of TLPHeader
		// should initialize all fields to 0, OHC vector to empty, and nonBase to Null
		this->header = TLPHeader();
		this->dataPayload;
		this->creditConsumedType = Dllp::CreditType::P;
		this->headerConsumption = 0;
		this->dataConsumption = 0;
	}

	static TLP createMemRead32Tlp(int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4> lastDWBE);
	static TLP createMemWrite32Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4>lastDWBE);
	static TLP createMemRead64Tlp(int requesterId, int tag, long long address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE);
	static TLP createMemWrite64Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, long long address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE);
	static TLP createConfigRead0Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment);
	static TLP createConfigWrite0Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment);
	static TLP createConfigRead1Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment);
	static TLP createConfigWrite1Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment);
	static TLP createCplTlp(int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddress, OHCA5::CPLStatus cplStatus);
	static TLP createCplDTlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddress, OHCA5::CPLStatus cplStatus);
	static TLP createVendorMsgTlp(int dataPayloadLength, std::string dataPayload, int requesterId, int messageCode, int destinationSegment);
};
