#pragma once
#include "../layers/layers_wrapper.h"
#include "./globals.h"
#include "../utils/queue_wrapper.h"
#include "../utils/dllp.h"
#include "../utils/tlp.h"
#include "../layers/flit.h"

/**
 * @brief Represents a transmitter that sends packets over a network.
 *
 * This class encapsulates the functionality required to transmit packets over
 * a network using a credit-based flow control mechanism. It maintains a set of
 * global parameters that govern the behavior of the transmitter, as well as a
 * set of wrapper classes that provide access to the various layers of the
 * network protocol.
 */
class Transmitter {
public:
	Globals globals;
	LayersWrapper* layers;
	QueueWrapper<Flit*>* listenOn;
	QueueWrapper<Flit*>* sendOn;

	/**
	 * @brief Sends an InitFC1 message to the receiver.
	 * @param void
	 * @return void
	*/
	void sendInitFC1(void);
	
	/**
	 * @brief Sends an InitFC2 message to the receiver.
	 * @param void
	 * @return void
	*/
	void sendInitFC2(void);
	void sendSequence(vector<TLP>* sequence);
};