#include "thread_functions.h"
#include <thread>
#include "transmitter.h"

void normalFlowSender(Transmitter& transmitter, QueueWrapper<TLP*>& listenOn) {
	while (true) {
		// popAll() waits if the queue is empty
		transmitter.sendSequence(listenOn.popAll());
	}
}

void initilizationSender(Globals& globals, QueueWrapper<TLP*>& queueListenOn, QueueWrapper<Flit*>& queueSendOn) {
	auto* transmitter = new Transmitter(globals, &queueSendOn);
	while (!globals.Fl1) {
		transmitter->sendInitFC1();
	}
	while (!globals.Fl2) {
		transmitter->sendInitFC2();
	}
	std::thread normalFlowSenderThread(normalFlowSender, std::ref(*transmitter), std::ref(queueListenOn));
	normalFlowSenderThread.join();
}
