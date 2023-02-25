#include "transaction_layer.h"
#include "Tlp.h"
/**
 * @brief Checks the gate equation to determine if a TLP can be transmitted.
 * @param sharedCreditLimit An array of shared credit limits.
 *							Example: sharedCreditLimit[1] = CplDSharedCreditLimit
 *									 sharedCreditLimit[0] = CplHSharedCreditLimit
 * @param shardCreditConsumed An array of shared credit limits.
 *							  Example: shardCreditConsumed[1] = CplDSharedCreditConsumed
 *								       shardCreditConsumed[0] = CplHSharedCreditConsumed
 * @param tlp The TLP (Transaction Layer Packet) object being transmitted.
 * @return True if the gate equation is valid, false otherwise.
*/
bool TransactionLayer::checkGateEquation(int sharedCreditLimit[2], int shardCreditConsumed[2], Tlp tlp) {
	// checking for the Data gate equation
	int dataSharedCreditLimit = sharedCreditLimit[1];
	int dataSharedCreditConsumed = shardCreditConsumed[1];
	int twoPowCreditDataFieldSize = pow(2, CREDIT_DATA_FIELD_SIZE);

	if ((dataSharedCreditLimit - (dataSharedCreditConsumed + tlp.dataConsumption) % twoPowCreditDataFieldSize) % twoPowCreditDataFieldSize > twoPowCreditDataFieldSize / 2)
		return false;

	// checking for the Header gate equation
	int headerSharedCreditLimit = sharedCreditLimit[0];
	int headerSharedCreditConsumed = shardCreditConsumed[0];
	int twoPowCreditDataFieldSize = pow(2, CREDIT_HEADER_FIELD_SIZE);

	if ((headerSharedCreditLimit - (headerSharedCreditConsumed + tlp.headerConsumption) % twoPowCreditDataFieldSize) % twoPowCreditDataFieldSize > twoPowCreditDataFieldSize / 2)
		return false;

	return true;
}