#include "./layers_wrapper.h"
/**
 * @brief Sends a NOP flit with specified DLLP type and credit types.
 * @param P_SHARED_CREDIT An array containing the credit information for shared P-type credit.
 * @param NP_SHARED_CREDIT An array containing the credit information for shared NP-type credit.
 * @param CPL_SHARED_CREDIT An array containing the credit information for shared Cpl-type credit.
 * @param P_DEDICATED_CREDIT An array containing the credit information for dedicated P-type credit.
 * @param NP_DEDICATED_CREDIT An array containing the credit information for dedicated NP-type credit.
 * @param CPL_DEDICATED_CREDIT An array containing the credit information for dedicated Cpl-type credit.
 * @param dllpType An enum representing the DLLP type to create.
 * @param sendOn The queue on which to send the FLIT.
*/
void LayersWrapper::sendNOPFlit(const int P_SHARED_CREDIT[2], const int NP_SHARED_CREDIT[2], const int CPL_SHARED_CREDIT[2], const int P_DEDICATED_CREDIT[2], const int NP_DEDICATED_CREDIT[2], const int CPL_DEDICATED_CREDIT[2], Dllp::DllpType dllpType, QueueWrapper<Flit> sendOn) {
	Flit* flit = new Flit();

	// Loop over the 6 types of InitFC packets to be sent
	switch (dllpType)
	{
	// STATE: INIT_FC1
	case Dllp::DllpType::initFC1:
		// Send NOP flit with shared InitFC1 Dllp
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC1, Dllp::CreditType::P, true, P_SHARED_CREDIT);
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC1, Dllp::CreditType::NP, true, NP_SHARED_CREDIT);
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC1, Dllp::CreditType::Cpl, true, CPL_SHARED_CREDIT);
		// Send NOP flit with dedicated InitFC1 Dllp
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC1, Dllp::CreditType::P, false, P_DEDICATED_CREDIT);
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC1, Dllp::CreditType::NP, false, NP_DEDICATED_CREDIT);
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC1, Dllp::CreditType::Cpl, false, CPL_DEDICATED_CREDIT);
			break;
	// STATE: INIT_FC2
	case Dllp::DllpType::initFC2:
		// Send NOP flit with shared InitFC2 Dllp
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC2, Dllp::CreditType::P, true, P_SHARED_CREDIT);
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC2, Dllp::CreditType::NP, true, NP_SHARED_CREDIT);
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl, true, CPL_SHARED_CREDIT);
		// Send NOP flit with dedicated InitFC2 Dllp
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC2, Dllp::CreditType::P, false, P_DEDICATED_CREDIT);
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC2, Dllp::CreditType::NP, false, NP_DEDICATED_CREDIT);
		this->dataLink.sendFlit(flit, sendOn, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl, false, CPL_DEDICATED_CREDIT);
		break;
	default:
		break;
	}
}
