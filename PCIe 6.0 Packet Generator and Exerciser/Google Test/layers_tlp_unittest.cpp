#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/utils/tlp.h"

TEST(TLPGetBitRep, OHCA1firstDWBE) {
	OHCA1* ohc = new OHCA1(std::bitset<4>(), std::bitset<4>());
	for (int i = 0; i < 16; i++) {
		ohc->firstDWBE = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}