#include "layers_wrapper.h"

void LayersWrapper::sendNOPFlit(int P_CREDIT[2], int NP_CREDIT[2], int CPL_CREDIT[2], Dllp::DllpType dllpType, QueueWrapper<std::queue<Flit*>*>* sendOn) {
	// create a new queue for NOP Flits
	std::queue<Flit*>* nopFlitQueue = new std::queue<Flit*>();

	// Send shared NOP Flits for each credit type 
	this->datalink->pushFlitToQueue(new Flit(), nopFlitQueue, dllpType, Dllp::CreditType::Cpl, true, CPL_CREDIT);
	this->datalink->pushFlitToQueue(new Flit(), nopFlitQueue, dllpType, Dllp::CreditType::NP, true, NP_CREDIT);
	this->datalink->pushFlitToQueue(new Flit(), nopFlitQueue, dllpType, Dllp::CreditType::P, true, P_CREDIT);
	
	// Send dedicated NOP Flits for each credit type 
	this->datalink->pushFlitToQueue(new Flit(), nopFlitQueue, dllpType, Dllp::CreditType::Cpl, false, CPL_CREDIT);
	this->datalink->pushFlitToQueue(new Flit(), nopFlitQueue, dllpType, Dllp::CreditType::NP, false, NP_CREDIT);
	this->datalink->pushFlitToQueue(new Flit(), nopFlitQueue, dllpType, Dllp::CreditType::P, false, P_CREDIT);

	// push the NOP Flit queue to the specified queue
	sendOn->push(nopFlitQueue);
}