#include "layers/data_link_layer.h"

/**
 * @brief Updates the shared credit limit values based on the received DLLP information
 * @param flit Flit containing the DLLPs
 * @param P_SHARED_CREDIT_LIMIT Array of shared credit limit for posted traffic
 * @param NP_SHARED_CREDIT_LIMIT Array of shared credit limit for non-posted traffic
 * @param CPL_SHARED_CREDIT_LIMIT Array of shared credit limit for completion traffic
 * @param FI1 First indication (FI1) flag for credit update
 * @param FI2 Second indication (FI2) flag for credit update
*/
void DataLinkLayer::updateCreditLimit(Flit flit, int& P_SHARED_CREDIT_LIMIT[2], int& NP_SHARED_CREDIT_LIMIT[2], int& CPL_SHARED_CREDIT_LIMIT[2], bool& FI1, bool& FI2) {
	// Static variables to store the flags and state across function calls
	static bool discard, pFc1Flag, npFc1Flag, cplFc1Flag, pFc2Flag, npFc2Flag, cplFc2Flag;

	// The flit contains two DLLPs, dllp_1 = flit.dllpPayload[0:32], dllp_2 = flit.dllpPayload[32:]
	auto dllpPayload = flit.dllpPayload.to_ulong();

	// the two dllps found in the flit
	Dllp Dllps[2] = { Dllp::DllpObjRep(std::bitset<32>((dllpPayload >> 32) & 0xffffffff)), Dllp::DllpObjRep(std::bitset<32>(dllpPayload & 0xffffffff)) };

	// Discard received DLLPs if the discard flag is set
	if (discard) {
		for (Dllp dllp : Dllps) {
			switch (dllp.m_type)
			{
			case Dllp::DllpType::initFC1:
				switch (dllp.m_creditType)
				{
				case Dllp::CreditType::Cpl:
					cplFc1Flag = true;
					break;
				case Dllp::CreditType::P:
					pFc1Flag = true;
					break;
				case Dllp::CreditType::NP:
					npFc1Flag = true;
					break;
				default:
					break;
				}
				break;
			case Dllp::DllpType::initFC2:
				switch (dllp.m_creditType)
				{
				case Dllp::CreditType::Cpl:
					cplFc2Flag = true;
					break;
				case Dllp::CreditType::P:
					pFc2Flag = true;
					break;
				case Dllp::CreditType::NP:
					npFc2Flag = true;
					break;
				default:
					break;
				}
				break;
			}
		}
	}

	// Update credit limits if the discard flag is not set and the FI1 flag is not set
	if (!discard && !FI1)
	{
		for (Dllp dllp : Dllps) {
			switch (dllp.m_creditType)
			{
			case Dllp::CreditType::Cpl:

				break;
			case Dllp::CreditType::P:
				P_SHARED_CREDIT_LIMIT[0] = dllp.HdrFC;
				P_SHARED_CREDIT_LIMIT[1] = dllp.DataFc;
				break;
			case Dllp::CreditType::NP:
				NP_SHARED_CREDIT_LIMIT[0] = dllp.HdrFC;
				NP_SHARED_CREDIT_LIMIT[1] = dllp.DataFc;
				break;
			default:
				break;
			}
		}
	}

	// Set the FI1 flag if all credit limits are updated
	if (P_SHARED_CREDIT_LIMIT && NP_SHARED_CREDIT_LIMIT && CPL_SHARED_CREDIT_LIMIT) {
		FI1 = true;
		// Set the FI2 flag if all expected DLLPs are received
		if (!FI2 && pFc1Flag && npFc1Flag && cplFc1Flag && pFc2Flag && npFc2Flag && cplFc2Flag)
			FI2 = true;
	}
}