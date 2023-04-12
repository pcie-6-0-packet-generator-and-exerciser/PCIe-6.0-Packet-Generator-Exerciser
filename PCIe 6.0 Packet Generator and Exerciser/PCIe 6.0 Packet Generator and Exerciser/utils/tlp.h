#pragma once
#include "tlp_header.h"
#include "dllp.h"
#include <cmath>
#include<QString>
#define FC_UNIT_SIZE 4

QString TLPenumToString(TLPType value);

class TLP {
public:
	int headerConsumption;
	int dataConsumption;
	TLPHeader* header;
	Dllp::CreditType creditConsumedType;
	boost::dynamic_bitset<> dataPayload = boost::dynamic_bitset<>(header->lengthInDoubleWord * 32);
	int getTotalLength();
	boost::dynamic_bitset<> getBitRep();

	TLP() {
		// default constructor of TLPHeader
		// should initialize all fields to 0, OHC vector to empty, and nonBase to Null
		this->header = new TLPHeader();
		this->dataPayload;
		this->creditConsumedType = Dllp::CreditType::P;
		this->headerConsumption = 0;
		this->dataConsumption = 0;
	}
	static TLP createMemRead32Tlp(int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4> lastDWBE);
	static TLP createMemWrite32Tlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4>lastDWBE);
	static TLP createMemRead64Tlp(int requesterId, int tag, long long address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE);
	static TLP createMemWrite64Tlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, long long address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE);
	static TLP createConfigRead0Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment);
	static TLP createConfigWrite0Tlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment);
	static TLP createConfigRead1Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment);
	static TLP createConfigWrite1Tlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment);
	static TLP createCplTlp(int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddress, OHCA5::CPLStatus cplStatus);
	static TLP createCplDTlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddress, OHCA5::CPLStatus cplStatus);
	static TLP createVendorMsgTlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int messageCode, int destinationSegment);

};