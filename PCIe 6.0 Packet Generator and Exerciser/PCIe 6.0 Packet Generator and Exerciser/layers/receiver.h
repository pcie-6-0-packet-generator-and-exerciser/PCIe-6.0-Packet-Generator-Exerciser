#pragma once
#include "./globals.h"
#include "layers_wrapper.h"
#include "../utils/queue_wrapper.h"
#include "flit.h"
#include <vector>

class Receiver {
public:
	Globals globals;
	LayersWrapper layers;
	QueueWrapper<TLP*>& sendOn;

	Receiver(Globals& global, LayersWrapper layer, QueueWrapper<TLP*>& sendOnQueue);

	void receiveInit(Flit* flit, Globals& globals);
	void receiveFlit(std::queue<Flit*> flits);

};