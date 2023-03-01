#pragma once
#include "tlp_header.h"
#include "dllp.h"
class TLP {
public:
	int headerConsumption;
	int dataConsumption;
	TLPHeader header;
	Dllp::CreditType creditConsumedType;
	boost::dynamic_bitset<> dataPayload( TLPHeader::lengthInDoubleWord * 32 );
	int getTotalLength();
	boost::dynamic_bitset<> getBitRep() const;

};