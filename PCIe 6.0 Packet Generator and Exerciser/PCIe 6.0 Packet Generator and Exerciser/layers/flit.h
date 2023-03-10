#pragma once
#include "boost/dynamic_bitset.hpp"

class Flit {
public:
	// Public data members
	int firstHalfTLPCount = 0;
	int secondHalfTLPCount = 0;
	boost::dynamic_bitset<> TLPPayload = boost::dynamic_bitset<>(236 * 8);
	boost::dynamic_bitset<> DLLPPayload = boost::dynamic_bitset<>(6 * 8);
	boost::dynamic_bitset<> CRCPayload = boost::dynamic_bitset<>(8 * 8);
	boost::dynamic_bitset<> ECCPayload = boost::dynamic_bitset<>(6 * 8);
};
