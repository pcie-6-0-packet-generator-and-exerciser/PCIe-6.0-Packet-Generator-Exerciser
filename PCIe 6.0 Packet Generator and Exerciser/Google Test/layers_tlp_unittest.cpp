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

TEST(TLPGetBitRep, OHCA1lastDWBE) {
	OHCA1* ohc = new OHCA1(std::bitset<4>(), std::bitset<4>());
	for (int i = 0; i < 16; i++) {
		ohc->lastDWBE = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(4));
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA1FullPacket) {
	OHCA1* ohc = new OHCA1(std::bitset<4>(9), std::bitset<4>(7));
	ohc->firstDWBE = 9;
	ohc->lastDWBE = 7;
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	EXPECT_EQ(bitRep.to_ulong(), 0x79);
}

TEST(TLPGetBitRep, OHCA3firstDWBE) {
	OHCA3* ohc = new OHCA3(std::bitset<4>(), std::bitset<4>(), 0);
	for (int i = 0; i < 16; i++) {
		ohc->firstDWBE = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA3lastDWBE) {
	OHCA3* ohc = new OHCA3(std::bitset<4>(), std::bitset<4>(), 0);
	for (int i = 0; i < 16; i++) {
		ohc->lastDWBE = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(4));
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA3destinationSegment) {
	OHCA3* ohc = new OHCA3(std::bitset<4>(), std::bitset<4>(), 0);
	for (int i = 0; i < 256; i++) {
		ohc->destinationSegment = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(24));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA3FullPacket) {
	OHCA3* ohc = new OHCA3(std::bitset<4>(9), std::bitset<4>(7), 186);
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	EXPECT_EQ(bitRep.to_ulong(), 0xBA000079);
}

TEST(TLPGetBitRep, OHCA4destinationSegment) {
	OHCA4* ohc = new OHCA4(0);
	for (int i = 0; i < 256; i++) {
		ohc->destinationSegment = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(24));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA4FullPacket) {
	OHCA4* ohc = new OHCA4(186);
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	EXPECT_EQ(bitRep.to_ulong(), 0xBA000000);
}

TEST(TLPGetBitRep, OHCA5cplStatus) {
	OHCA5* ohc = new OHCA5(0, 0, std::bitset<2>(), OHCA5::CPLStatus::True);
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	bitRep.resize(3);
	EXPECT_EQ(bitRep.to_ulong(), 1);
	ohc->CPLStatusEnum = OHCA5::CPLStatus::False;
	bitRep = ohc->getBitRep();
	bitRep.resize(3);
	EXPECT_EQ(bitRep.to_ulong(), 0);
}

TEST(TLPGetBitRep, OHCA5lowerAddress) {
	OHCA5* ohc = new OHCA5(0, 0, std::bitset<2>(), OHCA5::CPLStatus::True);
	for (int i = 0; i < 4; i++) {
		ohc->lowerAddress = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(3));
		bitRep.resize(2);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA5completerSegment) {
	OHCA5* ohc = new OHCA5(0, 0, std::bitset<2>(), OHCA5::CPLStatus::True);
	for (int i = 0; i < 256; i++) {
		ohc->completerSegment = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(16));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA5destinationSegment) {
	OHCA5* ohc = new OHCA5(0, 0, std::bitset<2>(), OHCA5::CPLStatus::True);
	for (int i = 0; i < 256; i++) {
		ohc->destinationSegment = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(24));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA5FullPacket) {
	OHCA5* ohc = new OHCA5(91, 249, std::bitset<2>(1), OHCA5::CPLStatus::True);
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	EXPECT_EQ(bitRep.to_ulong(), 0x5BF90009);
}
