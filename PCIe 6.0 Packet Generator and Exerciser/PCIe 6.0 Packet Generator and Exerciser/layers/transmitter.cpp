#include "transmitter.h"
/**
 * @brief Sends an InitFC2 message to the receiver.
 * @param void
 * @return void
*/
void Transmitter::sendInitFC2(void) {
	this->layers.sendNOpFlit(this->globals.P_CREDITS, this->globals.NP_CREDITS, this->globals.CPP_CREDITS, Dllp::DllpType::initFC2);
}