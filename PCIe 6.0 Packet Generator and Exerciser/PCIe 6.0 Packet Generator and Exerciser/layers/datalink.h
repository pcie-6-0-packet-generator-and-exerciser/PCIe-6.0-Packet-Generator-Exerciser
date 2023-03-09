#pragma once
#include "flit.h"
#include "../utils/dllp.h"

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
};