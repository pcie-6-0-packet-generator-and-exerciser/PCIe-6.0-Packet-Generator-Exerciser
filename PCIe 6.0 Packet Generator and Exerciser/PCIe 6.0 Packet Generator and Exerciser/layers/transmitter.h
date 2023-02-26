#pragma once
#include "./layersWrapper.h"
#include "./globals.h"
#include "../utils/queue_wrapper.h"
#include "../utils/dllp.h"
#include "../utils/sequence.h"

class Transmitter {
public:
	void sendSequence(Sequence sequence);
};