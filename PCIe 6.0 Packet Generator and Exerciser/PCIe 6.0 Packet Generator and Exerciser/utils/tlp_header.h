#pragma once
#include "ohc.h";
#include "non_header_base.h";
#include <bitset>
#include <string>
#include <vector>

enum TLPType {
	MemRead32,
	MemWrite32,
	MemRead64,
	MemWrite64,
	Cpl,
	CpID,
	VendorMsg,
	ConfigRead0,
	ConfigWrite0,
	ConfigRead1,
	ConfigWrite1
};

class TLPHeader {
public:
	TLPType TLPtype;
	int TC;
	int lengthInDoubleWord;
	std::vector<OHC> OHCVector;
	NonHeaderBase* nonBase;
	int OHC;

	string getBitRep() const;

};
