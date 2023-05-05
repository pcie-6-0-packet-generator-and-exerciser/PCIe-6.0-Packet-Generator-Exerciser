#include "receiver.h"


Receiver::Receiver(Globals& global, LayersWrapper layer, QueueWrapper<Flit>& sendOnQueue)
	: globals(global), layers(layer), sendOn(sendOnQueue)
{
	// Constructor body (if needed)
}

///nopflit
void Receiver::receiveInit(Flit* flit,Globals& globals) {
	//void LayersWrapper::receiveNOPFlit(Flit* flit, Globals& globals) 
	this->layers.receiveNOPFlit(flit, globals);
}
/*
//payloadflit
void Receiver::receiveFlit(Flit flit) {
	this->layers.receivePayloadFlit(flit, this->sendOn, this->globals.P_CREDIT, this->globals.NP_CREDIT, this->globals.CPL_CREDIT);
}
*/