#include "./threads_functions.h"
#include <thread>

void initializationReceiver(Globals& globals, QueueWrapper<Flit> listenOn, QueueWrapper<Sequence> sendOn) {
	auto receiver = new Receiver(globals, sendOn);
	while (!globals.Fl1) {
		receiver.sendInitFC1();
	}
	while (!globals.Fl2) {
		receiver.sendInitFC2();
	}
	std::thread receiverNormalFlowThread(normalFlowReceiver, receiver, listenOn);
	receiverNormalFlowThread.join();
}
