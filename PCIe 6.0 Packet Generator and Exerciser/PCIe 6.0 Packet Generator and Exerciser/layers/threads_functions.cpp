#include "./threads_functions.h"

/**
 * @brief Sends a flit to the reciever from the listenOn queue
 *
 * This function waits on the listenOn queue until a flit is available and sends it to a receiver
 *
 * @param receiver A reference to the Reciever object
 * @param listenOn A QueueWrapper<Sequence> object that holds the flits sent from transmitter
 */
void ThreadsFunctions::normalFlowReceiver(Receiver& receiver, QueueWrapper<Flit> listenOn) {
	// waits on the queue until a flit is available 
	auto flit = listenOn.pop();
	
	// send the flit to the receiver
	receiver.receiveFlit(flit);
}
