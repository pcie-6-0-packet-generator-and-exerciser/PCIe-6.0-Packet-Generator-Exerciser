#pragma once
#include <iostream>
#include "../layers/flit.h"
#include "../utils/dllp.h"
#include "boost/dynamic_bitset.hpp"

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
	Flit *addDLLP(Flit *flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
  
public:
	void updateCreditLimit(Flit flit, int P_SHARED_CREDIT_LIMIT[], int NP_SHARED_CREDIT_LIMIT[], int CPL_SHARED_CREDIT_LIMIT[], int P_DEDICATED_CREDIT_LIMIT[], int NP_DEDICATED_CREDIT_LIMIT[], int CPL_DEDICATED_CREDIT_LIMIT[], bool& FI1, bool& FI2);

};