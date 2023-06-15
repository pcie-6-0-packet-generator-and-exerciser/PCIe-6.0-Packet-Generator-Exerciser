#include "transaction_layer.h"


bool  TransactionLayer::checkGateEquation(const Globals globals, const TLP* tlp) {
	// shared credit limit and shared credit consumed for header and data
	int dataSharedCreditLimit, dataSharedCreditConsumed, headerSharedCreditLimit, headerSharedCreditConsumed;

	// Tlp data and header consumption
	int tlpDataConsumption = tlp.dataConsumption;
	int tlpHeaderConsumption = tlp.headerConsumption;

	// getting the shared credit limit and shared credit consumed based on the Tlp credit consumption type
	switch (tlp.creditConsumedType)
	{
	case Dllp::CreditType::Cpl:
		headerSharedCreditLimit = globals.CPL_SHARED_CREDIT_LIMIT[0];
		dataSharedCreditLimit = globals.CPL_SHARED_CREDIT_LIMIT[1];
		headerSharedCreditConsumed = globals.CPL_SHARED_CREDITS_CONSUMED[0];
		dataSharedCreditConsumed = globals.CPL_SHARED_CREDITS_CONSUMED[1];
		break;
	case Dllp::CreditType::NP:
		headerSharedCreditLimit = globals.NP_SHARED_CREDIT_LIMIT[0];
		dataSharedCreditLimit = globals.NP_SHARED_CREDIT_LIMIT[1];
		headerSharedCreditConsumed = globals.NP_SHARED_CREDITS_CONSUMED[0];
		dataSharedCreditConsumed = globals.NP_SHARED_CREDITS_CONSUMED[1];
		break;
	case Dllp::CreditType::P:
		headerSharedCreditLimit = globals.P_SHARED_CREDIT_LIMIT[0];
		dataSharedCreditLimit = globals.P_SHARED_CREDIT_LIMIT[1];
		headerSharedCreditConsumed = globals.P_SHARED_CREDITS_CONSUMED[0];
		dataSharedCreditConsumed = globals.P_SHARED_CREDITS_CONSUMED[1];
		break;
	}

	if ((dataSharedCreditLimit - (dataSharedCreditConsumed + tlpDataConsumption) % TWO_POW_CREDIT_DATA_FIELD_SIZE) % TWO_POW_CREDIT_DATA_FIELD_SIZE > TWO_POW_CREDIT_DATA_FIELD_SIZE / 2)
		return false;

	if ((headerSharedCreditLimit - (headerSharedCreditConsumed + tlpHeaderConsumption) % TWO_POW_CREDIT_HEADER_FIELD_SIZE) % TWO_POW_CREDIT_HEADER_FIELD_SIZE > TWO_POW_CREDIT_HEADER_FIELD_SIZE / 2)
		return false;

	return true;
}