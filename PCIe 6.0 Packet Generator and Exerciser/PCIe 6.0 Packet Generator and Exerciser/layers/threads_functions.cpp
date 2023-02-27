#include "./threads_functions.h"

/**
 * @brief Sends a sequence to the transmitter from a queue
 *
 * This function waits on the queue until a sequence is available, and then sends it to the transmitter.
 *
 * @param transmitter A reference to the Transmitter object
 * @param listenOn A QueueWrapper<Sequence> object that holds the sequences sent from Root Complex
 */
void ThreadsFunctions::normalFlowSender(Transmitter& transmitter, QueueWrapper<Sequence> listenOn) {
	// waits on the queue until a sequence is available on the top of the Tlp
	auto tlpSequence = listenOn.pop();
	
	// send the sequence to the transmitter
	transmitter.sendSequence(tlpSequence);
}
