#include "receiver.h"

Receiver::Receiver(Globals global, LayersWrapper layer, QueueWrapper<Flit> sendOnQueue) {
	this->globals = global;
	this->layers = layer;
	this->sendOn = sendOnQueue;
}

//nopflit
void Receiver::receiveInit(Flit flit) {
	this->layers.receiveNOPFlit(flit,this->globals.P_SHARED_CREDIT_LIMIT,this->globals.NP_SHARED_CREDIT_LIMIT,this->globals.CPL_SHARED_CREDIT_LIMIT,this->globals.Fl1,this->globals.Fl2);
}

//payloadflit
void Receiver::receiveFlit(Flit flit) {
	this->layers.receivePayloadFlit(flit, this->sendOn, this->globals.P_CREDIT, this->globals.NP_CREDIT, this->globals.CPL_CREDIT);
}
