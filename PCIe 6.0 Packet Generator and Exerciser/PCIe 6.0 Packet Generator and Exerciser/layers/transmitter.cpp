#include "transmitter.h"

Transmitter::Transmitter(Globals& globals, QueueWrapper<Flit*>* sendOn)
{
	this->globals = globals;
	this->sendOn = sendOn;
}

void Transmitter::sendInitFC1(void) {
	this->layers->sendNOPFlit(this->globals, Dllp::DllpType::initFC1, this->sendOn);
}

void Transmitter::sendInitFC2(void) {
	this->layers->sendNOPFlit(this->globals, Dllp::DllpType::initFC2, this->sendOn);
}

void Transmitter::sendSequence(std::queue<TLP*> sequence) {
	this->layers->sendPayloadFlit(this->globals, sequence, *this->sendOn);
}