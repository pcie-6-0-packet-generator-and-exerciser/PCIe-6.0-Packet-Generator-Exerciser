#pragma once
#include "ohc.h";
#include "NonHeaderBase.h";
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
	int length;
	std::vector<OHC> OHCVector;
	NonHeaderBase nonBase;

	void setLength(int newLength);
};
