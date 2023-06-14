#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/transaction_layer.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/globals.h"
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

//CPL
// 
//bool  TransactionLayer::checkGateEquation(const Globals globals, const TLP* tlp)
TEST(checkEquationsuite, CPL_passed_values) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0;
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0;
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0;
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0;
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_due_dataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 5000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_due_dataConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 5000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_due_dataConsumptionAnddataSharedCredit) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 3000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 2000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_due_dataConsumptionAnddataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 2000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 3000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_passed_values_due_dataConsumptionAnddataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 2000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 2000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_passed_values_due_dataConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 4000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_passed_values_due_dataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 4000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_2049) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 2100; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 30; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 21;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, CPL_passed_values_2047) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 2100; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 33; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 20;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}
//********************************

TEST(checkEquationsuite, CPL_fail_values_due_headerSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 100; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_due_headerConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 100;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_due_headerConsumptionAnddheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 50; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 50;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_due_headerConsumptionAndheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 50; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 50;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_passed_values_due_headerConsumptionAnddheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 2000; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 2000;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_passed_values_due_dheaderConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 4000;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_passed_values_due_headerSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 4000; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_2049_header) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 300; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 30; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 21;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, CPL_passed_values_127_header) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 200; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 33; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 40;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_INT_MAX) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = INT_MAX; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, CPL_fail_values_INT_MAX_data) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = INT_MAX; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, CPL_fail_values_INT_MAX_dataandheader) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::Cpl;
	globals->CPL_SHARED_CREDIT_LIMIT[0] = INT_MAX; //headerSharedCreditLimit
	globals->CPL_SHARED_CREDIT_LIMIT[1] = INT_MAX; //dataSharedCreditLimit
	globals->CPL_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->CPL_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

//P
TEST(checkEquationsuite, P_passed_values) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0;
	globals->P_SHARED_CREDIT_LIMIT[1] = 0;
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0;
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0;
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}
//*****************
TEST(checkEquationsuite, P_fail_values_due_dataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 5000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_due_dataConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 5000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_due_dataConsumptionAnddataSharedCredit) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 3000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 2000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_due_dataConsumptionAnddataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 2000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 3000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_passed_values_due_dataConsumptionAnddataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 2000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 2000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_passed_values_due_dataConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 4000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_passed_values_due_dataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 4000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_2049) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 2100; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 30; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 21;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, P_passed_values_2047) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 2100; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 33; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 20;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}
//********************************

TEST(checkEquationsuite, P_fail_values_due_headerSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 100; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_due_headerConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 100;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_due_headerConsumptionAnddheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 50; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 50;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_due_headerConsumptionAndheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 50; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 50;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_passed_values_due_headerConsumptionAnddheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 2000; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 2000;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_passed_values_due_dheaderConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 4000;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_passed_values_due_headerSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 4000; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_2049_header) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 300; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 30; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 21;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, P_passed_values_127_header) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 200; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 33; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 40;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_INT_MAX) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = INT_MAX; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, P_fail_values_INT_MAX_data) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = INT_MAX; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, P_fail_values_INT_MAX_dataandheader) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::P;
	globals->P_SHARED_CREDIT_LIMIT[0] = INT_MAX; //headerSharedCreditLimit
	globals->P_SHARED_CREDIT_LIMIT[1] = INT_MAX; //dataSharedCreditLimit
	globals->P_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->P_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

//NP
TEST(checkEquationsuite, NP_passed_values) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0;
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0;
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0;
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0;
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_due_dataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 5000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_due_dataConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 5000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_due_dataConsumptionAnddataSharedCredit) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 3000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 2000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_due_dataConsumptionAnddataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 3000; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 2000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 3000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_passed_values_due_dataConsumptionAnddataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 2000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 2000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_passed_values_due_dataConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 4000;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_passed_values_due_dataSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 1000; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 4000; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_2049) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 2100; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 30; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 21;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, NP_passed_values_2047) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 2100; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 33; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 20;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}
//********************************

TEST(checkEquationsuite, NP_fail_values_due_headerSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 100; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_due_headerConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 100;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_due_headerConsumptionAnddheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 50; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 50;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_due_headerConsumptionAndheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 600; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 50; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 50;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_passed_values_due_headerConsumptionAnddheaderSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 2000; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 2000;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_passed_values_due_dheaderConsumption) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 4000;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_passed_values_due_headerSharedCreditConsumed) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 1000; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 4000; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_2049_header) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 300; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 30; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 21;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, NP_passed_values_127_header) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 200; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 33; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 40;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE((transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_INT_MAX) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = INT_MAX; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = 0; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}

TEST(checkEquationsuite, NP_fail_values_INT_MAX_data) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = 0; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = INT_MAX; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}
TEST(checkEquationsuite, NP_fail_values_INT_MAX_dataandheader) {
	//Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
	Globals* globals = new Globals(globalsParameters);
	TLP* tlp = new TLP();
	tlp->creditConsumedType = Dllp::CreditType::NP;
	globals->NP_SHARED_CREDIT_LIMIT[0] = INT_MAX; //headerSharedCreditLimit
	globals->NP_SHARED_CREDIT_LIMIT[1] = INT_MAX; //dataSharedCreditLimit
	globals->NP_SHARED_CREDITS_CONSUMED[0] = 0; //headerSharedCreditConsumed
	globals->NP_SHARED_CREDITS_CONSUMED[1] = 0; //dataSharedCreditConsumed
	tlp->headerConsumption = 0;
	tlp->dataConsumption = 0;
	TransactionLayer* transcationLayer = new TransactionLayer();
	EXPECT_TRUE(!(transcationLayer->checkGateEquation(*globals, tlp)));
}