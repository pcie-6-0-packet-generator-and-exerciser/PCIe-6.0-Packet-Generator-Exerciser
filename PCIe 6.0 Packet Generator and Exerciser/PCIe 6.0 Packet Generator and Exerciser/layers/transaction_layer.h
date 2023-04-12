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
	 * @brief Checks the gate equation for a TLP.
	 * @param globals pointer for Globals object
	 * @param tlp pointer for TLP object
	 * @return True if the gate equation is satisfied, false otherwise
	*/
	bool  checkGateEquation(const Globals globals, const TLP tlp);
};