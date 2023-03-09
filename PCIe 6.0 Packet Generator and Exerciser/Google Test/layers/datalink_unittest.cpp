#include "../pch.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/layers/datalink.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/layers/flit.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/utils/dllp.h"

TEST(UpdateCreditLimit, SetPCreditLimit) {
	const DatalinkLayer *datalink;
	const int PSharedCredit[2] = {8, 5};
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp *dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::updateFC, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, &FI1, &FI2);
	EXPECT_EQ(PSharedCreditLimit[0], PSharedCredit[0]);
	EXPECT_EQ(PSharedCreditLimit[1], PSharedCredit[1]);
	EXPECT_EQ(NPSharedCreditLimit[0], -1);
	EXPECT_EQ(NPSharedCreditLimit[1], -1);
	EXPECT_EQ(CplSharedCreditLimit[0], -1);
	EXPECT_EQ(CplSharedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
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
