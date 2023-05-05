#include "thread_functions.h"

void noramlFlowSender(Transmitter& transmitter, QueueWrapper<TLP*>& listenOn) {
	while (true) {
		// Wait until the queue is not empty
		if (!listenOn.size()) {
			transmitter.sendSequence(listenOn.popAll());
		}
	}
}