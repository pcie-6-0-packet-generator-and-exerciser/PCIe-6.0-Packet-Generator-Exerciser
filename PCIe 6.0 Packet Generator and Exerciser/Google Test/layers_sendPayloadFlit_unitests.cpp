#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/layers_wrapper.h"

// macro instead of leaving it global to avoid change from other test cases
#define DEFAULT_CREDIT_PARAMS int pSharedCredit[] = {1, 2};\
int npSharedCredit[] = { 10, 10 };\
int cplSharedCredit[] = { 10, 10 };\
int pDedicatedCredit[] = { 10, 10 };\
int npDedicatedCredit[] = { 10, 10 };\
int cplDedicatedCredit[] = { 10, 10 }

#define DEFAULT_CREDIT_VALUES pSharedCredit, npSharedCredit, cplSharedCredit, pDedicatedCredit, npDedicatedCredit, cplDedicatedCredit

#define DEFAULT_MEM_READ32_TLP_PARAMS 0, 0, 0, 0, 0
#define DEFAULT_MEM_WRITE32_TLP_PARAMS 0, boost::dynamic_bitset<>(), 0, 0, 0, 0, 0

// Test Suite: SendPayloadFlitTestSuite
// Description: This test suite contains test cases for the sendPayloadFlit() function.

// global layersWrapper object to be used in all test cases
// static to avoid accessing from other files
static LayersWrapper layersWrapper;

// Test Case: PassGateEquation
// Description: Pass a queue of one TLP, which shouldn't pass the gate equation. Which will make the function return without sending any flits
// Input: one TLP object in a queue
// Expected Output: sendOnQueue should conatin one std::queue<Flit*> object, which should contain 1 tlp
TEST(SendPayloadFlitTestSuite, PassGateEquation) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemRead32Tlp(DEFAULT_MEM_READ32_TLP_PARAMS);
	tlp->dataConsumption = 0; // change tlp data consumption to Pass the gate equation
	tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin one std::queue<Flit*> object, which should contain 1 tlp
	EXPECT_EQ(sendOnQueue.size(), 1);
	EXPECT_EQ(sendOnQueue.pop()->firstHalfTLPCount, 1);
}


// Test Case: AddOneTlpToFlit
// Description: Pass a queue of one TLP, which its size is one. Which will make the function send 1 flit with firstHalfTLPCount = 1
// Input: one TLP object in a queue
// Expected Output: sendOnQueue should conatin one std::queue<Flit*> object, which should contain one tlp with firstHalfTLPCount = 1
TEST(SendPayloadFlitTestSuite, AddOneTlpToFlit) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemWrite32Tlp(DEFAULT_MEM_WRITE32_TLP_PARAMS);

	// making a tlp payload of zero size, so Tlp::getTotalLength() -> 1
	tlp->header->OHCVector.resize(0);
	tlp->header->lengthInDoubleWord = 0;
	tlp->header->nonBase->headerSizeInBytes = 1;

	tlpPackets.push(tlp);
	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin one std::queue<Flit*> object, which should contain one tlp with firstHalfTLPCount = 1
	EXPECT_EQ(sendOnQueue.size(), 1);
	EXPECT_EQ(sendOnQueue.pop()->firstHalfTLPCount, 1);
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

	// making a tlp payload of zero size, so Tlp::getTotalLength() -> 0, and not exceeding the flit size
	tlp->header->OHCVector.resize(0);
	tlp->header->lengthInDoubleWord = 0;
	tlp->header->nonBase->headerSizeInBytes = 0;

	for (int i = 0; i < 9; ++i) tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin one std::queue<Flit*> object, which should contain 9 tlps with firstHalfTLPCount = 8, and secondHalfTLPCount = 1
	EXPECT_EQ(sendOnQueue.size(), 1);

	Flit* sentFlit = sendOnQueue.pop();
	EXPECT_EQ(sentFlit->firstHalfTLPCount, 8);
	EXPECT_EQ(sentFlit->firstHalfTLPCount, 1);
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

	// making a tlp payload of maximum size possible, so Tlp::getTotalLength() -> INT_MAX, and exceed the size of a tlp to be sent in one flit
	tlp->header->OHCVector.resize(0);
	tlp->header->lengthInDoubleWord = 0;
	tlp->header->nonBase->headerSizeInBytes = INT_MAX;

	tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin multiple Flits
	EXPECT_NE(sendOnQueue.size(), 1);
}

// Test Case: FailGateEquation
// Description: Pass a queue of one TLP, which shouldn't pass the gate equation. Which will make the function return without sending any flits
// Input: one TLP object in a queue
// Expected Output: sendOnQueue should conatin one std::queue<Flit*> object, which should be empty
TEST(SendPayloadFlitTestSuite, FailGateEquation) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemRead32Tlp(DEFAULT_MEM_READ32_TLP_PARAMS);
	tlp->dataConsumption = INT_MAX; // change tlp data consumption to fail the gate equation
	tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin one std::queue<Flit*> object, which should be empty
	EXPECT_EQ(sendOnQueue.size(), 1);
	EXPECT_EQ(sendOnQueue.pop()->firstHalfTLPCount, 0);
}


// Test Case: FailToFitInOneFlit
// Description: Pass a queue of one TLP, which its size is bigger than the max size of a flit. Which will make the function return without sending any flits
// Input: one TLP object in a queue
// Expected Output: sendOnQueue should conatin one std::queue<Flit*> object, which should be empty
TEST(SendPayloadFlitTestSuite, FailToFitInOneFlit) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemWrite32Tlp(DEFAULT_MEM_WRITE32_TLP_PARAMS);
	tlp->header->lengthInDoubleWord = INT_MAX; // make the tlp can't fit in one flit
	tlpPackets.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	// sendOnQueue should conatin one std::queue<Flit*> object, which should be empty
	EXPECT_EQ(sendOnQueue.size(), 1);
	EXPECT_EQ(sendOnQueue.pop()->firstHalfTLPCount, 0);
}

// Test Case: SharedCreditsUpdate
// Description: Pass a queue of one Mem32Write TLP, and then check if the shared credits consmed in decrimented or not
// Input: one TLP object in a queue
// Expected Output: the PSharedCredits should be decremented by the header consumption of the TLP
TEST(SendPayloadFlitTestSuite, SharedCreditsUpdate) {
	DEFAULT_CREDIT_PARAMS;

	// sendPayloadFlit() params
	std::queue<TLP*> tlpPackets;
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<Flit*> sendOnQueue;

	TLP* tlp = TLP::createMemWrite32Tlp(DEFAULT_MEM_WRITE32_TLP_PARAMS);

	// making a tlp that consumes only one credit
	tlp->headerConsumption = 1;

	tlpPackets.push(tlp);
	layersWrapper.sendPayloadFlit(globals, tlpPackets, sendOnQueue);

	EXPECT_EQ(globals.P_SHARED_CREDIT[0], pSharedCredit[0] - tlp->headerConsumption);
}