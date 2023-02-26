#include "transmitter.h"
/**
 * @brief Sends an InitFC1 message to the receiver.
 * @param void
 * @return void
*/
void Transmitter::sendInitFc1(void) {
	this->layers.sendNOpFlit(this->globals.P_CREDITS, this->globals.NP_CREDITS, this->globals.CPP_CREDITS, Dllp::DllpType::initFC1);
}