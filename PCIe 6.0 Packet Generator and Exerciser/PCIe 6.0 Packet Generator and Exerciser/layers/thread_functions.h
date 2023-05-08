#pragma once
#include "./globals.h"
#include "./transmitter.h"
#include "./receiver.h"
#include "../utils/queue_wrapper.h"
#include "../utils/tlp.h"
#include "./flit.h"

/** 
 * @brief Listen continuously on a queue until it is not empty, then send the sequence of TLPs on the transmitter.
 * @param transmitter takes the sequence of TLPs and sends them over the network
 * @param listenOn the queue which is listened on for TLPs
 */
void normalFlowSender(Transmitter& transmitter, QueueWrapper<TLP*>& listenOn);

/**
 * @brief Listen continuously on a queue until it is not empty, then send the Flit recieved to the transmitter.
 * @param transmitter takes the Flit and extracts the TLPs from it
 * @param listenOn the queue which is listened on for Flits
 */
void normalFlowReceiver(Receiver& receiver, QueueWrapper<Flit*>& listenOn);