#include "receiver.h"


Receiver::Receiver(Globals& global, LayersWrapper layer, QueueWrapper<TLP*>& sendOnQueue)
	: globals(global), layers(layer), sendOn(sendOnQueue)
{
	// Constructor body (if needed)
}

///nopflit
void Receiver::receiveInit(Flit* flit, Globals& globals) {
	//void LayersWrapper::receiveNOPFlit(Flit* flit, Globals& globals) 
	this->layers.receiveNOPFlit(flit, globals);
}

//payloadflit
void Receiver::receiveFlit(queue<Flit*> flits) {
	//	void receivePayloadFlit(Globals& globals, std::queue<Flit> flits, QueueWrapper<std::queue<TLP>>& sendOn);
	this->layers.receivePayloadFlit(this->globals, flits, this->sendOn);
}
