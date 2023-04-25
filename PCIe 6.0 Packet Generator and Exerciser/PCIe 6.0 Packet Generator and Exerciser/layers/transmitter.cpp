#include "transmitter.h"

void Transmitter::sendInitFC1(void) {
	this->layers->sendNOPFlit(this->globals, Dllp::DllpType::initFC1, this->sendOn);
}

void Transmitter::sendInitFC2(void) {
	this->layers->sendNOPFlit(this->globals, Dllp::DllpType::initFC2, this->sendOn);
}

void Transmitter::sendSequence(std::vector<TLP*> sequence) {
	std::queue<TLP*> tlpQueue;
	
	// copy the sequence into a queue of TLPs
	for (auto it = sequence.begin(); it != sequence.end(); ++it) { tlpQueue.push(*it); }

	this->layers->sendPayloadFlit(this->globals, tlpQueue, *this->sendOn);
}