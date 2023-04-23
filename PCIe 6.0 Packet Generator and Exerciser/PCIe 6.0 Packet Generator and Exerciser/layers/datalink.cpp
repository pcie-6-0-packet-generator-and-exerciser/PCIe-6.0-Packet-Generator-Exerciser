#include "datalink.h"

/**
 * @brief Updates the shared credit limit values based on the received DLLP information
 * @param flit Flit containing the DLLPs
 * @param P_SHARED_CREDIT_LIMIT Array of shared credit limit for posted traffic
 * @param NP_SHARED_CREDIT_LIMIT Array of shared credit limit for non-posted traffic
 * @param CPL_SHARED_CREDIT_LIMIT Array of shared credit limit for completion traffic
 * @param FI1 First indication (FI1) flag for credit update
 * @param FI2 Second indication (FI2) flag for credit update
*/
void DatalinkLayer::updateCreditLimit(Flit flit, int P_SHARED_CREDIT_LIMIT[], int NP_SHARED_CREDIT_LIMIT[], int CPL_SHARED_CREDIT_LIMIT[], int P_DEDICATED_CREDIT_LIMIT[], int NP_DEDICATED_CREDIT_LIMIT[], int CPL_DEDICATED_CREDIT_LIMIT[], bool& FI1, bool& FI2) {

	// The flit contains a DLLP, with size of 32 bit from 14th byte
	auto dllpPayload = boost::dynamic_bitset(32, (flit.DLLPPayload.to_ulong() >> (14 * 8)) & 0xffffffff);
	auto dllpObj = Dllp::DllpObjRep(dllpPayload);

	// State FC_INIT1: if FI1 flag is not set
	// Wait for *all* credit limit type to be updated then set FI1 to true
	if (!FI1) {
		switch (dllpObj.shared)
		{
		case false:
			switch (dllpObj.m_creditType)
			{
			case Dllp::CreditType::Cpl:
				CPL_DEDICATED_CREDIT_LIMIT[0] = dllpObj.HdrFC;
				CPL_DEDICATED_CREDIT_LIMIT[1] = dllpObj.DataFc;
				break;
			case Dllp::CreditType::P:
				P_DEDICATED_CREDIT_LIMIT[0] = dllpObj.HdrFC;
				P_DEDICATED_CREDIT_LIMIT[1] = dllpObj.DataFc;
				break;
			case Dllp::CreditType::NP:
				NP_DEDICATED_CREDIT_LIMIT[0] = dllpObj.HdrFC;
				NP_DEDICATED_CREDIT_LIMIT[1] = dllpObj.DataFc;
				break;
			default:
				break;
			}
		case true:
			switch (dllpObj.m_creditType)
			{
			case Dllp::CreditType::Cpl:
				CPL_SHARED_CREDIT_LIMIT[0] = dllpObj.HdrFC;
				CPL_SHARED_CREDIT_LIMIT[1] = dllpObj.DataFc;
				break;
			case Dllp::CreditType::P:
				P_SHARED_CREDIT_LIMIT[0] = dllpObj.HdrFC;
				P_SHARED_CREDIT_LIMIT[1] = dllpObj.DataFc;
				break;
			case Dllp::CreditType::NP:
				NP_SHARED_CREDIT_LIMIT[0] = dllpObj.HdrFC;
				NP_SHARED_CREDIT_LIMIT[1] = dllpObj.DataFc;
				break;
			default:
				break;
			}
		}

		// Set the FI1 flag if all credit limits are updated
		if (P_SHARED_CREDIT_LIMIT[0] != -1 && NP_SHARED_CREDIT_LIMIT[0] != -1 &&
			CPL_SHARED_CREDIT_LIMIT[0] != -1 && P_DEDICATED_CREDIT_LIMIT[0] != -1 &&
			NP_DEDICATED_CREDIT_LIMIT[0] != -1 && CPL_DEDICATED_CREDIT_LIMIT[0] != -1) {
			FI1 = true;
		}
	}
	// STATE FC_INIT2: FI1 is set
	// Wait for *any* initFC2 Dllp to be recieved, then set FI2 to true
	else if (!FI2 && FI1 && dllpObj.m_type == Dllp::DllpType::initFC2) {
		// Set the FI2 flag if any expected DLLPs are received
		FI2 = true;
	}
}
Flit* DatalinkLayer::addDLLP(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[])
{
	Dllp* dllp = new Dllp(1, 1, credit[1], credit[0], 0, shared, dllpType, creditType);
	flit->DLLPPayload = dllp->getBitRep();
	return flit;
}

boost::dynamic_bitset<> concatDynamicBitset(const boost::dynamic_bitset<>& bs1, const boost::dynamic_bitset<>& bs2) {
	boost::dynamic_bitset<> bs1Copy(bs1);
	boost::dynamic_bitset<> bs2Copy(bs2);
	size_t totalSize = bs1.size() + bs2.size();
	bs1Copy.resize(totalSize);
	bs1Copy <<= bs2.size();
	bs1Copy |= bs2Copy;
	return bs1Copy;
}
void insertBitsetToArray(const boost::dynamic_bitset<>& bitset, uint8_t bitsetArr[], const int start = 0) {
	for (size_t i = start; i < bitset.size(); i++) {
		bitsetArr[i / 8] |= (bitset[i] << (i % 8));
	}
}
boost::dynamic_bitset<> DatalinkLayer::calculateCRC(Flit* flit) {
	const uint64_t polynomial = 0b100001011001101110010101100011010101100110101001011;

	uint8_t flitPayloadArray[242] = { 0 };

	insertBitsetToArray(flit->TLPPayload, flitPayloadArray);
	insertBitsetToArray(flit->DLLPPayload, flitPayloadArray, flit->TLPPayload.size());
	
	CRC::Parameters<uint8_t, 64> params = { polynomial, 0, 0, false, false };
	uint8_t crc = CRC::Calculate(flitPayloadArray, sizeof(flitPayloadArray), params);

	return boost::dynamic_bitset<>(crc);
}
