#include "layers_wrapper.h"
#include "../utils/dllp.h"
#include "../utils/tlp.h"

void LayersWrapper::sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) {
	static bool sharedturn = true;
	static int intCreditType = 0; // P credit type
	int credits[2] = { -1 };

	switch (intCreditType)
	{
		// P credits
	case 0:
		credits[0] = sharedturn ? globals.P_SHARED_CREDIT[0] : globals.P_DEDICATED_CREDIT[0];
		credits[1] = sharedturn ? globals.P_SHARED_CREDIT[1] : globals.P_DEDICATED_CREDIT[1];
		break;
		// NP credits
	case 1:
		credits[0] = sharedturn ? globals.NP_SHARED_CREDIT[0] : globals.NP_DEDICATED_CREDIT[0];
		credits[1] = sharedturn ? globals.NP_SHARED_CREDIT[1] : globals.NP_DEDICATED_CREDIT[1];
		break;
		// CPL credits
	case 2:
		credits[0] = sharedturn ? globals.CPL_SHARED_CREDIT[0] : globals.CPL_DEDICATED_CREDIT[0];
		credits[1] = sharedturn ? globals.CPL_SHARED_CREDIT[1] : globals.CPL_DEDICATED_CREDIT[1];
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
	bool isPartialTLP = false;
	TLP* packet;
	boost::dynamic_bitset<> bitRep;

	
	// For each packet, call checkGateEquation to see if it can be sent
	while (!packets.empty() or isPartialTLP) {
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
					isPartialTLP = false;
					updateConsumedCredits(globals, packet->creditConsumedType, packet->headerConsumption, packet->dataConsumption);
				}
				// If it doesn't, add what can fit, send the current flit, and return to the beginning of the loop without taking the next TLP
				else {
					flit->TLPPayload.operator|=(bitRep.operator>>((236 - flitIndexInBytes - (packet->getTotalLength() - packetIndexInBytes)) * -8));
					packetIndexInBytes += 236 - flitIndexInBytes;
					bitRep.resize((packet->getTotalLength() - packetIndexInBytes) * 8);
					bitRep.resize(236 * 8, false);
					nextTLP = false;
					isPartialTLP = true;
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
							isPartialTLP = false;
							updateConsumedCredits(globals, packet->creditConsumedType, packet->headerConsumption, packet->dataConsumption);
						}
						// If it doesn't, add what can fit, send the current flit, and return to the beginning of the loop without taking the next TLP
						else {
							flit->TLPPayload.operator|=(bitRep.operator>>((236 - flitIndexInBytes - (packet->getTotalLength() - packetIndexInBytes)) * -8));
							packetIndexInBytes += 236 - flitIndexInBytes;
							bitRep.resize((packet->getTotalLength() - packetIndexInBytes) * 8);
							bitRep.resize(236 * 8, false);
							nextTLP = false;
							isPartialTLP = true;
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
	if (nextTLP) pushReadyFlit(globals, flit, flitsToSend);
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
	int* creditConsumed;
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

void LayersWrapper::receiveNOPFlit(Flit* flit, Globals& globals) {
	//First passes the FLIT to checkCRC()
	if (datalink->checkCRC(flit)) {
		//updateCreditLimit(Flit flit, int P_SHARED_CREDIT_LIMIT[], int NP_SHARED_CREDIT_LIMIT[], int CPL_SHARED_CREDIT_LIMIT[], int P_DEDICATED_CREDIT_LIMIT[], int NP_DEDICATED_CREDIT_LIMIT[], int CPL_DEDICATED_CREDIT_LIMIT[], bool& FI1, bool& FI2) {
		datalink->updateCreditLimit(flit, globals.P_SHARED_CREDIT_LIMIT, globals.NP_SHARED_CREDIT_LIMIT, globals.CPL_SHARED_CREDIT_LIMIT, globals.P_DEDICATED_CREDIT_LIMIT, globals.NP_DEDICATED_CREDIT_LIMIT, globals.CPL_DEDICATED_CREDIT_LIMIT, globals.Fl1, globals.Fl2);
	}
	else {
		//cout Error
	}
}

int getHeaderLengthByType(TLPType type) {
	switch (type) {
	case TLPType::MemRead32:
		return 12;
		break;
	case TLPType::MemWrite32:
		return 12;
		break;
	case TLPType::MemRead64:
		return 16;
		break;
	case TLPType::MemWrite64:
		return 16;
		break;
	case TLPType::Cpl:
		return 12;
		break;
	case TLPType::CplD:
		return 16;
		break;
	case TLPType::VendorMsg:
		return 12;
		break;
	case TLPType::ConfigRead0:
		return 12;
		break;
	case TLPType::ConfigWrite0:
		return 12;
		break;
	case TLPType::ConfigRead1:
		return 16;
		break;
	case TLPType::ConfigWrite1:
		return 16;
		break;
	default:
		break;
	}
}

void LayersWrapper::receivePayloadFlit(Globals& globals, std::queue<Flit*> flits, QueueWrapper<TLP*>& sendOn)
{
	std::queue<TLP*> extractedTLPs;
	Flit* flit;
	bool nextFlit = true;
	int flitIndexinBytes = 0;
	boost::dynamic_bitset<> payload;
	while (!flits.empty())
	{
		if (nextFlit)
		{
			flit = flits.front();
			flits.pop();
			flitIndexinBytes = 0;
			if (!datalink->checkCRC(flit)) {
				// malformed
			}
			datalink->updateCreditLimit(flit, globals.P_SHARED_CREDIT_LIMIT, globals.NP_SHARED_CREDIT_LIMIT, globals.CPL_SHARED_CREDIT_LIMIT, globals.P_DEDICATED_CREDIT_LIMIT, globals.NP_DEDICATED_CREDIT_LIMIT, globals.CPL_DEDICATED_CREDIT_LIMIT, globals.Fl1, globals.Fl2);
			payload = flit->TLPPayload;
		}
		boost::dynamic_bitset<> tlpCommonHeader(4 * 8);
		int type;
		// Try to extract TLP type. Keep on iterating on bytes until type is not 0
		do {
			type = (payload.operator>>((236 - flitIndexinBytes - 1) * 8)).to_ulong();
			flitIndexinBytes++;
			payload.resize((236 - flitIndexinBytes) * 8);
			payload.resize(236 * 8);
		} while (type == 0 && flitIndexinBytes < 236);
		// Get next flit if reached end of flit. TODO: refactor
		if (type == 0 && flitIndexinBytes == 236) {
			nextFlit = true;
			continue;
		}
		// Put type at beginning of TLP
		tlpCommonHeader |= (boost::dynamic_bitset(4 * 8, type)).operator<<((4 - 1) * 8);
		payload.resize((236 - flitIndexinBytes) * 8);
		payload.resize(236 * 8);
		// Add rest of common header to tlpCommonHeader
		if (flitIndexinBytes + 3 > 236) {
			int bytesToAdd = 236 - flitIndexinBytes;
			// Add what can fit
			tlpCommonHeader.resize(236 * 8);
			tlpCommonHeader.operator=((tlpCommonHeader.operator>>((4 - 1 - bytesToAdd) * 8).operator|=(payload)).operator<<((4 - 1 - bytesToAdd) * 8));
			// Get next flit
			flit = flits.front();
			flits.pop();
			flitIndexinBytes = 0;
			if (!datalink->checkCRC(flit)) {
				// malformed
			}
			datalink->updateCreditLimit(flit, globals.P_SHARED_CREDIT_LIMIT, globals.NP_SHARED_CREDIT_LIMIT, globals.CPL_SHARED_CREDIT_LIMIT, globals.P_DEDICATED_CREDIT_LIMIT, globals.NP_DEDICATED_CREDIT_LIMIT, globals.CPL_DEDICATED_CREDIT_LIMIT, globals.Fl1, globals.Fl2);
			payload = flit->TLPPayload;
			// Add the rest
			bytesToAdd = 3 - bytesToAdd;
			tlpCommonHeader.operator|=(payload.operator>>((236 - bytesToAdd) * 8));
			tlpCommonHeader.resize(4 * 8);
			flitIndexinBytes += bytesToAdd;
			payload.resize((236 - flitIndexinBytes) * 8);
			payload.resize(236 * 8);
		}
		else {
			tlpCommonHeader.resize(236 * 8);
			tlpCommonHeader.operator|=(payload.operator>>((236 - flitIndexinBytes - 3) * 8));
			tlpCommonHeader.resize(4 * 8);
			flitIndexinBytes += 3;
			payload.resize((236 - flitIndexinBytes) * 8);
			payload.resize(236 * 8);
		}
		// Extract length
		boost::dynamic_bitset<> length(4 * 8);
		length.operator=(tlpCommonHeader);
		length.resize(10);
		int payloadLength = length.to_ulong();
		int headerLength = getHeaderLengthByType(static_cast<TLPType>(type));
		boost::dynamic_bitset<> tlpWholeHeader(headerLength * 8);
		// Add common header to tlpWholeHeader
		tlpCommonHeader.resize(tlpWholeHeader.size());
		tlpWholeHeader.operator|=(tlpCommonHeader);
		tlpWholeHeader.operator<<((headerLength - 4) * 8);
		// Add rest of header to tlpWholeHeader
		if (flitIndexinBytes + (headerLength - 4) > 236) {
			int bytesToAdd = 236 - flitIndexinBytes;
			// Add what can fit
			tlpWholeHeader.resize(236 * 8);
			tlpWholeHeader.operator=((tlpWholeHeader.operator>>((headerLength - 4 - bytesToAdd) * 8).operator|=(payload)).operator<<((headerLength - 4 - bytesToAdd) * 8));
			// Get next flit
			flit = flits.front();
			flits.pop();
			flitIndexinBytes = 0;
			if (datalink->checkCRC(flit)) {
				// malformed
			}
			datalink->updateCreditLimit(flit, globals.P_SHARED_CREDIT_LIMIT, globals.NP_SHARED_CREDIT_LIMIT, globals.CPL_SHARED_CREDIT_LIMIT, globals.P_DEDICATED_CREDIT_LIMIT, globals.NP_DEDICATED_CREDIT_LIMIT, globals.CPL_DEDICATED_CREDIT_LIMIT, globals.Fl1, globals.Fl2);
			payload = flit->TLPPayload;
			// Add the rest
			bytesToAdd = headerLength - 4 - bytesToAdd;
			tlpWholeHeader.operator|=(payload.operator>>((236 - bytesToAdd) * 8));
			tlpWholeHeader.resize(headerLength * 8);
			flitIndexinBytes += bytesToAdd;
			payload.resize((236 - flitIndexinBytes) * 8);
			payload.resize(236 * 8);
		}
		else {
			tlpWholeHeader.resize(236 * 8);
			tlpWholeHeader.operator|=(payload.operator>>((236 - flitIndexinBytes - (headerLength - 4)) * 8));
			flitIndexinBytes += 3;
			payload.resize((236 - flitIndexinBytes - (headerLength - 4)) * 8);
			payload.resize(236 * 8);
		}
		// Extract payload
		boost::dynamic_bitset<> tlpPayload(0);
		if (auto tlpType = static_cast<TLPType>(type); tlpType == TLPType::MemWrite32 || tlpType == TLPType::MemWrite64 || tlpType == TLPType::CplD || tlpType == TLPType::ConfigWrite0 || tlpType == TLPType::ConfigWrite1) {
			if (payloadLength == 0) payloadLength = 1024;
			payloadLength *= 4;
			tlpPayload.resize(payloadLength * 8);
			int addedBytes = 0;
			int bytesRemaining = payloadLength;
			while (bytesRemaining > 0) {
				if (flitIndexinBytes + bytesRemaining > 236) {
					int bytesToAdd = 236 - flitIndexinBytes;
					// Add what can fit
					payload.resize(payloadLength * 8);
					tlpPayload.operator=((tlpPayload.operator>>((payloadLength - addedBytes - bytesToAdd) * 8).operator|=(payload)).operator<<((payloadLength - addedBytes - bytesToAdd) * 8));
					addedBytes += bytesToAdd;
					bytesRemaining -= bytesToAdd;
					// Get next flit
					flit = flits.front();
					flits.pop();
					flitIndexinBytes = 0;
					if (datalink->checkCRC(flit)) {
						// malformed
					}
					datalink->updateCreditLimit(flit, globals.P_SHARED_CREDIT_LIMIT, globals.NP_SHARED_CREDIT_LIMIT, globals.CPL_SHARED_CREDIT_LIMIT, globals.P_DEDICATED_CREDIT_LIMIT, globals.NP_DEDICATED_CREDIT_LIMIT, globals.CPL_DEDICATED_CREDIT_LIMIT, globals.Fl1, globals.Fl2);
					payload = flit->TLPPayload;
				}
				else {
					boost::dynamic_bitset<> payloadCopy(236 * 8);
					payloadCopy = payload.operator>>((236 - flitIndexinBytes - bytesRemaining) * 8);
					payloadCopy.resize(tlpPayload.size());
					tlpPayload.operator|=(payloadCopy);
					flitIndexinBytes += bytesRemaining;
					payload.resize((236 - flitIndexinBytes) * 8);
					payload.resize(236 * 8);
				}
			}
			tlpPayload.resize(payloadLength * 8);
		}
		boost::dynamic_bitset<> tlpWhole(tlpWholeHeader.size() + tlpPayload.size());
		tlpWholeHeader.resize(tlpWhole.size());
		tlpWhole.operator|=(tlpWholeHeader);
		tlpWhole.operator<<(tlpWhole.size() - tlpWholeHeader.size());
		tlpPayload.resize(tlpWhole.size());
		tlpWhole.operator|=(tlpPayload);
		TLP* tlp = TLP::getObjRep(tlpWhole);
		extractedTLPs.push(tlp);
		updateAllocatedCredits(globals, tlp->creditConsumedType, tlp->headerConsumption, tlp->dataConsumption);
	}
	sendOn.push(extractedTLPs);
}

void LayersWrapper::updateAllocatedCredits(Globals& globals, Dllp::CreditType creditType, int headerConsumption, int dataConsumption) {
	int* creditAllocated;
	const int headerFieldSize = 8;
	const int dataFieldSize = 12;
	switch (creditType) {
	case Dllp::CreditType::P:
		creditAllocated = globals.P_SHARED_CREDIT;
		break;
	case Dllp::CreditType::NP:
		creditAllocated = globals.NP_SHARED_CREDIT;
		break;
	case Dllp::CreditType::Cpl:
		creditAllocated = globals.CPL_SHARED_CREDIT;
		break;
	}
	creditAllocated[0] = (creditAllocated[0] + headerConsumption) % (int)pow(2, headerFieldSize);
	creditAllocated[1] = (creditAllocated[1] + dataConsumption) % (int)pow(2, dataFieldSize);
}
