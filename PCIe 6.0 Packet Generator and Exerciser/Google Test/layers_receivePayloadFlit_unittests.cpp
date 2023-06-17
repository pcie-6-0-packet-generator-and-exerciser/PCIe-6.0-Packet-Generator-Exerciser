#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/layers/layers_wrapper.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/utils/queue_wrapper.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/utils/non_header_base.h"

// macro instead of leaving it global to avoid change from other test cases
#define DEFAULT_CREDIT_PARAMS int pSharedCredit[] = {10, 10};\
int npSharedCredit[] = { 10, 10};\
int cplSharedCredit[] = { 10, 10 };\
int pDedicatedCredit[] = { 10, 10 };\
int npDedicatedCredit[] = { 10, 10 };\
int cplDedicatedCredit[] = { 10, 10 }

#define DEFAULT_CREDIT_VALUES pSharedCredit, npSharedCredit, cplSharedCredit, pDedicatedCredit, npDedicatedCredit, cplDedicatedCredit

#define DEFAULT_MEM_READ32_TLP_PARAMS 0, 0, 0, 0, 0
#define DEFAULT_MEM_WRITE32_TLP_PARAMS 0, boost::dynamic_bitset<>(), 0, 0, 0, 0, 0

// Test Suite: ReceivePayloadFlitTestSuite
// Description: This test suite contains test cases for the receivePayloadFlit() function.

// global layersWrapper object to be used in all test cases
// static to avoid accessing from other files
static LayersWrapper layersWrapper;

// Test case to verify that receivePayloadFlit correctly handles an empty TLP payload
TEST(ReceivePayloadFlitTestSuite, EmptyTLPPayload) {
	// Set up default credit parameters
	DEFAULT_CREDIT_PARAMS;

	// Set up parameters for receivePayloadFlit
	Globals globals(DEFAULT_CREDIT_VALUES);
	QueueWrapper<TLP*> sendOnQueue;
	std::queue<Flit*> flits;

	// Create a single empty flit and add it to the queue
	Flit* flit = new Flit();
	flits.push(flit);

	// Call receivePayloadFlit with the empty flit and check that no TLPs were sent
	layersWrapper.receivePayloadFlit(globals, flits, sendOnQueue);
	EXPECT_EQ(sendOnQueue.size(), 0);

	// Check that there's no change in the credit values
	EXPECT_EQ(globals.P_SHARED_CREDIT[0], pSharedCredit[0]);
	EXPECT_EQ(globals.P_SHARED_CREDIT[1], pSharedCredit[1]);
	EXPECT_EQ(globals.NP_SHARED_CREDIT[0], npSharedCredit[0]);
	EXPECT_EQ(globals.NP_SHARED_CREDIT[1], npSharedCredit[1]);
	EXPECT_EQ(globals.CPL_SHARED_CREDIT[0], cplSharedCredit[0]);
	EXPECT_EQ(globals.CPL_SHARED_CREDIT[1], cplSharedCredit[1]);
}

TEST(ReceivePayloadFlitTestSuite, SingleFlitTLPPayload) {
	// Set up default credit parameters
	DEFAULT_CREDIT_PARAMS;
	Globals globals(DEFAULT_CREDIT_VALUES);

	// Set up parameters for sendPayloadFlit
	QueueWrapper<Flit*> sendOnQueueFlits;
	std::queue<TLP*> tlps;

	TLP* tlp = TLP::createMemRead32Tlp(DEFAULT_MEM_READ32_TLP_PARAMS);
	tlps.push(tlp);

	layersWrapper.sendPayloadFlit(globals, tlps, sendOnQueueFlits);

	// Set up parameters for receivePayloadFlit
	QueueWrapper<TLP*> sendOnQueueTlps;
	std::queue<Flit*> flits;

	Flit* flit = sendOnQueueFlits.pop();
	flits.push(flit);

	layersWrapper.receivePayloadFlit(globals, flits, sendOnQueueTlps);

	// Check that the TLP was sent
	EXPECT_EQ(sendOnQueueTlps.size(), 1);

	TLP* receivedTlp = sendOnQueueTlps.pop();
	EXPECT_EQ(receivedTlp->header->TLPtype, TLPType::MemRead32);
	EXPECT_EQ(receivedTlp->header->lengthInDoubleWord, 0);
	EXPECT_EQ(receivedTlp->header->nonBase->requestID, 0);
	EXPECT_EQ(receivedTlp->header->nonBase->getTag(), 0);
	EXPECT_EQ(dynamic_cast<AddressRouting32Bit*>(receivedTlp->header->nonBase)->address, 0);
	EXPECT_EQ(receivedTlp->header->OHCVector.size(), 1);
	
	auto ohca1 = dynamic_cast<OHCA1*>(receivedTlp->header->OHCVector[0]);
	EXPECT_EQ(ohca1->firstDWBE.to_ulong(), 0);
	EXPECT_EQ(ohca1->lastDWBE.to_ulong(), 0);

	EXPECT_EQ(receivedTlp->creditConsumedType, Dllp::CreditType::NP);
	EXPECT_EQ(receivedTlp->headerConsumption, 1);
	EXPECT_EQ(receivedTlp->dataConsumption, 0);
}