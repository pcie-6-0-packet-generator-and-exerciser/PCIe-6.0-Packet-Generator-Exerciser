#pragma once
//#include "OHC.h";
//#include "NonHeaderBase.h";
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
	TLPType TLPType_;
	int TC;
	int length;
	std::vector<OHC> OHCs;
	NonHeaderBase nonBase;

	void setLength(int newLength);
};
