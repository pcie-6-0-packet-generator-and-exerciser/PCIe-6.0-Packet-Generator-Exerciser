#include "thread_functions.h"
#include "transmitter.h"
#include "receiver.h"
#include <thread>

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


void normalFlowReceiver(Receiver& receiver, QueueWrapper<Flit*>& listenOn) {
	while (true) {
		// popAll() waits if the queue is empty
		receiver.receiveFlit(listenOn.popAll());
	}
}

void initializationReceiver(Globals& globals, QueueWrapper<Flit*>& listenOn, QueueWrapper<TLP*>& sendOn, QueueWrapper<Flit*>& transmitterSendOn) {
	Receiver* receiever = new Receiver(globals, LayersWrapper(), sendOn);
	while (!globals.Fl1 or !globals.Fl2) {
		// pop() waits if the queue is empty
		receiever->receiveInit(listenOn.pop(), globals);
		if (globals.Fl1) {
			auto* transmitter = new Transmitter(globals, &transmitterSendOn);
			transmitter->sendInitFC2();
			delete transmitter;
		}
	}
	std::thread normalFlowReceiverThread(normalFlowReceiver, std::ref(*receiever), std::ref(listenOn));
	normalFlowReceiverThread.join();
}