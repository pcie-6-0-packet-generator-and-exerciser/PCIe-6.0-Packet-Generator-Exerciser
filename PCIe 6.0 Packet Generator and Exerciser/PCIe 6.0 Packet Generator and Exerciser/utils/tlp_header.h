#pragma once
#include "ohc.h";
#include "non_header_base.h";
#include <bitset>
#include <string>
#include <vector>

enum class TLPType {
	MemRead32=3,
	MemWrite32=64,
	MemRead64=32,
	MemWrite64=96,
	Cpl=10,
	CpID=74,
	VendorMsg,
	ConfigRead0=4,
	ConfigWrite0=68,
	ConfigRead1=5,
	ConfigWrite1=69
};

class TLPHeader {
public:
	TLPType TLPtype;
	int TC;
	int lengthInDoubleWord;
	std::vector<OHC> OHCVector;
	NonHeaderBase* nonBase;
	int OHC;

	boost::dynamic_bitset<> getBitRep() const;

};
