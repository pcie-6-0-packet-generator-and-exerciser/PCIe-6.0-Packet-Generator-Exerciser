#include "transaction_layer.h"

bool  TransactionLayer::checkGateEquation(const Globals* globals, const TLP* tlp) {

	// getting the shared credit limit and shared credit consumed
	int sharedCreditLimit[2], shardCreditConsumed[2], tlpDataConsumption, tlpHeaderConsumption;

	//switch (tlp->header->TLPtype)
	//{
	//case TLPType::MemoryRead:
	//default:
	//	break;
	//}

	// checking for the Data gate equation
	int dataSharedCreditLimit = sharedCreditLimit[1];
	int dataSharedCreditConsumed = shardCreditConsumed[1];
	int twoPowCreditDataFieldSize = pow(2, CREDIT_DATA_FIELD_SIZE);

	if ((dataSharedCreditLimit - (dataSharedCreditConsumed + tlpDataConsumption) % twoPowCreditDataFieldSize) % twoPowCreditDataFieldSize > twoPowCreditDataFieldSize / 2)
		return false;

	// checking for the Header gate equation
	int headerSharedCreditLimit = sharedCreditLimit[0];
	int headerSharedCreditConsumed = shardCreditConsumed[0];
	int twoPowCreditHeaderFieldSize = pow(2, CREDIT_HEADER_FIELD_SIZE);

	if ((headerSharedCreditLimit - (headerSharedCreditConsumed + tlpHeaderConsumption) % twoPowCreditHeaderFieldSize) % twoPowCreditHeaderFieldSize > twoPowCreditHeaderFieldSize / 2)
		return false;

	return true;
}