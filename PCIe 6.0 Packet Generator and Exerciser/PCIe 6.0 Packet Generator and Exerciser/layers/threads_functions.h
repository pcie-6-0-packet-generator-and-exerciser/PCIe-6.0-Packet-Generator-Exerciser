#pragma once
#include "./globals.h"
#include "../utils/queue_wrapper.h"
#include "./Sequence.h"
#include "./Flit.h"
#include "./Transmitter.h"
#include "./Receiver.h"

/**
 * @brief class that contains functions for managing threads 
*/
class ThreadsFunctions {
public:
	void initializationSender(Globals& globals, QueueWrapper<Sequence> listenOn, QueueWrapper<Flit> sendOn);
	void initializationReceiver(Globals& globals, QueueWrapper<Flit> listenOn, QueueWrapper<Sequence> sendOn);
	void normalFlowSender(Transmitter& transmitter, Globals& globals, QueueWrapper<Sequence> listenOn, QueueWrapper<Flit> sendOn);
	void normalFlowReceiver(Receiver& receiver, Globals& globals, QueueWrapper<Flit> listenOn, QueueWrapper<Sequence> sendOn);
};