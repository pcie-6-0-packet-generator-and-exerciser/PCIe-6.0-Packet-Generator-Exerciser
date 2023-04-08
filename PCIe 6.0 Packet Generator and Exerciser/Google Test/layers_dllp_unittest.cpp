#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/utils/dllp.h"
#include "boost/dynamic_bitset.hpp"

TEST(GetBitRep, InitFC1Type) {
	Dllp dllp;
	dllp.m_type = Dllp::DllpType::initFC1;
	boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 2);
	EXPECT_EQ(expected.to_ulong(), 1);
}

TEST(GetBitRep, InitFC2Type) {
	Dllp dllp;
	dllp.m_type = Dllp::DllpType::initFC2;
	boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 2);
	EXPECT_EQ(expected.to_ulong(), 3);
}

TEST(GetBitRep, UpdateFCType) {
	Dllp dllp;
	dllp.m_type = Dllp::DllpType::updateFC;
	boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 2);
	EXPECT_EQ(expected.to_ulong(), 2);
}

TEST(GetBitRep, PType) {
	Dllp dllp;
	dllp.m_creditType = Dllp::CreditType::P;
	boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 4);
	expected.resize(2);
	EXPECT_EQ(expected.to_ulong(), 0);
}

TEST(GetBitRep, NPType) {
	Dllp dllp;
	dllp.m_creditType = Dllp::CreditType::NP;
	boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 4);
	expected.resize(2);
	EXPECT_EQ(expected.to_ulong(), 1);
}

TEST(GetBitRep, CplType) {
	Dllp dllp;
	dllp.m_creditType = Dllp::CreditType::Cpl;
	boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 4);
	expected.resize(2);
	EXPECT_EQ(expected.to_ulong(), 2);
}

TEST(GetBitRep, DedicatedFlowControl) {
	Dllp dllp;
	dllp.shared = false;
	boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 5);
	expected.resize(1);
	EXPECT_EQ(expected.to_ulong(), 0);
}

TEST(GetBitRep, SharedFlowControl) {
	Dllp dllp;
	dllp.shared = true;
	boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 5);
	expected.resize(1);
	EXPECT_EQ(expected.to_ulong(), 1);
}

TEST(GetBitRep, VC) {
	Dllp dllp;
	for (int i = 0; i < 8; i++) {
		dllp.VC = i;
		boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 8);
		expected.resize(3);
		EXPECT_EQ(expected.to_ulong(), i);
	}
}

TEST(GetBitRep, HdrFC) {
	Dllp dllp;
	for (int i = 0; i < 256; i++) {
		dllp.HdrFC = i;
		boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 18);
		expected.resize(8);
		EXPECT_EQ(expected.to_ulong(), i);
	}
}

TEST(GetBitRep, DataFC) {
	Dllp dllp;
	for (int i = 0; i < 4096; i++) {
		dllp.DataFc = i;
		boost::dynamic_bitset<> expected = dllp.getBitRep();
		expected.resize(12);
		EXPECT_EQ(expected.to_ulong(), i);
	}
}

TEST(GetBitRep, HdrScale) {
	Dllp dllp;
	for (int i = 0; i < 3; i++) {
		dllp.HdrScale = i;
		boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 10);
		expected.resize(2);
		EXPECT_EQ(expected.to_ulong(), i);
	}
}

TEST(GetBitRep, DataScale) {
	Dllp dllp;
	for (int i = 0; i < 3; i++) {
		dllp.DataScale = i;
		boost::dynamic_bitset<> expected = dllp.getBitRep().operator>>(32 - 20);
		expected.resize(2);
		EXPECT_EQ(expected.to_ulong(), i);
	}
}

TEST(GetBitRep, FullPacket1) {
	Dllp dllp(0, 0, 5, 20, 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	EXPECT_EQ(dllp.getBitRep().to_ulong(), 0b01001000000001010000000000000101);
}

TEST(GetBitRep, FullPacket2) {
	Dllp dllp(1, 1, 17, 249, 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl);
	EXPECT_EQ(dllp.getBitRep().to_ulong(), 0b11101000011111100101000000010001);
}

TEST(GetBitRep, FullPacket3) {
	Dllp dllp(1, 1, 4095, 255, 0, true, Dllp::DllpType::updateFC, Dllp::CreditType::NP);
	EXPECT_EQ(dllp.getBitRep().to_ulong(), 0b10011000011111111101111111111111);
}
