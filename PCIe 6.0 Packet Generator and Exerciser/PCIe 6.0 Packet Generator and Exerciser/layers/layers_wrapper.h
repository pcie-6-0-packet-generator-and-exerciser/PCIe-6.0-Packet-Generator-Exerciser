#pragma once
#include "../utils/sequence.h"
#include "../utils/queue_wrapper.h"
#include "../utils/flit.h"
#include "globals.h"

class LayersWrapper {
public:
	/**
	 * @brief 
	 * @param sequence 
	 * @param sendOnQueue 
	 * @param PSharedCreditLimit 
	 * @param NPSharedCreditLimit 
	 * @param CplSharedCreditLimit 
	 * @param PSharedCreditConsumed 
	 * @param NPSharedCreditConsumed 
	 * @param CplSharedCreditConsumed 
	*/
	void sendPayloadFlit(Globals globals, Sequence sequence, QueueWrapper<Flit> sendOnQueue, int PSharedCreditLimit[2], int NPSharedCreditLimit[2], int CplSharedCreditLimit[2], int PSharedCreditConsumed[2], int NPSharedCreditConsumed[2], int CplSharedCreditConsumed[2]);
};