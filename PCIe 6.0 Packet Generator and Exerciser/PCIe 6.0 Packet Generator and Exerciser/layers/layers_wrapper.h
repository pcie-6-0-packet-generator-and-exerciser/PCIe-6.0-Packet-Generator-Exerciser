#pragma once
#include "./globals.h"
#include "../utils/queue_wrapper.h"
#include "../utils/dllp.h"
#include "./transaction.h"
#include "./datalink.h"
#include "./tlp.h"

class LayersWrapper {
	
public:
	TransactionLayer transaction;
	DataLinkLayer dataLink;
	Tlp partialTlp;

	void sendNOPFlit(const int P_CREDIT[2], const int NP_CREDIT[2], const int CPL_CREDIT[2], Dllp::DllpType dllpType);
};