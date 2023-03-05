#pragma once
#include "./globals.h"
#include "./transmitter.h"
#include "../utils/queue_wrapper.h"
#include "flit.h"

/** 
 * @brief Listen continuously on a queue until it is not empty, then send the sequence of TLPs on the transmitter.
 * @param transmitter takes the sequence of TLPs and sends them over the network
 * @param listenOn the queue which is listened on
 */
void normalFlowSender(Transmitter& transmitter, QueueWrapper<TLP*>& listenOn);
#include "../utils/queue_wrapper.h"
#include "globals.h"
#include "sequence.h"

/**
 * @brief This function is meant to be used to create a thread for each of the root-complex and endpoint
 * @param globals Globals object corresponding to either the root-complex or the endpoint
 * @param queueListenOn The QueueWrapper that the layers will receive TLPs from
 * @param queueSendOn The QueueWrapper that the layers will send on to layers of the other side
*/
void initilizationSender(Globals globals, QueueWrapper<Sequence> queueListenOn, QueueWrapper<Flit> queueSendOn);
