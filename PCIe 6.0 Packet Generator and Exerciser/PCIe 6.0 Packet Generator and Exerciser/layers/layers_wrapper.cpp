#include "layers_wrapper.h"
#include "../utils/dllp.h"

void LayersWrapper::sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) {
	static bool sharedturn = true;
	static int intCreditType = 0; // P credit type
	int credits[2] = { -1 };

	switch (intCreditType)
	{
		// P credits
	case 0:
		credits[0] = sharedturn ? globals.P_SHARED_CREDIT_LIMIT[0] : globals.P_DEDICATED_CREDIT_LIMIT[0];
		credits[1] = sharedturn ? globals.P_SHARED_CREDIT_LIMIT[0] : globals.P_DEDICATED_CREDIT_LIMIT[0];
		break;
		// NP credits
	case 1:
		credits[0] = sharedturn ? globals.NP_SHARED_CREDIT_LIMIT[0] : globals.NP_DEDICATED_CREDIT_LIMIT[0];
		credits[1] = sharedturn ? globals.NP_SHARED_CREDIT_LIMIT[0] : globals.NP_DEDICATED_CREDIT_LIMIT[0];
		break;
		// CPL credits
	case 2:
		credits[0] = sharedturn ? globals.CPL_SHARED_CREDIT_LIMIT[0] : globals.CPL_DEDICATED_CREDIT_LIMIT[0];
		credits[1] = sharedturn ? globals.CPL_SHARED_CREDIT_LIMIT[0] : globals.CPL_DEDICATED_CREDIT_LIMIT[0];
		break;
	}

	// Push the Flit to the queue
	sendOn->push(
		// Add the Dllp and the CRC to the Flit
		datalink->prepareFlit(
			new Flit(),
			dllpType,
			static_cast<Dllp::CreditType>(intCreditType),
			sharedturn,
			credits
		)
	);

	// Update the shared turn and credits type
	sharedturn ^= 1;
	intCreditType = (intCreditType + 1) % 3;
}

void LayersWrapper::sendPayloadFlit(Globals& globals, queue<TLP*>& packets, QueueWrapper<Flit*>& sendOnQueue) {
	queue<Flit*> flitsToSend;
	Flit* flit = new Flit();
	int flitIndexInBytes = 0;
	int packetIndexInBytes = 0;
	bool nextTLP = true;
	TLP* packet;
	boost::dynamic_bitset<> bitRep;
	// For each packet, call checkGateEquation to see if it can be sent
	while (!packets.empty()) {
		if (nextTLP) {
			packet = packets.front();
			bitRep = packet->getBitRep();
			bitRep.resize(236 * 8, false);
			packets.pop();
			packetIndexInBytes = 0;
		}
		if (transaction->checkGateEquation(globals, packet)) {
			// If it can be sent, check if the current half of the flit contains less than 8 TLPs
			if (flitIndexInBytes >= 128 ? flit->secondHalfTLPCount < 8 : flit->firstHalfTLPCount < 8) {
				// If it does, check if what's left of the TLP can fit in what's remaining of the flit
				if (flitIndexInBytes + (packet->getTotalLength() - packetIndexInBytes) <= 236) {
					// If it does, then add what's left of the TLP, and return to the beginning of the loop with taking the next TLP
					if (flitIndexInBytes >= 128) {
						flit->secondHalfTLPCount++;
					}
					else {
						flit->firstHalfTLPCount++;
						if (flitIndexInBytes + packet->getTotalLength() - packetIndexInBytes > 128)
							flit->secondHalfTLPCount++;
					}
					flit->TLPPayload.operator|=(bitRep.operator<<((236 - flitIndexInBytes - (packet->getTotalLength() - packetIndexInBytes)) * 8));
					flitIndexInBytes += packet->getTotalLength() - packetIndexInBytes;
					nextTLP = true;
					updateConsumedCredits(globals, packet->creditConsumedType, packet->headerConsumption, packet->dataConsumption);
				}
				// If it doesn't, add what can fit, send the current flit, and return to the beginning of the loop without taking the next TLP
				else {
					flit->TLPPayload.operator|=(bitRep.operator>>((236 - flitIndexInBytes - (packet->getTotalLength() - packetIndexInBytes)) * -8));
					packetIndexInBytes += 236 - flitIndexInBytes;
					bitRep.resize((packet->getTotalLength() - packetIndexInBytes)*8);
					bitRep.resize(236*8, false);
					nextTLP = false;
					pushReadyFlit(globals, flit, flitsToSend);
					flit = new Flit();
					flitIndexInBytes = 0;
				}
			}
			// If it doesn't, check if the current half is the first half
			else {
				if (flitIndexInBytes < 128) {
					flitIndexInBytes = 128;
					// If it is, check if the second half contains less than 8 TLPs
					if (flit->secondHalfTLPCount < 8) {
						// If it does, check if what's left of the TLP can fit in what's remaining of the flit
						if (flitIndexInBytes + (packet->getTotalLength() - packetIndexInBytes) <= 236) {
							// If it does, then add what's left of the TLP, and return to the beginning of the loop
							flit->secondHalfTLPCount++;
							flit->TLPPayload.operator|=(bitRep.operator<<((236 - flitIndexInBytes - (packet->getTotalLength() - packetIndexInBytes)) * 8));
							flitIndexInBytes += packet->getTotalLength() - packetIndexInBytes;
							nextTLP = true;
							updateConsumedCredits(globals, packet->creditConsumedType, packet->headerConsumption, packet->dataConsumption);
						}
						// If it doesn't, add what can fit, send the current flit, and return to the beginning of the loop without taking the next TLP
						else {
							flit->TLPPayload.operator|=(bitRep.operator>>((236 - flitIndexInBytes - (packet->getTotalLength() - packetIndexInBytes)) * -8));
							packetIndexInBytes += 236 - flitIndexInBytes;
							bitRep.resize((packet->getTotalLength() - packetIndexInBytes)*8);
							bitRep.resize(236*8, false);
							nextTLP = false;
							pushReadyFlit(globals, flit, flitsToSend);
							flit = new Flit();
							flitIndexInBytes = 0;
						}
					}
					// If it doesn't, then send the current flit, and return to the beginning of the loop without taking the next TLP
					else {
						nextTLP = false;
						pushReadyFlit(globals, flit, flitsToSend);
						flit = new Flit();
						flitIndexInBytes = 0;
					}
				}
				// If it isn't, then send the current flit, and return to the beginning of the loop without taking the next TLP
				else {
					nextTLP = false;
					pushReadyFlit(globals, flit, flitsToSend);
					flit = new Flit();
					flitIndexInBytes = 0;
				}
			}
				
		}
		else {
			// If it can't be sent, then send the current flit, and return to the beginning of the loop without taking the next TLP
			nextTLP = false;
			pushReadyFlit(globals, flit, flitsToSend);
			flit = new Flit();
			flitIndexInBytes = 0;
		}
	}
	sendOnQueue.push(flitsToSend);
}

void LayersWrapper::pushReadyFlit(Globals globals, Flit* flit, queue<Flit*>& queue) {
	static int creditCounter = 0;
	Dllp::CreditType creditType;
	bool shared;
	int* credit;
	switch (creditCounter)
	{
	case 0:
		creditType = Dllp::CreditType::P;
		shared = true;
		credit = globals.P_SHARED_CREDIT;
		break;
	case 1:
		creditType = Dllp::CreditType::NP;
		shared = true;
		credit = globals.NP_SHARED_CREDIT;
		break;
	case 2:
		creditType = Dllp::CreditType::Cpl;
		shared = true;
		credit = globals.CPL_SHARED_CREDIT;
		break;
	case 3:
		creditType = Dllp::CreditType::P;
		shared = false;
		credit = globals.P_DEDICATED_CREDIT;
		break;
	case 4:
		creditType = Dllp::CreditType::NP;
		shared = false;
		credit = globals.NP_DEDICATED_CREDIT;
		break;
	case 5:
		creditType = Dllp::CreditType::Cpl;
		shared = false;
		credit = globals.CPL_DEDICATED_CREDIT;
		break;
	default:
		break;
	}
	creditCounter = (creditCounter + 1) % 6;
	flit = datalink->prepareFlit(flit, Dllp::DllpType::updateFC, creditType, shared, credit);
	queue.push(flit);
}

void LayersWrapper::updateConsumedCredits(Globals& globals, Dllp::CreditType creditType, int headerConsumption, int dataConsumption) {
	int *creditConsumed;
	const int headerFieldSize = 8;
	const int dataFieldSize = 12;
	switch (creditType) {
		case Dllp::CreditType::P:
			creditConsumed = globals.P_SHARED_CREDITS_CONSUMED;
			break;
		case Dllp::CreditType::NP:
			creditConsumed = globals.NP_SHARED_CREDITS_CONSUMED;
			break;
		case Dllp::CreditType::Cpl:
			creditConsumed = globals.CPL_SHARED_CREDITS_CONSUMED;
			break;
	}
	creditConsumed[0] = (creditConsumed[0] + headerConsumption) % (int)pow(2, headerFieldSize);
	creditConsumed[1] = (creditConsumed[1] + dataConsumption) % (int)pow(2, dataFieldSize);
}
