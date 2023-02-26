#include "transmitter.h"
/**
 * @brief Sends a sequence of packets to the receiver.
 * @param sequence The sequence of packets to be sent.
 * @return void
*/
void Transmitter::sendSequence(Sequence sequence) {
	this->layers.sendPayloadFlit(sequence, this->sendOnQueue, this->globals.P_SHARED_CREDIT_LIMIT, this->globals.NP_SHARED_CREDIT_LIMIT, this->globals.CPL_SHARED_CREDIT_LIMIT, this->globals.P_SHARED_CREDITS_CONSUMED, this->globals.NP_SHARED_CREDITS_CONSUMED, this->globals.CPL_SHARED_CREDITS_CONSUMED);
}

