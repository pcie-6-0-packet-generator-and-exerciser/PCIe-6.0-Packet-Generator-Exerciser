#include "transmitter.h"
/**
 * @brief Sends an InitFC1 message to the receiver.
 * @param void
 * @return void
*/
void Transmitter::sendInitFC1(void) {
	this->layers->sendNOPFlit(this->globals, Dllp::DllpType::initFC1, this->sendOn);
}