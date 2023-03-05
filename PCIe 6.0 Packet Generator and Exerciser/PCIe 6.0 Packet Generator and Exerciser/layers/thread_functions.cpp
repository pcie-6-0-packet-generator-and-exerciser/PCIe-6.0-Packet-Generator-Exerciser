#include "thread_functions.h"
#include <thread>

void normalFlowSender(Transmitter& transmitter, QueueWrapper<TLP*>& listenOn) {
	while (true) {
		// popAll() waits if the queue is empty
		transmitter.sendSequence(listenOn.popAll());
	}
}

void initilizationSender(Globals globals, QueueWrapper<Sequence> queueListenOn, QueueWrapper<Flit> queueSendOn) {
	Transmitter transmitter = new Transmitter(globals, NULL, queueSendOn);
	while (!globals.Fl1) {
		transmitter.sendInitFC1();
	}
	while (!globals.Fl2) {
		transmitter.sendInitFC2();
	}
	std::thread normalFlowSender(globals, queueListenOn, queueSendOn);
	normalFlowSender.join();
}
