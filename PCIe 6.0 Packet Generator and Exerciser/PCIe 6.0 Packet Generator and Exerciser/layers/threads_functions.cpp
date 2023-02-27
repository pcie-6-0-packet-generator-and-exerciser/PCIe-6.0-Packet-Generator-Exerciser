#include "./threads_functions.h"

/**
 * @brief Sends a sequence to the transmitter from a queue
 *
 * This function waits on the queue until a sequence is available, and then sends it to the transmitter.
 *
 * @param transmitter A reference to the Transmitter object
 * @param globals A reference to the Globals object
 * @param listenOn A QueueWrapper<Sequence> object that holds the sequences sent from Root Complex
 * @param sendOn A QueueWrapper<Flit> object 
 */
void ThreadsFunctions::normalFlowSender(Transmitter& transmitter, Globals& globals, QueueWrapper<Sequence> listenOn, QueueWrapper<Flit> sendOn) {
	// waits on the queue until a sequence is available on the top of the Tlp
	auto tlpSequence = listenOn.pop();
	
	// send the sequence to the transmitter
	transmitter.sendSequence(tlpSequence);

	
}
