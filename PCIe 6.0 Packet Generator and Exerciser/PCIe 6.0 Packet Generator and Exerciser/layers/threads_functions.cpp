#include "./threads_functions.h"

/**
 * @brief Sends a flit to the reciever from the listenOn queue
 *
 * This function waits on the listenOn queue until a flit is available and sends it to a receiver
 *
 * @param transmitter A reference to the Reciever object
 * @param globals A reference to the Globals object
 * @param listenOn A QueueWrapper<Sequence> object that holds the flits sent from transmitter
 * @param sendOn A QueueWrapper<Flit> object 
 */
void ThreadsFunctions::normalFlowReceiver(Receiver& receiver, Globals& globals, QueueWrapper<Flit> listenOn, QueueWrapper<Sequence> sendOn) {
	// waits on the queue until a flit is available 
	auto flit = listenOn.pop();
	
	// send the flit to the receiver
	reciever.receiveFlit(flit);
}
