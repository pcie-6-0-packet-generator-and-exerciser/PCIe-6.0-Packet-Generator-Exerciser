#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/layers_wrapper.h"

// macro instead of leaving it global to avoid change from other test cases
#define DEFAULT_CREDIT_PARAMS int pSharedCredit[] = {10, 10};\
int npSharedCredit[] = { 10, 10};\
int cplSharedCredit[] = { 10, 10 };\
int pDedicatedCredit[] = { 10, 10 };\
int npDedicatedCredit[] = { 10, 10 };\
int cplDedicatedCredit[] = { 10, 10 }

#define DEFAULT_CREDIT_VALUES pSharedCredit, npSharedCredit, cplSharedCredit, pDedicatedCredit, npDedicatedCredit, cplDedicatedCredit

#define DEFAULT_MEM_READ32_TLP_PARAMS 0, boost::dynamic_bitset<>(), 0, 0, 0, 0, 0
#define DEFAULT_MEM_WRITE32_TLP_PARAMS 0, boost::dynamic_bitset<>(), 0, 0, 0, 0, 0

// Test Suite: SendPayloadFlitTestSuite
// Description: This test suite contains test cases for the sendPayloadFlit() function.

// global layersWrapper object to be used in all test cases
// static to avoid accessing from other files
static LayersWrapper layersWrapper;

// Test Case: PassGateEquation
// Description: Pass a queue of one TLP, which should pass the gate equation. Which will make the function return with sending only 1 flit
// Input: one TLP object in a queue
// Expected Output: sendOnQueue should have a queue of flits, which should contain 1 flit contating only 1 tlp
TEST(SendPayloadFlitTestSuite, PassGateEquation) {
	DEFAULT_CREDIT_PARAMS;
	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemRead32Tlp(DEFAULT_MEM_READ32_TLP_PARAMS);
	// Change the values of the globals, and tlp data consumption to pass the gate equation
	tlp->dataConsumption = 0;
	globals.NP_SHARED_CREDIT_LIMIT[0] = 0;
	globals.NP_SHARED_CREDIT_LIMIT[1] = 0;

	tlpPackets.push(tlp);
	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin only one queue of flits, which should contain 1 tlp
	EXPECT_EQ(sendOnQueue.size(), 1);
	
	Flit* flit = sendOnQueue.pop();
	EXPECT_EQ(flit->firstHalfTLPCount + flit->secondHalfTLPCount, 1);
}


// Test Case: AddNineTlpToFlit
// Description: Adding 9 Tlps to the flit, which will make the function send 1 flit with firstHalfTLPCount = 8 and secondHalfTLPCount = 1
// Input: 9 TLPs objects in a queue
// Expected Output: firstHalfTLPCount = 8 and secondHalfTLPCount = 1
TEST(SendPayloadFlitTestSuite, AddNineTlpToFlit) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemWrite32Tlp(DEFAULT_MEM_WRITE32_TLP_PARAMS);

	for (int i = 0; i < 9; ++i) tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin queue of flits contating only one flit, which should contain 9 tlps with firstHalfTLPCount = 8, and secondHalfTLPCount = 1
	EXPECT_EQ(sendOnQueue.size(), 1);

	Flit* flit = sendOnQueue.pop();
	EXPECT_EQ(flit->firstHalfTLPCount, 8);
	EXPECT_EQ(flit->secondHalfTLPCount, 1);
}

// Test Case: BigTlpToFlit
// Description: Adding a Tlp to the flit, Its size is bigger than 236 bits, which will make the function send multiple flits
// Input: Tlp with size bigger than 236 bits
// Expected Output: sendOnQueue should conatin two std::queue<Flit*> objects, which should contain more than 1 flit
TEST(SendPayloadFlitTestSuite, BigTlpToFlit) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemWrite32Tlp(DEFAULT_MEM_WRITE32_TLP_PARAMS);

	// making a tlp payload of Huge size possible, so Tlp::getTotalLength() -> +10000, and exceed the size of a tlp to be sent in one flit
	tlp->header->lengthInDoubleWord = 10000;
	tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin multiple Flits
	EXPECT_GT(sendOnQueue.size(), 1);
}

// Test Case: FailGateEquation
// Description: Pass a queue of one TLP, which shouldn't pass the gate equation. Which will make the function return without sending any flits
// Input: one TLP object in a queue
// Expected Output: sendOnQueue should conatin one queue of flits, containig 1 flit which should be empty
TEST(SendPayloadFlitTestSuite, FailGateEquation) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemRead32Tlp(DEFAULT_MEM_READ32_TLP_PARAMS);
	// change values to fail the gate equation
	globals.NP_SHARED_CREDIT_LIMIT[0] = 2000;
	globals.NP_SHARED_CREDIT_LIMIT[1] = 2000;
	tlp->dataConsumption = 0;

	tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin one std::queue<Flit*> object, which should be empty
	EXPECT_EQ(sendOnQueue.size(), 1);
	EXPECT_EQ(sendOnQueue.pop()->firstHalfTLPCount, 0);
}

// Test Case: SharedCreditsUpdate
// Description: Pass a queue of one Mem32Write TLP, and then check if the shared credits consmed is incremented 
// Input: one TLP object in a queue
// Expected Output: the PSharedCredits should be decremented by the header consumption of the TLP
TEST(SendPayloadFlitTestSuite, SharedCreditsUpdate) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	int oldPsharedCreditLimitConsumedHeader = globals.P_SHARED_CREDITS_CONSUMED[0];
	int oldPsharedCreditLimitConsumedData = globals.P_SHARED_CREDITS_CONSUMED[1];

	TLP* tlp = TLP::createMemWrite32Tlp(DEFAULT_MEM_WRITE32_TLP_PARAMS);

	tlpPackets.push(tlp);
	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	EXPECT_EQ(globals.P_SHARED_CREDITS_CONSUMED[0], oldPsharedCreditLimitConsumedHeader + tlp->headerConsumption);
	EXPECT_EQ(globals.P_SHARED_CREDITS_CONSUMED[1], oldPsharedCreditLimitConsumedHeader + tlp->dataConsumption);
}

// Test Case: Add17TlpToFlit
// Description: Adding 17 Tlps to the flit, which will make the function send 2 flits 
// Input: 17 TLPs objects in a queue
// Expected Output: 2 flits in the queue
TEST(SendPayloadFlitTestSuite, Add17TlpToFlit) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemWrite32Tlp(DEFAULT_MEM_WRITE32_TLP_PARAMS);

	for (int i = 0; i < 17; ++i) tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin queue of flits contating only two flits
	EXPECT_EQ(sendOnQueue.size(), 2);
}

