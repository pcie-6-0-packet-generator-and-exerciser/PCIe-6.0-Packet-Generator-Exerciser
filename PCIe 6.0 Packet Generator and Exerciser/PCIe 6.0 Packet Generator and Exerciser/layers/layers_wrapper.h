#pragma once
#include "../utils/queue_wrapper.h"
#include "globals.h"
#include "sequence.h"
#include "flit.h"
#include "datalink.h"
#include "transaction_layer.h"
#include "../utils/tlp.h"
#include <queue>

class LayersWrapper {
	private:

	/**
	 * @brief This is a utility function used by sendPayloadFlit. It performs a round-robin on all 6 credit types and calls the sendFlit function in the datalink layer
	 * @param globals The globals object containing the credits tracked by this device
	 * @param flit The flit to be sent
	 * @param queue The queue on which the flit should be sent
	*/
	void pushReadyFlit(Globals globals, Flit* flit, queue<Flit*>& queue);
	/**
	 * @brief This is a utility function used by sendPayloadFlit. It updates the credits tracked by this device
	 * @param globals The globals object containing the credits tracked by this device
	 * @param creditType The type of credit consumed by the packet being sent
	 * @param headerConsumption The amount of header credits consumed by the packet being sent
	 * @param dataConsumption The amount of data credits consumed by the packet being sent
	*/
	void updateConsumedCredits(Globals& globals, Dllp::CreditType creditType, int headerConsumption, int dataConsumption);

	void updateAllocatedCredits(Globals& globals, Dllp::CreditType creditType, int headerConsumption, int dataConsumption);

public:	

	TransactionLayer* transaction;
	DatalinkLayer* datalink;

	/**
	 * @brief Sends NOP Flit to the specified queue
	 * This function sends NOP Flits to the specified queue for each credit type.
	 * @param P_CREDIT an array of two integers representing the available P credits
	 * @param NP_CREDIT an array of two integers representing the available NP credits
	 * @param CPL_CREDIT an array of two integers representing the available CPL credits
	 * @param dllpType the DLLP type for the NOP Flits
	 * @param sendOn a pointer to a QueueWrapper object where the NOP Flit queue will be pushed
	 * @return void
	*/
	void sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn);

	/**
	 * @brief This function is used to send a payload flit. It splits the received queue of TLPs on flits according to the PCIe 6.0 spec
	 * @param globals The globals object containing the credits tracked by this device
	 * @param packets The queue of packets to be sent to the other device
	 * @param sendOnQueue The queue on which the packets should be sent
	*/
	void sendPayloadFlit(Globals& globals, queue<TLP*>& packets, QueueWrapper<Flit*>& sendOnQueue);


	/**
	 * @brief This function is used to receive nop flits
	 * @param globals The globals object containing the credits tracked by this device
	 * @param flit flit to checkcrc on it
	*/
	void receiveNOPFlit(Flit* flit, Globals& globals);

	void receivePayloadFlit(Globals& globals, std::queue<Flit*> flits, QueueWrapper<TLP*>& sendOn);
};
