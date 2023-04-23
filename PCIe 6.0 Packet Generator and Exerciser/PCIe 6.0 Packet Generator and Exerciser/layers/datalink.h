#pragma once
#include <iostream>
#include "../layers/flit.h"
#include "../utils/dllp.h"
#include "boost/dynamic_bitset.hpp"
#include "CRC.h"

class DatalinkLayer {
private:
	/**
	 * @brief This function adds a DLLP to a flit
	 * @param flit The flit that the DLLP is added to
	 * @param dllpType The enum type of the DLLP
	 * @param creditType The enum type of the credit to inform the receiver of
	 * @param shared Whether the credit is shared or dedicated
	 * @param credit The credit to inform the receiver of
	 * @return The flit after adding the DLLP
	*/
	Flit* addDLLP(Flit* flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
	/**
	 * @brief Just adds the CRC value to the flit
	 * @param flit a pointer to the flit to add the CRC to
	 * @return pointer to a flit with the CRC added
	*/
	Flit* addCRC(Flit* flit);
public:
	void updateCreditLimit(Flit flit, int P_SHARED_CREDIT_LIMIT[], int NP_SHARED_CREDIT_LIMIT[], int CPL_SHARED_CREDIT_LIMIT[], int P_DEDICATED_CREDIT_LIMIT[], int NP_DEDICATED_CREDIT_LIMIT[], int CPL_DEDICATED_CREDIT_LIMIT[], bool& FI1, bool& FI2);
	
	/**
	 * @brief Calculates the CRC for a given Flit object.
	 * @param flit pointer to the Flit object to calculate the CRC for.
	 * @return A dynamic_bitset object representing the calculated CRC.
	*/
	boost::dynamic_bitset<> calculateCRC(Flit* flit);
};