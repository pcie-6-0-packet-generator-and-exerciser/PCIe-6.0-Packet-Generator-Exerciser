#pragma once
#include "./globals.h"
#include "./layersWrapper.h"
#include "../utils/queue_wrapper.h"
#include "flit.h/"

class Receiver {
public:
	Globals globals;
	LayersWrapper layers;
	QueueWrapper<Flit> listenOn;
	QueueWrapper<Flit> sendOn;

	void receiveInit(void);
	void receiveFlit(void);
};

