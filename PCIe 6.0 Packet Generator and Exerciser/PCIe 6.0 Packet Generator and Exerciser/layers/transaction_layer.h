#pragma once
#include <math.h>
#define CREDIT_HEADER_FIELD_SIZE 8
#define CREDIT_DATA_FIELD_SIZE 12

/**
 * @brief Represents the TransactionLayer class which implements the functionality of a transaction layer in PCIe Gen 6.
 * The transaction layer manages the flow of data and transactions across the PCIe bus, ensuring reliable and efficient communication between devices.
*/
class TransactionLayer
{
public:
	bool checkGateEquation(int sharedCreditLimit[2], int shardCreditConsumed[2], Tlp tlp);
};