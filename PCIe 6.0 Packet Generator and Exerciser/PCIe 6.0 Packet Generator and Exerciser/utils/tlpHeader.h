#pragma once
#include "ohc.h";
#include "non_header_base.h";
#include <bitset>
#include <string>
#include <vector>

using namespace std;

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
	vector<OHC> OHCVector;
	NonHeaderBase *nonBase;

	string getBitRep() const;

};

