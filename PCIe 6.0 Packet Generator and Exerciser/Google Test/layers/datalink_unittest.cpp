#include "../pch.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/layers/datalink.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/utils/flit.h"

TEST(UpdateCreditLimit, SetPCreditLimit) {
	const DatalinkLayer datalink;
	bool Fl1 = false;
	bool Fl2 = false;
	int PSharedCreditLimit[2];
	int NPSharedCreditLimit[2];
	int CplSharedCreditLimit[2];
	datalink.updateCreditLimit(new Flit(null, null, null, 
		new Dllp(1, true, 0, 3, 1, 5, initFC1, P), null, null);
}