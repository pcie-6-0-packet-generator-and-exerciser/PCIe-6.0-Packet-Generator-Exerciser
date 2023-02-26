#include "transmitter.h"
/**
 * @brief Sends an InitFC1 message to the receiver.
 * @param void
 * @return void
*/
void Transmitter::sendInitFC1(void);

/**
 * @brief Sends an InitFC2 message to the receiver.
 * @param void
 * @return void
*/
void Transmitter::sendInitFC2(void);

/**
 * @brief Sends a sequence of packets to the receiver.
 * @param sequence The sequence of packets to send.
 * @return void
*/
void Transmitter::sendSequence(Sequence sequence);