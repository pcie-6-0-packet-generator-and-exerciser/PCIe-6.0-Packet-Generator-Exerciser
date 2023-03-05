#pragma once
#include "../utils/queue_wrapper.h"
#include "globals.h"
#include "sequence.h"
#include "flit.h"

/**
 * @brief This function is meant to be used to create a thread for each of the root-complex and endpoint
 * @param globals Globals object corresponding to either the root-complex or the endpoint
 * @param queueListenOn The QueueWrapper that the layers will receive TLPs from
 * @param queueSendOn The QueueWrapper that the layers will send on to layers of the other side
*/
void initilizationSender(Globals globals, QueueWrapper<Sequence> queueListenOn, QueueWrapper<Flit> queueSendOn);
