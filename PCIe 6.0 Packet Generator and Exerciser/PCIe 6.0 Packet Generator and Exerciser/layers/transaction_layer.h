#pragma once
#include <cmath>
#include "../layers/globals.h"
#include "../utils/tlp.h"
#define CREDIT_HEADER_FIELD_SIZE 8
#define CREDIT_DATA_FIELD_SIZE 12

/**
 * @brief Represents the TransactionLayer class which implements the functionality of a transaction layer in PCIe Gen 6.
 * The transaction layer manages the flow of data and transactions across the PCIe bus, ensuring reliable and efficient communication between devices.
*/
class TransactionLayer
{
public:
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
	bool  checkGateEquation(const Globals* globals, const TLP* tlp);
};