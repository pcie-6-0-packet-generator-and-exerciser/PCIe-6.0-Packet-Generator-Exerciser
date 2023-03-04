#pragma once
#include "flit.h"
#include "../utils/dllp.h"

class DatalinkLayer {
	Flit *addDLLP(Flit *flit, Dllp::DllpType dllpType, Dllp::CreditType creditType, bool shared, int credit[]);
};