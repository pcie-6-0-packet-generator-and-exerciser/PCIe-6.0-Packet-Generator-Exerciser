#include"pch.h"
#include"../PCIe 6.0 Packet Generator and Exerciser/layers/layers_wrapper.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/flit.h"

#define globalsParameters P_SHARED_CREDIT, NP_SHARED_CREDIT, CPL_SHARED_CREDIT, P_DEDICATED_CREDIT, NP_DEDICATED_CREDIT, CPL_DEDICATED_CREDIT
int P_SHARED_CREDIT[2] = {0 , 0}; //HEADER DATA
int NP_SHARED_CREDIT[2] = { 0 , 0 };
int CPL_SHARED_CREDIT[2] = { 0 , 0 };
int P_DEDICATED_CREDIT[2] = { 0 , 0 };
int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
bool Fl1 = false;
bool Fl2 = false;
int P_SHARED_CREDIT_LIMIT[2] = { -1,-1 };
int NP_SHARED_CREDIT_LIMIT[2] = { -1 ,-1 };
int CPL_SHARED_CREDIT_LIMIT[2] = { -1 ,-1 };
int P_DEDICATED_CREDIT_LIMIT[2] = { -1 ,-1 };
int NP_DEDICATED_CREDIT_LIMIT[2] = { -1 ,-1 };
int CPL_DEDICATED_CREDIT_LIMIT[2] = { -1 ,-1 };
int P_SHARED_CREDITS_CONSUMED[2] = { 0 ,0 };
int NP_SHARED_CREDITS_CONSUMED[2] = { 0 ,0 };
int CPL_SHARED_CREDITS_CONSUMED[2] = { 0 ,0 };
int P_DEDICATED_CREDITS_CONSUMED[2] = { 0 ,0 };
int NP_DEDICATED_CREDITS_CONSUMED[2] = { 0 ,0 };
int CPL_DEDICATED_CREDITS_CONSUMED[2] = { 0 ,0 };


TEST(sendNOPFlitsuite, test_six_values) {
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	bool flagSharedP = false, flagDedicatedP = false, flagSharedNP = false, flagDedicatedNP = false, flagSharedCPL = false, flagDedicatedCPL = false;
	for (int i = 0; i < 6; i++) {
		Flit* flit = outputqueue.front();
		outputqueue.pop();
		Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
		dllp.m_creditType;
		if (dllp.m_creditType == Dllp::CreditType::P) {
			if (dllp.shared) {
				flagSharedP = true;
			}
			else
				flagDedicatedP = true;
		}
		else if (dllp.m_creditType == Dllp::CreditType::NP) {
			if (dllp.shared) {
				flagSharedNP = true;
			}
			else
				flagDedicatedNP = true;
		}
		else
		{
			if (dllp.shared) {
				flagSharedCPL = true;
			}
			else
				flagDedicatedCPL = true;
		}
	}
	EXPECT_TRUE(flagSharedP && flagSharedNP && flagSharedCPL && flagDedicatedP && flagDedicatedNP && flagDedicatedCPL);

}

TEST(sendNOPFlitsuite, test_six_values_HDR_DataFC) {
	int P_SHARED_CREDIT[2] = { 1,2 }; //HEADER DATA
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	bool flagSharedP = false, flagDedicatedP = false, flagSharedNP = false, flagDedicatedNP = false, flagSharedCPL = false, flagDedicatedCPL = false;
	for (int i = 0; i < 6; i++) {
		Flit* flit = outputqueue.front();
		outputqueue.pop();
		Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
		if (dllp.m_creditType == Dllp::CreditType::P) {
			if (dllp.shared) {
				flagSharedP = true;
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
			}
			else
				flagDedicatedP = true;
		}
		else if (dllp.m_creditType == Dllp::CreditType::NP) {
			if (dllp.shared) {
				flagSharedNP = true;
			}
			else
				flagDedicatedNP = true;
		}
		else
		{
			if (dllp.shared) {
				flagSharedCPL = true;
			}
			else
				flagDedicatedCPL = true;
		}
	}
	EXPECT_TRUE(flagSharedP && flagSharedNP && flagSharedCPL && flagDedicatedP && flagDedicatedNP && flagDedicatedCPL);

}

TEST(sendNOPFlitsuite, test_one_value) {
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 1);
}

TEST(sendNOPFlitsuite, test_two_value) {
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 2);
}

TEST(sendNOPFlitsuite, test_three_value) {
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 3);
}

TEST(sendNOPFlitsuite, test_four_value) {
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 4);
}

TEST(sendNOPFlitsuite, test_five_value) {
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 5);
}


