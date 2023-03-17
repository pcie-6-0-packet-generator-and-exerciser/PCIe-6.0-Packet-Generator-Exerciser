#pragma once
#include "./globals.h"
#include "../utils/queue_wrapper.h"
#include "../utils/dllp.h"
#include "../layers/transaction_layer.h"
#include "./datalink.h"
#include "../utils/tlp.h"

class LayersWrapper {
	
public:
	TransactionLayer transaction;
	DatalinkLayer dataLink;
	TLP partialTlp;

	void sendNOPFlit(const int P_SHARED_CREDIT[2], const int NP_SHARED_CREDIT[2], const int CPL_SHARED_CREDIT[2], const int P_DEDICATED_CREDIT[2], const int NP_DEDICATED_CREDIT[2], const int CPL_DEDICATED_CREDIT[2], Dllp::DllpType dllpType, QueueWrapper<Flit> sendOnQueue);
};