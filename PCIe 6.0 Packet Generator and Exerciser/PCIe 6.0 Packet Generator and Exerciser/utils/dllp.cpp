#include "dllp.h"
#include "boost/dynamic_bitset.hpp"

Dllp::Dllp(int hdrScale, int dataScale, int dataFc, int hdrFC, int vc, bool share, DllpType type, CreditType creditType) {
	HdrScale = hdrScale;
	DataScale = dataScale;
	DataFc = dataFc;
	HdrFC = hdrFC;
	VC = vc;
	m_type = type;
	m_creditType = creditType;
	shared = share;
}

Dllp::Dllp() {
	// default constructor
	this->HdrScale = 0;
	this->DataScale = 0;
	this->DataFc = 0;
	this->HdrFC = 0;
	this->VC = 0;
	this->m_type = DllpType::updateFC;
	this->m_creditType = CreditType::Cpl;
	this->shared = false;
}

Dllp::~Dllp() {
	// destructor
}

boost::dynamic_bitset<> Dllp::getBitRep() const {
	// Create an unsigned int with all bits set to 0
	unsigned int bitRep = 0;

	// Add the value of DataFC in the first 12 bits (0-11)
	bitRep |= DataFc;

	// Add the value of DataScale in the next 2 bits (12-13)
	bitRep |= (DataScale << 12);

	// Add the value of HdrFC in the next 8 bits (14-21)
	bitRep |= (HdrFC << 14);

	// Add the value of HdrScale in the next 2 bits (22-23)
	bitRep |= (HdrScale << 22);

	// Add the value of VC in the next 3 bits (24-26)
	bitRep |= (VC << 24);

	// Add the value of Shared in the next bit (27)
	bitRep |= (shared << 27);

	// Add the value of CreditType in the next 2 bits (28-29)
	bitRep |= (static_cast<int>(m_creditType) << 28);

	// Add the value of Type in the last 2 bits (30-31)
	bitRep |= (static_cast<int>(m_type) << 30);

	// Return a std::bitset<32> object initialized with bitRep
	return boost::dynamic_bitset<>(32, bitRep);
}

/**
 * @brief This function constructs a Dllp object from a 32-bit bitset representation of a Dllp.
 * @param dllpPayloadBits A 32-bit bitset representing a Dllp.
 * @return Dllp The constructed Dllp object, If the Dllp type is invalid, the function returns NULL.
*/
Dllp Dllp::DllpObjRep(boost::dynamic_bitset<> dllpPayloadBits) {
	unsigned long dllpBitsValue = dllpPayloadBits.to_ulong();

	// Take a subset of the left-most 4bits for the credit type
	boost::dynamic_bitset<> dllpCreditType(4, dllpBitsValue >> 28);

	// Take a subset of bits from the 10th to 17th bit from left for the header fc
	boost::dynamic_bitset<> dllpHdrFc(8, (dllpBitsValue >> 14) & 0xff);

	// Take a subset of bits from the right-most 12 bits for the data fc
	boost::dynamic_bitset<> dllpDataFc(12, dllpBitsValue & 0xfff);

	// Take the 26th bit from right for the shared bit
	boost::dynamic_bitset<> dllpShared(1, (dllpBitsValue >> 27) & 0x1);

	// recreating the dllp out of the bit representation
	Dllp recievedDllp;

	// shared bit
	recievedDllp.shared = dllpShared.to_ulong();

	// credit type and dllp type
	switch (dllpCreditType.to_ulong())
	{
	case 0b0100:
		recievedDllp.m_creditType = Dllp::CreditType::P;
		recievedDllp.m_type = Dllp::DllpType::initFC1;
		break;
	case 0b0101:
		recievedDllp.m_creditType = Dllp::CreditType::NP;
		recievedDllp.m_type = Dllp::DllpType::initFC1;
		break;
	case 0b0110:
		recievedDllp.m_creditType = Dllp::CreditType::Cpl;
		recievedDllp.m_type = Dllp::DllpType::initFC1;
		break;
	case 0b1100:
		recievedDllp.m_creditType = Dllp::CreditType::P;
		recievedDllp.m_type = Dllp::DllpType::initFC2;
		break;
	case 0b1101:
		recievedDllp.m_creditType = Dllp::CreditType::NP;
		recievedDllp.m_type = Dllp::DllpType::initFC2;
		break;
	case 0b1110:
		recievedDllp.m_creditType = Dllp::CreditType::Cpl;
		recievedDllp.m_type = Dllp::DllpType::initFC2;
		break;
	}

	return recievedDllp;
}