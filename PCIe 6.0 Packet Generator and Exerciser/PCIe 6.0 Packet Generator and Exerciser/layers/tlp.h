#pragma once
#include <bitset>
#include "../utils/dllp.h"
#define MAX_DATA_PAYLOAD_LENGTH 1024 * 32
#define FC_UNIT_SIZE 4

class Tlp {
public:
	TlpHeader header;
	std::bitset<MAX_DATA_PAYLOAD_LENGTH> dataPayload;
	Dllp::CreditType creditConsumedType;
	int headerConsumption;
	int dataConsumption;

	Tlp() {
		// default constructor of TlpHeader
		// should initialize all fields to 0, OHC vector to empty, and nonBase to Null
		this->header = TlpHeader();
		this->dataPayload = NULL;
		this->creditConsumedType = Dllp::CreditType::P;
		this->headerConsumption = 0;
		this->dataConsumption = 0;
	}

	static Tlp createMemRead32Tlp(int requesterId, int tag, int address, int  firstDWBE[4], int  lastDWBE[4]);
	static Tlp createMemWrite32Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int address, int  firstDWBE[4], int  lastDWBE[4]);
	static Tlp createMemRead64Tlp(int requesterId, int tag, long long address, int  firstDWBE[4], int  lastDWBE[4]);
	static Tlp createMemWrite64Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, long long address, int  firstDWBE[4], int  lastDWBE[4]);
	static Tlp createConfigRead0Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, int  firstDWBE[4], int  lastDWBE[4], int destinationSegment);
	static Tlp createConfigWrite0Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, int  firstDWBE[4], int  lastDWBE[4], int destinationSegment);
	static Tlp createConfigRead1Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, int  firstDWBE[4], int  lastDWBE[4], int destinationSegment);
	static Tlp createConfigWrite1Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, int  firstDWBE[4], int  lastDWBE[4], int destinationSegment);
	static Tlp createCplTlp(int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int lowerAddress, int destinationSegment, int completerSegment, int lowerAddressArr[2], Tlp::CplStatus cplStatus);
	static Tlp createCplDTlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int lowerAddress, int destinationSegment, int completerSegment, int lowerAddressArr[2], Tlp::CplStatus cplStatus);
	static Tlp createVendorMsgTlp(int dataPayloadLength, std::string dataPayload, int requesterId, int messageCode, int destinationSegment);
};
