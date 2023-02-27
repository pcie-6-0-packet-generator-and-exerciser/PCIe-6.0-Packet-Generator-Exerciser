#pragma once
#include "./globals.h"
#include "../utils/queue_wrapper.h"
#include "../utils/dllp.h"
#include "./Sequence.h"
#include "./Flit.h"
#include "./Transmitter.h"
#include "./Reciever.h"

/**
 * @brief class that contains functions for managing threads 
*/
class ThreadsFunctions {
public:
	void initializationSender(Globals& globals, QueueWrapper<Sequence> listenOn, QueueWrapper<Flit> sendOn);
	void initializationReceiver(Globals& globals, QueueWrapper<Flit> listenOn, QueueWrapper<Sequence> sendOn);
	void normalFlowSender(Transmitter& transmitter, QueueWrapper<Sequence> listenOn);
	void normalFlowReceiver(Reciever& reciever, QueueWrapper<Flit> listenOn);
};