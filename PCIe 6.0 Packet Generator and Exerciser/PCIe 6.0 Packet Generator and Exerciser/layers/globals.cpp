#include "globals.h"

Globals::Globals(int pCredit[2], int npCredit[2], int cplCredit[2]) {
    // Set P_CREDIT, NP_CREDIT, and CPL_CREDIT attributes
    for (int i = 0; i < 2; i++) {
        P_CREDIT[i] = pCredit[i];
        NP_CREDIT[i] = npCredit[i];
        CPL_CREDIT[i] = cplCredit[i];
    }
}