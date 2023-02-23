#include "../pch.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/layers/datalink.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/utils/flit.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/utils/dllp.h"

TEST(UpdateCreditLimit, SetPCreditLimit) {
	const DatalinkLayer datalink;
	bool Fl1 = false;
	bool Fl2 = false;
	int PSharedCreditLimit[2];
	int NPSharedCreditLimit[2];
	int CplSharedCreditLimit[2];
	datalink.updateCreditLimit(new Flit(null, null, null, 
		new Dllp(1, true, 0, 3, 1, 5, Dllp::DllpType::initFC1, Dllp::CreditType::P), null, null));
}

TEST(UpdateCreditLimit, SetNPCreditLimit) {

	// Check NP limit is set to the correct value

	// Check Fl1 and Fl2 are not set

}

TEST(UpdateCreditLimit, SetCplCreditLimit) {

	// Check Cpl limit is set to the correct value

	// Check Fl1 and Fl2 are not set

}

TEST(UpdateCreditLimit, SetFl1) {

}

TEST(UpdateCreditLimit, SetFl2) {

}
