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

/**
 * @brief This function is meant to be used to create a thread for each of the root-complex and endpoint
 * @param globals Globals object corresponding to either the root-complex or the endpoint
 * @param queueListenOn The QueueWrapper that the layers will receive TLPs from
 * @param queueSendOn The QueueWrapper that the layers will send on to layers of the other side
*/
void initilizationSender(Globals& globals, QueueWrapper<TLP*>& queueListenOn, QueueWrapper<Flit*>& queueSendOn);

/**
 * @brief Creates a receiver, waits until Fl1, Fl2 flags are set then starts the normal flow receiver thread.
 * @param globals used to create the receiver object, and to check the Fl1, Fl2 flags
 * @param listenOn used to listen on the queue
 * @param sendTo used to create the receiver object
*/
void initializationReceiver(Globals& globals, QueueWrapper<TLP*>& listenOn, QueueWrapper<Flit*>& sendTo);