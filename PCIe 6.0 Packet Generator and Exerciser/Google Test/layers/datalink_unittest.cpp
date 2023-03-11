#include "../pch.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/layers/datalink.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/layers/flit.h"
#include "../../PCIe 6.0 Packet Generator and Exerciser/utils/dllp.h"

TEST(UpdateCreditLimit, SetPSharedCreditLimitFC1) {
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

TEST(UpdateCreditLimit, SetNPSharedCreditLimitFC1) {
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

TEST(UpdateCreditLimit, SetCplSharedCreditLimitFC1) {
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
	EXPECT_EQ(CplSharedCreditLimit[0], CplSharedCredit[0]);
	EXPECT_EQ(CplSharedCreditLimit[1], CplSharedCredit[1]);
	EXPECT_EQ(PDedicatedCreditLimit[0], -1);
	EXPECT_EQ(PDedicatedCreditLimit[1], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetPDedicatedCreditLimitFC1) {
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

TEST(UpdateCreditLimit, SetNPDedicatedCreditLimitFC1) {
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

TEST(UpdateCreditLimit, SetCplDedicatedCreditLimitFC1) {
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

TEST(UpdateCreditLimit, SetPSharedCreditLimitFC2) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::P);
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

TEST(UpdateCreditLimit, SetNPSharedCreditLimitFC2) {
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
	Dllp* dllp = new Dllp(1, 1, NPSharedCredit[1], NPSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::NP);
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

TEST(UpdateCreditLimit, SetCplSharedCreditLimitFC2) {
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
	Dllp* dllp = new Dllp(1, 1, CplSharedCredit[1], CplSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], -1);
	EXPECT_EQ(PSharedCreditLimit[1], -1);
	EXPECT_EQ(NPSharedCreditLimit[0], -1);
	EXPECT_EQ(NPSharedCreditLimit[1], -1);
	EXPECT_EQ(CplSharedCreditLimit[0], CplSharedCredit[0]);
	EXPECT_EQ(CplSharedCreditLimit[1], CplSharedCredit[1]);
	EXPECT_EQ(PDedicatedCreditLimit[0], -1);
	EXPECT_EQ(PDedicatedCreditLimit[1], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetPDedicatedCreditLimitFC2) {
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
	Dllp* dllp = new Dllp(1, 1, PDedicatedCredit[1], PDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::P);
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

TEST(UpdateCreditLimit, SetNPDedicatedCreditLimitFC2) {
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
	Dllp* dllp = new Dllp(1, 1, NPDedicatedCredit[1], NPDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::NP);
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

TEST(UpdateCreditLimit, SetCplDedicatedCreditLimitFC2) {
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
	Dllp* dllp = new Dllp(1, 1, CplDedicatedCredit[1], CplDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl);
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

TEST(UpdateCreditLimit, SetFI1OnPSharedFC1) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = {1, 3};
	int CplSharedCreditLimit[2] = {8, 7};
	int PDedicatedCreditLimit[2] = {5, 3};
	int NPDedicatedCreditLimit[2] = {2, 2};
	int CplDedicatedCreditLimit[2] = {0, 0};
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], PSharedCredit[0]);
	EXPECT_EQ(PSharedCreditLimit[1], PSharedCredit[1]);
	EXPECT_EQ(NPSharedCreditLimit[0], 1);
	EXPECT_EQ(NPSharedCreditLimit[1], 3);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnNPSharedFC1) {
	const DatalinkLayer datalink;
	const int NPSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = {1, 3};
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, NPSharedCredit[1], NPSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::NP);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], NPSharedCredit[0]);
	EXPECT_EQ(NPSharedCreditLimit[1], NPSharedCredit[1]);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnCplSharedFC1) {
	const DatalinkLayer datalink;
	const int CplSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = {8, 7};
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplSharedCredit[1], CplSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 8);
	EXPECT_EQ(NPSharedCreditLimit[1], 7);
	EXPECT_EQ(CplSharedCreditLimit[0], CplSharedCredit[0]);
	EXPECT_EQ(CplSharedCreditLimit[1], CplSharedCredit[1]);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnPDedicatedFC1) {
	const DatalinkLayer datalink;
	const int PDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 5, 3 };
	int NPSharedCreditLimit[2] = { 1, 3 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PDedicatedCredit[1], PDedicatedCredit[0], 0, false, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 5);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 1);
	EXPECT_EQ(NPSharedCreditLimit[1], 3);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], PDedicatedCredit[0]);
	EXPECT_EQ(PDedicatedCreditLimit[1], PDedicatedCredit[1]);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnNPDedicatedFC1) {
	const DatalinkLayer datalink;
	const int NPDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = {2, 2};
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, NPDedicatedCredit[1], NPDedicatedCredit[0], 0, false, Dllp::DllpType::initFC1, Dllp::CreditType::NP);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 2);
	EXPECT_EQ(NPSharedCreditLimit[1], 2);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], NPDedicatedCredit[0]);
	EXPECT_EQ(NPDedicatedCreditLimit[1], NPDedicatedCredit[1]);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnCplDedicatedFC1) {
	const DatalinkLayer datalink;
	const int CplDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 8, 7 };
	int CplSharedCreditLimit[2] = { 0, 0 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplDedicatedCredit[1], CplDedicatedCredit[0], 0, false, Dllp::DllpType::initFC1, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 8);
	EXPECT_EQ(NPSharedCreditLimit[1], 7);
	EXPECT_EQ(CplSharedCreditLimit[0], 0);
	EXPECT_EQ(CplSharedCreditLimit[1], );
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], CplDedicatedCredit[0]);
	EXPECT_EQ(CplDedicatedCreditLimit[1], CplDedicatedCredit[1]);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnPSharedFC2) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { 1, 3 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], PSharedCredit[0]);
	EXPECT_EQ(PSharedCreditLimit[1], PSharedCredit[1]);
	EXPECT_EQ(NPSharedCreditLimit[0], 1);
	EXPECT_EQ(NPSharedCreditLimit[1], 3);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnNPSharedFC2) {
	const DatalinkLayer datalink;
	const int NPSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { -1 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, NPSharedCredit[1], NPSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::NP);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], NPSharedCredit[0]);
	EXPECT_EQ(NPSharedCreditLimit[1], NPSharedCredit[1]);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnCplSharedFC2) {
	const DatalinkLayer datalink;
	const int CplSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 8, 7 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplSharedCredit[1], CplSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 8);
	EXPECT_EQ(NPSharedCreditLimit[1], 7);
	EXPECT_EQ(CplSharedCreditLimit[0], CplSharedCredit[0]);
	EXPECT_EQ(CplSharedCreditLimit[1], CplSharedCredit[1]);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnPDedicatedFC2) {
	const DatalinkLayer datalink;
	const int PDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 5, 3 };
	int NPSharedCreditLimit[2] = { 1, 3 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PDedicatedCredit[1], PDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 5);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 1);
	EXPECT_EQ(NPSharedCreditLimit[1], 3);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], PDedicatedCredit[0]);
	EXPECT_EQ(PDedicatedCreditLimit[1], PDedicatedCredit[1]);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnNPDedicatedFC2) {
	const DatalinkLayer datalink;
	const int NPDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 2, 2 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, NPDedicatedCredit[1], NPDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::NP);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 2);
	EXPECT_EQ(NPSharedCreditLimit[1], 2);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], NPDedicatedCredit[0]);
	EXPECT_EQ(NPDedicatedCreditLimit[1], NPDedicatedCredit[1]);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI1OnCplDedicatedFC2) {
	const DatalinkLayer datalink;
	const int CplDedicatedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 8, 7 };
	int CplSharedCreditLimit[2] = { 0, 0 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplDedicatedCredit[1], CplDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 8);
	EXPECT_EQ(NPSharedCreditLimit[1], 7);
	EXPECT_EQ(CplSharedCreditLimit[0], 0);
	EXPECT_EQ(CplSharedCreditLimit[1], 0);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], CplDedicatedCredit[0]);
	EXPECT_EQ(CplDedicatedCreditLimit[1], CplDedicatedCredit[1]);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, SetFI2OnPShared) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = { 8, 5 };
	bool FI1 = true;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 8, 5 };
	int NPSharedCreditLimit[2] = { 1, 3 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 8);
	EXPECT_EQ(PSharedCreditLimit[1], 5);
	EXPECT_EQ(NPSharedCreditLimit[0], 1);
	EXPECT_EQ(NPSharedCreditLimit[1], 3);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, true);
}

TEST(UpdateCreditLimit, SetFI2OnNPShared) {
	const DatalinkLayer datalink;
	const int NPSharedCredit[2] = { 8, 5 };
	bool FI1 = true;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 8, 5 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, NPSharedCredit[1], NPSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::NP);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 8);
	EXPECT_EQ(NPSharedCreditLimit[1], 5);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, true);
}

TEST(UpdateCreditLimit, SetFI2OnCplShared) {
	const DatalinkLayer datalink;
	const int CplSharedCredit[2] = { 8, 5 };
	bool FI1 = true;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 8, 7 };
	int CplSharedCreditLimit[2] = { 8, 5 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplSharedCredit[1], CplSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 8);
	EXPECT_EQ(NPSharedCreditLimit[1], 7);
	EXPECT_EQ(CplSharedCreditLimit[0], CplSharedCredit[0]);
	EXPECT_EQ(CplSharedCreditLimit[1], CplSharedCredit[1]);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, true);
}

TEST(UpdateCreditLimit, SetFI2OnPDedicated) {
	const DatalinkLayer datalink;
	const int PDedicatedCredit[2] = { 8, 5 };
	bool FI1 = true;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 5, 3 };
	int NPSharedCreditLimit[2] = { 1, 3 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 8, 5 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PDedicatedCredit[1], PDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 5);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 1);
	EXPECT_EQ(NPSharedCreditLimit[1], 3);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 8);
	EXPECT_EQ(PDedicatedCreditLimit[1], 5);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, true);
}

TEST(UpdateCreditLimit, SetFI2OnNPDedicated) {
	const DatalinkLayer datalink;
	const int NPDedicatedCredit[2] = { 8, 5 };
	bool FI1 = true;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 2, 2 };
	int CplSharedCreditLimit[2] = { 8, 7 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 8, 5 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, NPDedicatedCredit[1], NPDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::NP);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 2);
	EXPECT_EQ(NPSharedCreditLimit[1], 2);
	EXPECT_EQ(CplSharedCreditLimit[0], 8);
	EXPECT_EQ(CplSharedCreditLimit[1], 7);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 8);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 5);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, true);
}

TEST(UpdateCreditLimit, SetFI2OnCplDedicated) {
	const DatalinkLayer datalink;
	const int CplDedicatedCredit[2] = { 8, 5 };
	bool FI1 = true;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 8, 7 };
	int CplSharedCreditLimit[2] = { 0, 0 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 8, 5 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplDedicatedCredit[1], CplDedicatedCredit[0], 0, false, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 8);
	EXPECT_EQ(NPSharedCreditLimit[1], 7);
	EXPECT_EQ(CplSharedCreditLimit[0], 0);
	EXPECT_EQ(CplSharedCreditLimit[1], 0);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 8);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 5);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, true);
}

TEST(UpdateCreditLimit, NotSetFI1On2) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { 0 };
	int CplSharedCreditLimit[2] = { -1 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], PSharedCredit[0]);
	EXPECT_EQ(PSharedCreditLimit[1], PSharedCredit[1]);
	EXPECT_EQ(NPSharedCreditLimit[0], 0);
	EXPECT_EQ(NPSharedCreditLimit[1], 0);
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

TEST(UpdateCreditLimit, NotSetFI1On3) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { 0 };
	int CplSharedCreditLimit[2] = { 0 };
	int PDedicatedCreditLimit[2] = { -1 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], PSharedCredit[0]);
	EXPECT_EQ(PSharedCreditLimit[1], PSharedCredit[1]);
	EXPECT_EQ(NPSharedCreditLimit[0], 0);
	EXPECT_EQ(NPSharedCreditLimit[1], 0);
	EXPECT_EQ(CplSharedCreditLimit[0], 0);
	EXPECT_EQ(CplSharedCreditLimit[1], 0);
	EXPECT_EQ(PDedicatedCreditLimit[0], -1);
	EXPECT_EQ(PDedicatedCreditLimit[1], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, NotSetFI1On4) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { 0 };
	int CplSharedCreditLimit[2] = { 0 };
	int PDedicatedCreditLimit[2] = { 0 };
	int NPDedicatedCreditLimit[2] = { -1 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], PSharedCredit[0]);
	EXPECT_EQ(PSharedCreditLimit[1], PSharedCredit[1]);
	EXPECT_EQ(NPSharedCreditLimit[0], 0);
	EXPECT_EQ(NPSharedCreditLimit[1], 0);
	EXPECT_EQ(CplSharedCreditLimit[0], 0);
	EXPECT_EQ(CplSharedCreditLimit[1], 0);
	EXPECT_EQ(PDedicatedCreditLimit[0], 0);
	EXPECT_EQ(PDedicatedCreditLimit[1], 0);
	EXPECT_EQ(NPDedicatedCreditLimit[0], -1);
	EXPECT_EQ(NPDedicatedCreditLimit[1], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, NotSetFI1On5) {
	const DatalinkLayer datalink;
	const int PSharedCredit[2] = { 8, 5 };
	bool FI1 = false;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { -1 };
	int NPSharedCreditLimit[2] = { 0 };
	int CplSharedCreditLimit[2] = { 0 };
	int PDedicatedCreditLimit[2] = { 0 };
	int NPDedicatedCreditLimit[2] = { 0 };
	int CplDedicatedCreditLimit[2] = { -1 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], PSharedCredit[0]);
	EXPECT_EQ(PSharedCreditLimit[1], PSharedCredit[1]);
	EXPECT_EQ(NPSharedCreditLimit[0], 0);
	EXPECT_EQ(NPSharedCreditLimit[1], 0);
	EXPECT_EQ(CplSharedCreditLimit[0], 0);
	EXPECT_EQ(CplSharedCreditLimit[1], 0);
	EXPECT_EQ(PDedicatedCreditLimit[0], 0);
	EXPECT_EQ(PDedicatedCreditLimit[1], 0);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 0);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[0], -1);
	EXPECT_EQ(CplDedicatedCreditLimit[1], -1);
	EXPECT_EQ(FI1, false);
	EXPECT_EQ(FI2, false);
}

TEST(UpdateCreditLimit, NotSetFI2OnFC1) {
	const DatalinkLayer datalink;
	const int CplSharedCredit[2] = { 8, 5 };
	bool FI1 = true;
	bool FI2 = false;
	int PSharedCreditLimit[2] = { 1, 3 };
	int NPSharedCreditLimit[2] = { 8, 7 };
	int CplSharedCreditLimit[2] = { 8, 5 };
	int PDedicatedCreditLimit[2] = { 5, 3 };
	int NPDedicatedCreditLimit[2] = { 2, 2 };
	int CplDedicatedCreditLimit[2] = { 0, 0 };
	Flit* flit = new Flit();
	Dllp* dllp = new Dllp(1, 1, CplSharedCredit[1], CplSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp->getBitRep();
	datalink.updateCreditLimit(flit, PSharedCreditLimit, NPSharedCreditLimit, CplSharedCreditLimit, PDedicatedCreditLimit, NPDedicatedCreditLimit, CplDedicatedCreditLimit, FI1, FI2);
	EXPECT_EQ(PSharedCreditLimit[0], 1);
	EXPECT_EQ(PSharedCreditLimit[1], 3);
	EXPECT_EQ(NPSharedCreditLimit[0], 8);
	EXPECT_EQ(NPSharedCreditLimit[1], 7);
	EXPECT_EQ(CplSharedCreditLimit[0], CplSharedCredit[0]);
	EXPECT_EQ(CplSharedCreditLimit[1], CplSharedCredit[1]);
	EXPECT_EQ(PDedicatedCreditLimit[0], 5);
	EXPECT_EQ(PDedicatedCreditLimit[1], 3);
	EXPECT_EQ(NPDedicatedCreditLimit[0], 2);
	EXPECT_EQ(NPDedicatedCreditLimit[1], 2);
	EXPECT_EQ(CplDedicatedCreditLimit[0], 0);
	EXPECT_EQ(CplDedicatedCreditLimit[1], 0);
	EXPECT_EQ(FI1, true);
	EXPECT_EQ(FI2, false);
}
