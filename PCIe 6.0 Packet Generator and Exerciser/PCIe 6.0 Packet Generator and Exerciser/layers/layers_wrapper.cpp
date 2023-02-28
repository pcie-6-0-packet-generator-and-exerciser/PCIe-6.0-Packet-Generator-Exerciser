#include "layers_wrapper.h"
#include "../utils/dllp.h"

void LayersWrapper::sendPayloadFlit(Globals globals, Sequence sequence, QueueWrapper<Flit> sendOnQueue, int PSharedCreditLimit[2], int NPSharedCreditLimit[2], int CplSharedCreditLimit[2], int PSharedCreditConsumed[2], int NPSharedCreditConsumed[2], int CplSharedCreditConsumed[2]) {
	std::vector<TLP> packets = sequence.packets;
	if (packets.empty()) return;
	int dllpRoundRobinIndex = 0;
	int flitIndex = 0;
	Dllp::CreditType dllpCreditType[] = {Dllp::CreditType::P, Dllp::CreditType::NP, Dllp::CreditType::Cpl};
	TLP packet = packets.front();
	packets.erase(packets.begin());
	std::bitset<236> packetBits(packet.getBitRep().toString());
	int packetIndex = 0;
	bool isPartialTLP = false;
	while (!packets.empty()) {
		Flit flit = new Flit();
		if (!isPartialTLP) {
			packet = packets.front();
			packets.erase(packets.begin());
			packetBits = std::bitset<236>(packet.getBitRep().toString());
			packetIndex = 0;
		}
		Dllp::CreditType creditType = packet.getCreditType();
		if (transaction.checkGateEquation(
			(creditType == Dllp::CreditType::P ? PSharedCreditLimit : ((creditType == Dllp::CreditType::NP) ? NPSharedCreditLimit : CplSharedCreditLimit)),
			(creditType == Dllp::CreditType::P ? PSharedCreditConsumed : ((creditType == Dllp::CreditType::NP) ? NPSharedCreditConsumed : CplSharedCreditConsumed)),
			packet)) {
			if (flitIndex < 118 && flit.firstHalfTLPCount < 8) {
				flit.firstHalfTLPCount++;
				if (flitIndex + packet.getTotalLength() > 118) {
					flit.secondHalfTLPCount++;
					if (flitIndex + packet.getTotalLength() > 236) {
						isPartialTLP = true;
						flit.TLLPPayload |= packetBits << ((236 - flitIndex) * 8);
					}
				}
			}
		}
		else {
			datalink.sendFlit(flit, sendOnQueue, Dllp::DllpType::updateFC, dllpCreditType[dllpRoundRobinIndex / 2], dllpRoundRobinIndex % 2, 
				(dllpCreditType[dllpRoundRobinIndex / 2] == Dllp::CreditType::P ? (dllpRoundRobinIndex % 2 ? globals.P_CREDIT : 0) : 
					((creditType == Dllp::CreditType::NP) ? (dllpRoundRobinIndex % 2 ? globals.NP_CREDIT : 0) : 
						(dllpRoundRobinIndex % 2 ? globals.CPL_CREDIT : 0))));
			dllpRoundRobinIndex = (dllpRoundRobinIndex + 1) % 6;
		}
	}
}
