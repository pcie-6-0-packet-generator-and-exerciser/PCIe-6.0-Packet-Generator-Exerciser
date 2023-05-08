#include "thread_functions.h"

void normalFlowSender(Transmitter& transmitter, QueueWrapper<TLP*>& listenOn) {
	while (true) {
		// popAll() waits if the queue is empty
		transmitter.sendSequence(listenOn.popAll());
	}
}


void normalFlowReceiver(Receiver& receiver, QueueWrapper<Flit*>& listenOn) {
	while (true) {
		// popAll() waits if the queue is empty
		receiver.receiveFlit(listenOn.popAll());
	}
}