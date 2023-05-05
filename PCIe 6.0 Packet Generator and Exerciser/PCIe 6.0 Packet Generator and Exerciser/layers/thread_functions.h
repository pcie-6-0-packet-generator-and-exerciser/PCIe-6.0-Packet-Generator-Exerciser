#pragma once
#include "./globals.h"
#include "./transmitter.h"
#include "../utils/queue_wrapper.h"


/** 
 * @brief Listen continuously on a queue until it is not empty, then send the sequence of TLPs on the transmitter.
 * @param transmitter takes the sequence of TLPs and sends them over the network
 * @param listenOn the queue which is listened on
 */
void noramlFlowSender(Transmitter& transmitter, QueueWrapper<TLP*>& listenOn);