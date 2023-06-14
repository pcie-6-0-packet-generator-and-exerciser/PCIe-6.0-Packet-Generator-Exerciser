#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/utils/dllp.h"
#include "boost/dynamic_bitset.hpp"

#define INITFC1_P 0b0100
#define INITFC1_NP 0b0101
#define INITFC1_CPL 0b0110
#define INITFC2_P 0b1100
#define INITFC2_NP 0b1101
#define INITFC2_CPL 0b1110
#define TYPE_SIZE 4
#define DLLP_SIZE 32
#define TYPE_END_INDEX 31
#define DATA_FC_END_INDEX 11
#define DATA_FC_SIZE 12
#define HEADER_FC_END_INDEX 21
#define HEADER_FC_SIZE 8
#define VC_END_INDEX 26
#define VC_SIZE 3
#define SHARED_END_INDEX 27
#define SHARED_SIZE 1

/**
 * @brief Helper function that set the bits in a bitset from a given value
 * @param bitset the bitset to be modified
 * @param start the start index of the bitset to be modified
 * @param length the length of the bitset to be modified
 * @param value the unsigned decimal value to be set in the bitset
*/
void set_bits(boost::dynamic_bitset<>& bit_set, std::size_t start, std::size_t length, unsigned int value) {
	// Create the mask with the desired bits set to 1
	boost::dynamic_bitset<> mask(bit_set.size(), (1 << length) - 1);
	mask <<= (start - length + 1);

	// Create a temporary bitset to store the value
	boost::dynamic_bitset<> temp(bit_set.size(), value);
	temp <<= (start - length + 1);

	// Clear the bits in the bitset using the mask
	bit_set &= ~mask;

	// Set the bits in the bitset using the new value and the mask
	bit_set |= (temp & mask);
}

TEST(DllpGetObjRep, emptyFC1PDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC1 and the credit type to P
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC1_P);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0); // the data scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0); // the header scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->DataFc, 0); // there's should be no data 
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, false); // it should be dedicated
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::P);
}

TEST(DllpGetObjRep, emptyFC1NPDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC1 and the credit type to NP
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC1_NP);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0); // the data scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0); // the header scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->DataFc, 0); // there's should be no data 
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, false); // it should be dedicated
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::NP);
}

TEST(DllpGetObjRep, emptyFC1CPLDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC1 and the credit type to Cpl
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC1_CPL);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0); // the data scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0); // the header scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->DataFc, 0); // there's should be no data 
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, false); // it should be dedicated
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::Cpl);
}

TEST(DllpGetObjRep, emptyFC2PDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC2 and the credit type to P
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC2_P);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0); // the data scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0); // the header scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->DataFc, 0); // there's should be no data 
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, false); // it should be dedicated
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC2);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::P);
}

TEST(DllpGetObjRep, emptyFC2CNPLDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC2 and the credit type to NP
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC2_NP);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0); // the data scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0); // the header scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->DataFc, 0); // there's should be no data 
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, false); // it should be dedicated
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC2);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::NP);
}

TEST(DllpGetObjRep, emptyFC2CPLDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC2 and the credit type to Cpl
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC2_CPL);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0); // the data scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0); // the header scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->DataFc, 0); // there's should be no data 
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, false); // it should be dedicated
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC2);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::Cpl);
}

TEST(DllpGetObjRep, sharedInitFC1PDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC1 and the credit type to P
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC1_P);

	// set the Dllp shared bit to 1
	set_bits(dllpBitRep, SHARED_END_INDEX, SHARED_SIZE, 0b1);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0);
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0);
	EXPECT_EQ(dllpTestObjRep->DataFc, 0);
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, true);
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::P);
}

TEST(DllpGetObjRep, DllpWithDataFC) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC1 and the credit type to P
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC1_P);

	// set the Dllp data FC to 0b111111111111
	set_bits(dllpBitRep, DATA_FC_END_INDEX, DATA_FC_SIZE, 0b111111111111);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0);
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0);
	EXPECT_EQ(dllpTestObjRep->DataFc, 0b111111111111);
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, false);
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::P);
}


TEST(DllpGetObjRep, DllpWithHeaderFC) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC1 and the credit type to P
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC1_P);

	// set the Dllp header FC to 0b11111111
	set_bits(dllpBitRep, HEADER_FC_END_INDEX, HEADER_FC_SIZE, 0b11111111);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0);
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0);
	EXPECT_EQ(dllpTestObjRep->DataFc, 0);
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0b11111111);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, false);
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::P);
}

TEST(DllpGetObjRep, DllpWithVC) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(DLLP_SIZE);

	// set the Dllp type to initFC1 and the credit type to P
	set_bits(dllpBitRep, TYPE_END_INDEX, TYPE_SIZE, INITFC1_P);

	// set the Dllp VC to 0b111
	set_bits(dllpBitRep, VC_END_INDEX, VC_SIZE, 0b111);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0);
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0);
	EXPECT_EQ(dllpTestObjRep->DataFc, 0);
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0b111);
	EXPECT_EQ(dllpTestObjRep->shared, false);
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::P);
}
