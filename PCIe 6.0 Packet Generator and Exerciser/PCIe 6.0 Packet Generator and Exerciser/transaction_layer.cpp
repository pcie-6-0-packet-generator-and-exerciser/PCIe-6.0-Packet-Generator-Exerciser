#include "transaction_layer.h"
#include "Tlp.h"
/**
 * @brief Checks the gate equation to determine if a TLP can be transmitted.
 * @param sharedCreditLimit An array of shared credit limits.
 *							Example: sharedCreditLimit[0] = CplDSharedCreditLimit
 *									 sharedCreditLimit[1] = CplHSharedCreditLimit
 * @param shardCreditConsumed An array of shared credit limits.
 *							  Example: shardCreditConsumed[0] = CplDSharedCreditConsumed
 *								       shardCreditConsumed[1] = CplHSharedCreditConsumed
 * @param tlp The TLP (Transaction Layer Packet) object being transmitted.
 * @return True if the gate equation is valid, false otherwise.
*/
bool TransactionLayer::checkGateEquation(int sharedCreditLimit[2], int shardCreditConsumed[2], Tlp tlp) {
	// checking for the Data gate equation
	int dataSharedCreditLimit = sharedCreditLimit[0];
	int dataSharedCreditConsumed = shardCreditConsumed[0];
	int twoPowCreditDataFieldSize = pow(CREDIT_DATA_FIELD_SIZE, 2);
	
	if ((dataSharedCreditLimit - (dataSharedCreditConsumed + tlp.dataConsumption) % twoPowCreditDataFieldSize) % twoPowCreditDataFieldSize > twoPowCreditDataFieldSize / 2)
		return false;

	// checking for the Header gate equation
	int headerSharedCreditLimit = sharedCreditLimit[1];
	int headerSharedCreditConsumed = shardCreditConsumed[1];
	int twoPowCreditDataFieldSize = pow(CREDIT_HEADER_FIELD_SIZE, 2);
	
	if ((headerSharedCreditLimit - (headerSharedCreditConsumed + tlp.headerConsumption) % twoPowCreditDataFieldSize) % twoPowCreditDataFieldSize > twoPowCreditDataFieldSize / 2)
		return false;

	return true;
}