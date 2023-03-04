#include "datalink.h"

Flit DatalinkLayer::addDLLP(Flit flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[])
{
	Dllp* dllp = new Dllp(1, 1, credit[1], credit[0], 0, shared, dllpType, creditType);
	Flit *flit = new Flit();
	flit->DLLPPayload = dllp->getBitRep();
	return flit;
}