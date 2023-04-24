#pragma once
#include <iostream>
#include "../layers/flit.h"
#include "../utils/dllp.h"
#include "boost/dynamic_bitset.hpp"
#include "boost/crc.hpp"
#include <vector>
#include <queue>

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

	/**
	 * @brief Check the CRC of the flit with the CRCPayload 
	 * @param flit 
	 * @return true if they are the same / false if they are not the same
	*/
	bool checkCRC(Flit* flit);


public:
	/**
	 * @brief sends a FLIT after adding DLLP and CRC values to the receiver
	 * @param flit The FLIT to be sent
	 * @param sendOn The queue where the FLIT will be pushed
	 * @param dllpType The type of DLLP to be added to the FLIT
	 * @param creditType The type of credit to be added to the FLIT
	 * @param shared Whether the credit is shared or dedicated
	 * @param credit An array containing header and data credits
	*/
	void pushFlitToQueue(Flit* flit, std::queue<Flit*>* sendOn, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);

	/**
	 * @brief Updates the shared credit limit values based on the received DLLP information
	 * @param flit Flit containing the DLLPs
	 * @param P_SHARED_CREDIT_LIMIT Array of shared credit limit for posted traffic
	 * @param NP_SHARED_CREDIT_LIMIT Array of shared credit limit for non-posted traffic
	 * @param CPL_SHARED_CREDIT_LIMIT Array of shared credit limit for completion traffic
	 * @param FI1 First indication (FI1) flag for credit update
	 * @param FI2 Second indication (FI2) flag for credit update
	*/
	void updateCreditLimit(Flit flit, int P_SHARED_CREDIT_LIMIT[], int NP_SHARED_CREDIT_LIMIT[], int CPL_SHARED_CREDIT_LIMIT[], int P_DEDICATED_CREDIT_LIMIT[], int NP_DEDICATED_CREDIT_LIMIT[], int CPL_DEDICATED_CREDIT_LIMIT[], bool& FI1, bool& FI2);

	/**
	 * @brief Calculates the CRC for a given Flit object.
	 * @param flit pointer to the Flit object to calculate the CRC for.
	 * @return A dynamic_bitset object representing the calculated CRC.
	*/
	boost::dynamic_bitset<> calculateCRC(Flit* flit);
};