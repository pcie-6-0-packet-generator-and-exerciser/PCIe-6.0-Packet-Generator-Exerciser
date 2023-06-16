#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/datalink.h"
TEST(prepareFlitSuite, testinginputs) {
//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink=new DatalinkLayer();
	bool shared = true;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::initFC1, Dllp::CreditType::P, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type , Dllp::DllpType::initFC1);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::P);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}
TEST(prepareFlitSuite, testinginputs2) {
	//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink = new DatalinkLayer();
	bool shared = true;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::initFC1, Dllp::CreditType::NP, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::NP);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}
TEST(prepareFlitSuite, testinginputs3) {
	//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink = new DatalinkLayer();
	bool shared = true;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::initFC1, Dllp::CreditType::Cpl, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type, Dllp::DllpType::initFC1);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::Cpl);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}
TEST(prepareFlitSuite, testinginputs4) {
	//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink = new DatalinkLayer();
	bool shared = true;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::initFC2, Dllp::CreditType::P, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type, Dllp::DllpType::initFC2);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::P);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}
TEST(prepareFlitSuite, testinginputs5) {
	//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink = new DatalinkLayer();
	bool shared = true;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::initFC2, Dllp::CreditType::NP, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type, Dllp::DllpType::initFC2);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::NP);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}
TEST(prepareFlitSuite, testinginputs6) {
	//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink = new DatalinkLayer();
	bool shared = true;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::initFC2, Dllp::CreditType::Cpl, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type, Dllp::DllpType::initFC2);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::Cpl);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}
TEST(prepareFlitSuite, testinginputs7) {
	//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink = new DatalinkLayer();
	bool shared = false;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::initFC2, Dllp::CreditType::P, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type, Dllp::DllpType::initFC2);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::P);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}
TEST(prepareFlitSuite, testinginputs8) {
	//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink = new DatalinkLayer();
	bool shared = true;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::updateFC, Dllp::CreditType::P, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type, Dllp::DllpType::updateFC);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::P);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}
TEST(prepareFlitSuite, testinginputs9) {
	//	Flit* prepareFlit(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	Flit* flit = new Flit();
	int credit[2] = { 5,8 }; //HEADER DATA
	DatalinkLayer* datalink = new DatalinkLayer();
	bool shared = true;
	bool correct = false;
	datalink->prepareFlit(flit, Dllp::DllpType::updateFC, Dllp::CreditType::NP, shared, credit);
	Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
	EXPECT_EQ(dllp.m_type, Dllp::DllpType::updateFC);
	EXPECT_EQ(dllp.m_creditType, Dllp::CreditType::NP);
	EXPECT_EQ(dllp.shared, shared);
	EXPECT_EQ(dllp.DataFc, credit[1]);
	EXPECT_EQ(dllp.HdrFC, credit[0]);
}