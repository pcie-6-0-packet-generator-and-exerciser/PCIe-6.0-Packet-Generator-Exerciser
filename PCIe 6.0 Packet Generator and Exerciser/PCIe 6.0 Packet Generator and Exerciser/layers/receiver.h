#pragma once
#include "./globals.h"
#include "./layersWrapper.h"
#include "../utils/queue_wrapper.h"
#include "flit.h/"
#include <vector>

class Receiver {
public:
	Globals globals;
	LayersWrapper layers;
	QueueWrapper<Flit> sendOn;

	Receiver(Globals global,LayersWrapper layer,QueueWrapper<Flit> sendOnQueue);

	void receiveInit(Flit flit);
	void receiveFlit(Flit flit);
};

