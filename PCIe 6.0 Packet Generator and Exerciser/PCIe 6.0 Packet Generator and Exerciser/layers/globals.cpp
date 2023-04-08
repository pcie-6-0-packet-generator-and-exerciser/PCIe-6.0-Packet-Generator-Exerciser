#include "globals.h"

Globals::Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]) {
    // Set P_CREDIT, NP_CREDIT, and CPL_CREDIT attributes
    for (int i = 0; i < 2; i++) {
        P_SHARED_CREDIT[i] = pSharedCredit[i];
        NP_SHARED_CREDIT[i] = npSharedCredit[i];
        CPL_SHARED_CREDIT[i] = cplSharedCredit[i];
        P_DEDICATED_CREDIT[i] = pDedicatedCredit[i];
        NP_DEDICATED_CREDIT[i] = npDedicatedCredit[i];
        CPL_DEDICATED_CREDIT[i] = cplDedicatedCredit[i];
    }
}