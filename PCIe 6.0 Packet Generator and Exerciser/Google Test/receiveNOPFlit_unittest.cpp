#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/layers_wrapper.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/globals.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/flit.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/utils/dllp.h"
#define globalsParameters P_SHARED_CREDIT, NP_SHARED_CREDIT, CPL_SHARED_CREDIT, P_DEDICATED_CREDIT, NP_DEDICATED_CREDIT, CPL_DEDICATED_CREDIT

int P_SHARED_CREDIT[2];
int NP_SHARED_CREDIT[2];
int CPL_SHARED_CREDIT[2];
int P_DEDICATED_CREDIT[2];
int NP_DEDICATED_CREDIT[2];
int CPL_DEDICATED_CREDIT[2];
bool Fl1 = false;
bool Fl2 = false;
int P_SHARED_CREDIT_LIMIT[2] = { -1 };
int NP_SHARED_CREDIT_LIMIT[2] = { -1 };
int CPL_SHARED_CREDIT_LIMIT[2] = { -1 };
int P_DEDICATED_CREDIT_LIMIT[2] = { -1 };
int NP_DEDICATED_CREDIT_LIMIT[2] = { -1 };
int CPL_DEDICATED_CREDIT_LIMIT[2] = { -1 };
int P_SHARED_CREDITS_CONSUMED[2] = { 0 };
int NP_SHARED_CREDITS_CONSUMED[2] = { 0 };
int CPL_SHARED_CREDITS_CONSUMED[2] = { 0 };
int P_DEDICATED_CREDITS_CONSUMED[2] = { 0 };
int NP_DEDICATED_CREDITS_CONSUMED[2] = { 0 };
int CPL_DEDICATED_CREDITS_CONSUMED[2] = { 0 };


TEST(receiveNOPFlitsuite, checkingupdatecreditlimit_getting_called) {
	LayersWrapper layerwrapper;
	const int PSharedCredit[2] = { 8, 5 };
	Globals* globals = new Globals(globalsParameters);
	Flit* flit = new Flit();
	Dllp dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp.getBitRep();
	//receiveNOPFlit(Flit* flit, Globals& globals) 
	layerwrapper.receiveNOPFlit(flit, *globals);
	EXPECT_EQ(globals->P_SHARED_CREDIT_LIMIT[0], PSharedCredit[0]);
	EXPECT_EQ(globals->P_SHARED_CREDIT_LIMIT[1], PSharedCredit[1]);
	EXPECT_EQ(globals->NP_SHARED_CREDIT_LIMIT[0], -1);
	EXPECT_EQ(globals->NP_SHARED_CREDIT_LIMIT[1], -1);
	EXPECT_EQ(globals->CPL_SHARED_CREDIT_LIMIT[0], -1);
	EXPECT_EQ(globals->CPL_SHARED_CREDIT_LIMIT[1], -1);
	EXPECT_EQ(globals->P_DEDICATED_CREDIT_LIMIT[0], -1);
	EXPECT_EQ(globals->P_DEDICATED_CREDIT_LIMIT[1], -1);
	EXPECT_EQ(globals->NP_DEDICATED_CREDIT_LIMIT[0], -1);
	EXPECT_EQ(globals->NP_DEDICATED_CREDIT_LIMIT[1], -1);
	EXPECT_EQ(globals->CPL_DEDICATED_CREDIT_LIMIT[0], -1);
	EXPECT_EQ(globals->CPL_DEDICATED_CREDIT_LIMIT[1], -1);
	EXPECT_EQ(globals->Fl1, false);
	EXPECT_EQ(globals->Fl2, false);
}


TEST(receiveNOPFlitsuite, checkingupdatecreditlimit_getting_called_randomvalues) {
	LayersWrapper layerwrapper;
	Globals* globals = new Globals(globalsParameters);
	const int PSharedCredit[2] = { 8, 5 };
	globals->Fl1 = false;
	globals->Fl2 = false;
	globals->P_SHARED_CREDIT_LIMIT[0] = -1;
	globals->P_SHARED_CREDIT_LIMIT[1] = -1;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 1;
	globals->NP_SHARED_CREDIT_LIMIT[1] = 3;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 8;
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 7;
	globals->P_DEDICATED_CREDIT_LIMIT[0] = 5;
	globals->P_DEDICATED_CREDIT_LIMIT[1] = 3;
	globals->NP_DEDICATED_CREDIT_LIMIT[0] = 2;
	globals->NP_DEDICATED_CREDIT_LIMIT[1] = 2;
	globals->CPL_DEDICATED_CREDIT_LIMIT[0] = 0;
	globals->CPL_DEDICATED_CREDIT_LIMIT[1] = 0;
	Flit* flit = new Flit();
	Dllp dllp(1, 1, PSharedCredit[1], PSharedCredit[0], 0, true, Dllp::DllpType::initFC1, Dllp::CreditType::P);
	flit->DLLPPayload = dllp.getBitRep();
	//receiveNOPFlit(Flit* flit, Globals& globals) 
	layerwrapper.receiveNOPFlit(flit, *globals);
	EXPECT_EQ(globals->P_SHARED_CREDIT_LIMIT[0], PSharedCredit[0]);
	EXPECT_EQ(globals->P_SHARED_CREDIT_LIMIT[1], PSharedCredit[1]);
	EXPECT_EQ(globals->NP_SHARED_CREDIT_LIMIT[0], 1);
	EXPECT_EQ(globals->NP_SHARED_CREDIT_LIMIT[1], 3);
	EXPECT_EQ(globals->CPL_SHARED_CREDIT_LIMIT[0], 8);
	EXPECT_EQ(globals->CPL_SHARED_CREDIT_LIMIT[1], 7);
	EXPECT_EQ(globals->P_DEDICATED_CREDIT_LIMIT[0], 5);
	EXPECT_EQ(globals->P_DEDICATED_CREDIT_LIMIT[1], 3);
	EXPECT_EQ(globals->NP_DEDICATED_CREDIT_LIMIT[0], 2);
	EXPECT_EQ(globals->NP_DEDICATED_CREDIT_LIMIT[1], 2);
	EXPECT_EQ(globals->CPL_DEDICATED_CREDIT_LIMIT[0], 0);
	EXPECT_EQ(globals->CPL_DEDICATED_CREDIT_LIMIT[1], 0);
	EXPECT_EQ(globals->Fl1, true);
	EXPECT_EQ(globals->Fl2, false);
}

TEST(receiveNOPFlitsuite, checkingupdatecreditlimit_getting_called_randomvalues2) {
	LayersWrapper layerwrapper;
	Globals* globals = new Globals(globalsParameters);
	const int CplSharedCredit[2] = { 8, 5 };
	globals->Fl1 = false;
	globals->Fl2 = false;
	globals->P_SHARED_CREDIT_LIMIT[0] = 1;
	globals->P_SHARED_CREDIT_LIMIT[1] = 3;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 8;
	globals->NP_SHARED_CREDIT_LIMIT[1] = 7;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = -1;
	globals->CPL_SHARED_CREDIT_LIMIT[1] = -1;
	globals->P_DEDICATED_CREDIT_LIMIT[0] = 5;
	globals->P_DEDICATED_CREDIT_LIMIT[1] = 3;
	globals->NP_DEDICATED_CREDIT_LIMIT[0] = 2;
	globals->NP_DEDICATED_CREDIT_LIMIT[1] = 2;
	globals->CPL_DEDICATED_CREDIT_LIMIT[0] = 0;
	globals->CPL_DEDICATED_CREDIT_LIMIT[1] = 0;
	Flit* flit = new Flit();
	Dllp dllp(1, 1, CplSharedCredit[1], CplSharedCredit[0], 0, true, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl);
	flit->DLLPPayload = dllp.getBitRep();
	//receiveNOPFlit(Flit* flit, Globals& globals) 
	layerwrapper.receiveNOPFlit(flit, *globals);
	EXPECT_EQ(globals->P_SHARED_CREDIT_LIMIT[0], 1);
	EXPECT_EQ(globals->P_SHARED_CREDIT_LIMIT[1], 3);
	EXPECT_EQ(globals->NP_SHARED_CREDIT_LIMIT[0], 8);
	EXPECT_EQ(globals->NP_SHARED_CREDIT_LIMIT[1], 7);
	EXPECT_EQ(globals->CPL_SHARED_CREDIT_LIMIT[0], CplSharedCredit[0]);
	EXPECT_EQ(globals->CPL_SHARED_CREDIT_LIMIT[1], CplSharedCredit[1]);
	EXPECT_EQ(globals->P_DEDICATED_CREDIT_LIMIT[0], 5);
	EXPECT_EQ(globals->P_DEDICATED_CREDIT_LIMIT[1], 3);
	EXPECT_EQ(globals->NP_DEDICATED_CREDIT_LIMIT[0], 2);
	EXPECT_EQ(globals->NP_DEDICATED_CREDIT_LIMIT[1], 2);
	EXPECT_EQ(globals->CPL_DEDICATED_CREDIT_LIMIT[0], 0);
	EXPECT_EQ(globals->CPL_DEDICATED_CREDIT_LIMIT[1], 0);
	EXPECT_EQ(globals->Fl1, true);
	EXPECT_EQ(globals->Fl2, false);
}