#include"pch.h"
#include"../PCIe 6.0 Packet Generator and Exerciser/layers/layers_wrapper.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/flit.h"

#define globalsParameters P_SHARED_CREDIT, NP_SHARED_CREDIT, CPL_SHARED_CREDIT, P_DEDICATED_CREDIT, NP_DEDICATED_CREDIT, CPL_DEDICATED_CREDIT

TEST(sendNOPFlitsuite, test_six_values) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
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
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
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
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 1);
}

TEST(sendNOPFlitsuite, test_two_value) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
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
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
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
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
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
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
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

TEST(sendNOPFlitsuite, test_six_values_FC2) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
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

TEST(sendNOPFlitsuite, test_one_value_FC2) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 1);
}

TEST(sendNOPFlitsuite, test_two_value_FC2) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 2);
}

TEST(sendNOPFlitsuite, test_three_value_FC2) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 3);
}

TEST(sendNOPFlitsuite, test_four_value_FC2) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 4);
}

TEST(sendNOPFlitsuite, test_five_value_FC2) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	EXPECT_EQ(outputqueue.size(), 5);
}

TEST(sendNOPFlitsuite, test_value_mix_FC1_FC2) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
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

TEST(sendNOPFlitsuite, test_six_values_HDR_DataFC_NP) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_SHARED_CREDIT[2] = { 1,2 }; //HEADER DATA
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
				
			}
			else
				flagDedicatedP = true;
		}
		else if (dllp.m_creditType == Dllp::CreditType::NP) {
			if (dllp.shared) {
				flagSharedNP = true;
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
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

TEST(sendNOPFlitsuite, test_six_values_HDR_DataFC_CPL) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 1,2 }; //HEADER DATA
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
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
			}
			else
				flagDedicatedCPL = true;
		}
	}
	EXPECT_TRUE(flagSharedP && flagSharedNP && flagSharedCPL && flagDedicatedP && flagDedicatedNP && flagDedicatedCPL);

}

TEST(sendNOPFlitsuite, test_six_values_HDR_DataFC_P_Dedicated) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 1,2 }; //HEADER DATA
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	bool flagSharedP = false, flagDedicatedP = false, flagSharedNP = false, flagDedicatedNP = false, flagSharedCPL = false, flagDedicatedCPL = false;
	for (int i = 0; i < 6; i++) {
		Flit* flit = outputqueue.front();
		outputqueue.pop();
		Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
		if (dllp.m_creditType == Dllp::CreditType::P) {
			if (dllp.shared) {
				flagSharedP = true;
			}
			else {
				flagDedicatedP = true;
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
			}
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
TEST(sendNOPFlitsuite, test_six_values_HDR_DataFC_NP_Dedicated) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 1,2 }; //HEADER DATA
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	bool flagSharedP = false, flagDedicatedP = false, flagSharedNP = false, flagDedicatedNP = false, flagSharedCPL = false, flagDedicatedCPL = false;
	for (int i = 0; i < 6; i++) {
		Flit* flit = outputqueue.front();
		outputqueue.pop();
		Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
		if (dllp.m_creditType == Dllp::CreditType::P) {
			if (dllp.shared) {
				flagSharedP = true;
			}
			else {
				flagDedicatedP = true;
				
			}
		}
		else if (dllp.m_creditType == Dllp::CreditType::NP) {
			if (dllp.shared) {
				flagSharedNP = true;

			}
			else {
				flagDedicatedNP = true;
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
			}
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
TEST(sendNOPFlitsuite, test_six_values_HDR_DataFC_CPL_Dedicated) {
	int P_SHARED_CREDIT[2] = { 0 , 0 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 0 , 0 };
	int CPL_SHARED_CREDIT[2] = { 0 , 0 };
	int P_DEDICATED_CREDIT[2] = { 0 , 0 };
	int NP_DEDICATED_CREDIT[2] = { 0 , 0 };
	int CPL_DEDICATED_CREDIT[2] = { 1,2 }; //HEADER DATA
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	bool flagSharedP = false, flagDedicatedP = false, flagSharedNP = false, flagDedicatedNP = false, flagSharedCPL = false, flagDedicatedCPL = false;
	for (int i = 0; i < 6; i++) {
		Flit* flit = outputqueue.front();
		outputqueue.pop();
		Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
		if (dllp.m_creditType == Dllp::CreditType::P) {
			if (dllp.shared) {
				flagSharedP = true;
			}
			else {
				flagDedicatedP = true;

			}
		}
		else if (dllp.m_creditType == Dllp::CreditType::NP) {
			if (dllp.shared) {
				flagSharedNP = true;

			}
			else {
				flagDedicatedNP = true;
				
			}
		}
		else
		{
			if (dllp.shared) {
				flagSharedCPL = true;

			}
			else {
				flagDedicatedCPL = true;
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
			}
		}
	}
	EXPECT_TRUE(flagSharedP && flagSharedNP && flagSharedCPL && flagDedicatedP && flagDedicatedNP && flagDedicatedCPL);

}
TEST(sendNOPFlitsuite, test_MIX) {
	int CPL_DEDICATED_CREDIT[2] = { 1,2 }; //HEADER DATA
	int CPL_SHARED_CREDIT[2] = { 8,9 }; //HEADER DATA
	int P_DEDICATED_CREDIT[2] = { 1,2 }; //HEADER DATA
	int P_SHARED_CREDIT[2] = { 8,9}; //HEADER DATA
	int NP_DEDICATED_CREDIT[2] = { 1,2 }; //HEADER DATA
	int NP_SHARED_CREDIT[2] = { 8,9 }; //HEADER DATA
	Globals* globals = new Globals(globalsParameters);
	QueueWrapper<Flit*>* queuewrapper = new QueueWrapper<Flit*>();
	LayersWrapper* layerwrapper = new LayersWrapper();
	//sendNOPFlit(Globals globals, Dllp::DllpType dllpType, QueueWrapper<Flit*>* sendOn) 
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC1, queuewrapper);
	layerwrapper->sendNOPFlit(*globals, Dllp::DllpType::initFC2, queuewrapper);
	std::queue<Flit*> outputqueue = queuewrapper->popAll();
	bool flagSharedP = false, flagDedicatedP = false, flagSharedNP = false, flagDedicatedNP = false, flagSharedCPL = false, flagDedicatedCPL = false;
	for (int i = 0; i < 6; i++) {
		Flit* flit = outputqueue.front();
		outputqueue.pop();
		Dllp dllp = Dllp::DllpObjRep(flit->DLLPPayload);
		if (dllp.m_creditType == Dllp::CreditType::P) {
			if (dllp.shared) {
				flagSharedP = true;
				EXPECT_EQ(dllp.HdrFC, 8);
				EXPECT_EQ(dllp.DataFc, 9);
			}
			else {
				flagDedicatedP = true;
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
			}
		}
		else if (dllp.m_creditType == Dllp::CreditType::NP) {
			if (dllp.shared) {
				flagSharedNP = true;
				EXPECT_EQ(dllp.HdrFC, 8);
				EXPECT_EQ(dllp.DataFc, 9);
			}
			else {
				flagDedicatedNP = true;
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
			}
		}
		else
		{
			if (dllp.shared) {
				flagSharedCPL = true;
				EXPECT_EQ(dllp.HdrFC, 8);
				EXPECT_EQ(dllp.DataFc, 9);
			}
			else {
				flagDedicatedCPL = true;
				EXPECT_EQ(dllp.HdrFC, 1);
				EXPECT_EQ(dllp.DataFc, 2);
			}
		}
	}
	EXPECT_TRUE(flagSharedP && flagSharedNP && flagSharedCPL && flagDedicatedP && flagDedicatedNP && flagDedicatedCPL);

}