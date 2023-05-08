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

//payloadflit
void Receiver::receiveFlit(std::queue<Flit*> flits) {
}
