#include "layers_wrapper.h"
#include "../utils/dllp.h"

void LayersWrapper::sendPayloadFlit(Globals globals, Sequence sequence, QueueWrapper<Flit> sendOnQueue, int PSharedCreditLimit[2], int NPSharedCreditLimit[2], int CplSharedCreditLimit[2], int PSharedCreditConsumed[2], int NPSharedCreditConsumed[2], int CplSharedCreditConsumed[2]) {
	int dllpRoundRobinIndex = 0;
	Dllp::CreditType dllpCreditType[] = {Dllp::CreditType::P, Dllp::CreditType::NP, Dllp::CreditType::Cpl};
	std::vector<TLP> packets = sequence.packets;
	Flit flit = new Flit();
	while (!packets.empty()) {
		TLP packet = packets.front();
		packets.erase(packets.begin());
		Dllp::CreditType creditType = packet.getCreditType();
		if (transaction.checkGateEquation(
			(creditType == Dllp::CreditType::P ? PSharedCreditLimit : ((creditType == Dllp::CreditType::NP) ? NPSharedCreditLimit : CplSharedCreditLimit)),
			(creditType == Dllp::CreditType::P ? PSharedCreditConsumed : ((creditType == Dllp::CreditType::NP) ? NPSharedCreditConsumed : CplSharedCreditConsumed)),
			packet)) {

		}
		else {
			datalink.sendFlit(flit, sendOnQueue, Dllp::DllpType::updateFC, dllpCreditType[dllpRoundRobinIndex / 2], dllpRoundRobinIndex % 2, 
				(dllpCreditType[dllpRoundRobinIndex / 2] == Dllp::CreditType::P ? (dllpRoundRobinIndex % 2 ? globals.P_CREDIT : 0) : 
					((creditType == Dllp::CreditType::NP) ? (dllpRoundRobinIndex % 2 ? globals.NP_CREDIT : 0) : 
						(dllpRoundRobinIndex % 2 ? globals.CPL_CREDIT : 0))));
		}
	}
}
