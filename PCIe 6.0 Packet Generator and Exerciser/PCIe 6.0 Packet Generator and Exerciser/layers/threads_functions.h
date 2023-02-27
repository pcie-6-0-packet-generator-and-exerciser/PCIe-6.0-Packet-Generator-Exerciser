#pragma once
#include "./globals.h"
#include "../utils/queue_wrapper.h"
#include "../utils/dllp.h"
#include "./Sequence.h"
#include "./Flit.h"
#include "./Transmitter.h"
#include "./Reciever.h"

class ThreadsFunctions {
public:
	void initializationSender(Transmitter& transmitter, Globals& globals, QueueWrapper<Sequence> listenOn, QueueWrapper<Flit> sendOn);
	void initializationReceiver(Reciever& reciever, Globals& globals, QueueWrapper<Flit> listenOn, QueueWrapper<Sequence> sendOn);
	void normalFlowSender(Transmitter& transmitter, Globals& globals, QueueWrapper<Sequence> listenOn, QueueWrapper<Flit> sendOn);
	void normalFlowReceiver(Reciever& reciever, Globals& globals, QueueWrapper<Flit> listenOn, QueueWrapper<Sequence> sendOn);
};