#pragma once
#include <iostream>
#include "layers/flit.h"
#include "../utils/dllp.h"
#include <bitset>

class DataLinkLayer {
public:
	void updateCreditLimit(Flit flit, int(&P_SHARED_CREDIT_LIMIT)[2], int(&NP_SHARED_CREDIT_LIMIT)[2], int(&CPL_SHARED_CREDIT_LIMIT)[2], bool& FI1, bool& FI2);
};