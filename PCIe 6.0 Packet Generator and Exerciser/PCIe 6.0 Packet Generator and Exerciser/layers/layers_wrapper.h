#pragma once
#include "transaction_layer.h"
#include "datalink.h"
#include "../utils/tlp.h"
#include "../utils/queue_wrapper.h"
#include <queue>

class LayersWrapper
{
public:
	TransactionLayer* transaction;
	DatalinkLayer* datalink;
	TLP* partialTlp;

	/**
	 * @brief Sends NOP Flit to the specified queue
	 * This function sends NOP Flits to the specified queue for each credit type.
	 * @param P_CREDIT an array of two integers representing the available P credits
	 * @param NP_CREDIT an array of two integers representing the available NP credits
	 * @param CPL_CREDIT an array of two integers representing the available CPL credits
	 * @param dllpType the DLLP type for the NOP Flits
	 * @param sendOn a pointer to a QueueWrapper object where the NOP Flit queue will be pushed
	 * @return void
	*/
	void sendNOPFlit(int P_CREDIT[2], int NP_CREDIT[2], int CPL_CREDIT[2], Dllp::DllpType dllpType, QueueWrapper<std::queue<Flit*>*>* sendOn);

};

