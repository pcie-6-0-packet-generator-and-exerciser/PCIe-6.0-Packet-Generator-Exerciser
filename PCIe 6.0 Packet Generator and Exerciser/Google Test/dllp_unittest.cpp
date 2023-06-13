#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/utils/dllp.h"
#include "boost/dynamic_bitset.hpp"

#define INITFC1_P 0b0100
#define INITFC1_NP 0b0101
#define INITFC1_CPL 0b0110
#define INITFC2_P 0b1100
#define INITFC2_NP 0b1101
#define INITFC2_CPL 0b1110

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

/**
 * @brief testing the function to an empty InitFC1 Dllp bitset with P credit type
 * @param dllpGetObjRep test suite that contain test for the Dllp::getObjRep function
 * @param emptyDllpTest
*/
TEST(dllpGetObjRep, emptyFC1PDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(32);

	// set the Dllp type to initFC1 and the credit type to P
	set_bits(dllpBitRep, 31, 4, INITFC1_P);

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

/**
 * @brief testing the function to an empty InitFC1 Dllp bitset with NP credit type
 * @param dllpGetObjRep test suite that contain test for the Dllp::getObjRep function
 * @param emptyDllpTest
*/
TEST(dllpGetObjRep, emptyFC1NPDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(32);

	// set the Dllp type to initFC1 and the credit type to NP
	set_bits(dllpBitRep, 31, 4, INITFC1_NP);

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

/**
 * @brief testing the function to an empty InitFC1 Dllp bitset with Cpl credit type
 * @param dllpGetObjRep test suite that contain test for the Dllp::getObjRep function
 * @param emptyDllpTest
*/
TEST(dllpGetObjRep, emptyFC1CPLDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(32);

	// set the Dllp type to initFC1 and the credit type to Cpl
	set_bits(dllpBitRep, 31, 4, INITFC1_CPL);

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

/**
 * @brief testing the function to an empty InitFC2 Dllp bitset with P credit type
 * @param dllpGetObjRep test suite that contain test for the Dllp::getObjRep function
 * @param emptyDllpTest
*/
TEST(dllpGetObjRep, emptyFC2PDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(32);

	// set the Dllp type to initFC2 and the credit type to P
	set_bits(dllpBitRep, 31, 4, INITFC2_P);

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

/**
 * @brief testing the function to an empty InitFC2 Dllp bitset with NP credit type
 * @param dllpGetObjRep test suite that contain test for the Dllp::getObjRep function
 * @param emptyDllpTest
*/
TEST(dllpGetObjRep, emptyFC2CNPLDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(32);

	// set the Dllp type to initFC2 and the credit type to NP
	set_bits(dllpBitRep, 31, 4, INITFC2_NP);

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

/**
 * @brief testing the function to an empty InitFC2 Dllp bitset with Cpl credit type
 * @param dllpGetObjRep test suite that contain test for the Dllp::getObjRep function
 * @param emptyDllpTest
*/
TEST(dllpGetObjRep, emptyFC2CPLDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(32);

	// set the Dllp type to initFC2 and the credit type to Cpl
	set_bits(dllpBitRep, 31, 4, INITFC2_CPL);

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

TEST(DllpObjRepTest, sharedInitFC1PDllpTest) {
	// Dllp size is 32 bit, initialized with 0s
	boost::dynamic_bitset<> dllpBitRep(32);

	// set the Dllp type to initFC1 and the credit type to P
	set_bits(dllpBitRep, 31, 4, INITFC1_P);

	// set the Dllp type to initFC2 and the credit type to Cpl
	set_bits(dllpBitRep, 27, 1, 0b1);

	// get the Dllp object representation
	Dllp* dllpTestObjRep = &Dllp::DllpObjRep(dllpBitRep);

	EXPECT_EQ(dllpTestObjRep->DataScale, 0); // the data scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->HdrScale, 0); // the header scaling always should be 0
	EXPECT_EQ(dllpTestObjRep->DataFc, 0); // there's should be no data 
	EXPECT_EQ(dllpTestObjRep->HdrFC, 0);
	EXPECT_EQ(dllpTestObjRep->VC, 0);
	EXPECT_EQ(dllpTestObjRep->shared, true); // it should be dedicated
	EXPECT_EQ(dllpTestObjRep->m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllpTestObjRep->m_creditType, Dllp::CreditType::P);
}
