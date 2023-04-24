#include "layers_wrapper.h"

void LayersWrapper::sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) {
	static bool sharedturn = true;
	static int intCreditType = 0; // P credit type
	int credits[2] = { -1 };

	switch (intCreditType)
	{
		// P credits
	case 0:
		credits[0] = sharedturn ? globals.P_SHARED_CREDIT_LIMIT[0] : globals.P_DEDICATED_CREDIT_LIMIT[0];
		credits[1] = sharedturn ? globals.P_SHARED_CREDIT_LIMIT[0] : globals.P_DEDICATED_CREDIT_LIMIT[0];
		break;
		// NP credits
	case 1:
		credits[0] = sharedturn ? globals.NP_SHARED_CREDIT_LIMIT[0] : globals.NP_DEDICATED_CREDIT_LIMIT[0];
		credits[1] = sharedturn ? globals.NP_SHARED_CREDIT_LIMIT[0] : globals.NP_DEDICATED_CREDIT_LIMIT[0];
		break;
		// CPL credits
	case 2:
		credits[0] = sharedturn ? globals.CPL_SHARED_CREDIT_LIMIT[0] : globals.CPL_DEDICATED_CREDIT_LIMIT[0];
		credits[1] = sharedturn ? globals.CPL_SHARED_CREDIT_LIMIT[0] : globals.CPL_DEDICATED_CREDIT_LIMIT[0];
		break;
	}
	
	// Push NOP Flit to the specified queue
	datalink->pushFlitToQueue(new Flit(), sendOn, dllpType, static_cast<Dllp::CreditType>(intCreditType), sharedturn, credits);

	// Update the shared turn and credits type
	sharedturn ^= 1;
	intCreditType = (intCreditType + 1) % 3;
}