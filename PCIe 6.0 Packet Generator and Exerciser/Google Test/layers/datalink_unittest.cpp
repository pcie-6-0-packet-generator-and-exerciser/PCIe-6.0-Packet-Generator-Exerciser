#include "../pch.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/layers/datalink.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/layers/flit.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/utils/dllp.h"

TEST(UpdateCreditLimit, SetPSharedCreditLimit) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = {8, 5};
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp *dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], PSharedCredit[0]);
	EXPECT_EQ(PSharedCreditLimit[1], PSharedCredit[1]);
	EXPECT_EQ(NPSharedCreditLimit[0], -1);
	EXPECT_EQ(NPSharedCreditLimit[1], -1);
	EXPECT_EQ(CplSharedCreditLimit[0], -1);
	EXPECT_EQ(CplSharedCreditLimit[1], -1);
	EXPECT_EQ(PDedicatedCreditLimit[0], -1);
	EXPECT_EQ(PDedicatedCreditLimit[1], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetNPSharedCreditLimit) {
	const DatalinkLayer datalink;
	const int NPSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, NPSharedCredit[1], NPSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::NP);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], -1);
	EXPECT_EQ(PSharedCreditLimit[1], -1);
	EXPECT_EQ(NPSharedCreditLimit[0], NPSharedCredit[0]);
	EXPECT_EQ(NPSharedCreditLimit[1], NPSharedCredit[1]);
	EXPECT_EQ(CplSharedCreditLimit[0], -1);
	EXPECT_EQ(CplSharedCreditLimit[1], -1);
	EXPECT_EQ(PDedicatedCreditLimit[0], -1);
	EXPECT_EQ(PDedicatedCreditLimit[1], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetCplSharedCreditLimit) {
	const DatalinkLayer datalink;
	const int CplSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplSharedCredit[1], CplSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], -1);
	EXPECT_EQ(PSharedCreditLimit[1], -1);
	EXPECT_EQ(NPSharedCreditLimit[0], -1);
	EXPECT_EQ(NPSharedCreditLimit[1], -1);
	EXPECT_EQ(CplSharedCreditLimit[0], CplSharedCreditLimit[0]);
	EXPECT_EQ(CplSharedCreditLimit[1], CplSharedCreditLimit[1]);
	EXPECT_EQ(PDedicatedCreditLimit[0], -1);
	EXPECT_EQ(PDedicatedCreditLimit[1], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetPDedicatedCreditLimit) {
	const DatalinkLayer datalink;
	const int PDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PDedicatedCredit[1], PDedicatedCredit[0], 0, false, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], -1);
	EXPECT_EQ(PSharedCreditLimit[1], -1);
	EXPECT_EQ(NPSharedCreditLimit[0], -1);
	EXPECT_EQ(NPSharedCreditLimit[1], -1);
	EXPECT_EQ(CplSharedCreditLimit[0], -1);
	EXPECT_EQ(CplSharedCreditLimit[1], -1);
	EXPECT_EQ(PDedicatedCreditLimit[0], PDedicatedCredit[0]);
	EXPECT_EQ(PDedicatedCreditLimit[1], PDedicatedCredit[1]);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetNPDedicatedCreditLimit) {
	const DatalinkLayer datalink;
	const int NPDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, NPDedicatedCredit[1], NPDedicatedCredit[0], 0, false, Dllp::DllpType::initFC1, Dllp::CreditType::NP);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], -1);
	EXPECT_EQ(PSharedCreditLimit[1], -1);
	EXPECT_EQ(NPSharedCreditLimit[0], -1);
	EXPECT_EQ(NPSharedCreditLimit[1], -1);
	EXPECT_EQ(CplSharedCreditLimit[0], -1);
	EXPECT_EQ(CplSharedCreditLimit[1], -1);
	EXPECT_EQ(PDedicatedCreditLimit[0], -1);
	EXPECT_EQ(PDedicatedCreditLimit[1], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[0], NPDedicatedCredit[0]);
	EXPECT_EQ(NPDedicatedCreditLimit[1], NPDedicatedCredit[1]);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetCplDedicatedCreditLimit) {
	const DatalinkLayer datalink;
	const int CplDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplDedicatedCredit[1], CplDedicatedCredit[0], 0, false, Dllp::DllpType::initFC1, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], -1);
	EXPECT_EQ(PSharedCreditLimit[1], -1);
	EXPECT_EQ(NPSharedCreditLimit[0], -1);
	EXPECT_EQ(NPSharedCreditLimit[1], -1);
	EXPECT_EQ(CplSharedCreditLimit[0], -1);
	EXPECT_EQ(CplSharedCreditLimit[1], -1);
	EXPECT_EQ(PDedicatedCreditLimit[0], -1);
	EXPECT_EQ(PDedicatedCreditLimit[1], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], CplDedicatedCredit[0]);
	EXPECT_EQ(CplDedicatedCreditLimit[1], CplDedicatedCredit[1]);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFl1) {

}

TEST(UpdateCreditLimit, SetFl2) {

}
