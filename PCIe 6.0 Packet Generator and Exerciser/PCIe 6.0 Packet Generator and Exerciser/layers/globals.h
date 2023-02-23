#pragma once
class Globals {
public:
    int P_CREDIT[2];
    int NP_CREDIT[2];
    int CPL_CREDIT[2];
    bool Fl1 = false;
    bool Fl2 = false;
    int P_SHARED_CREDIT_LIMIT[2] = { -1 };
    int NP_SHARED_CREDIT_LIMIT[2] = { -1 };
    int CPL_SHARED_CREDIT_LIMIT[2] = { -1 };
    int P_SHARED_CREDITS_CONSUMED[2];
    int NP_SHARED_CREDITS_CONSUMED[2];
    int CPL_SHARED_CREDITS_CONSUMED[2];

    Globals(int pCredit[2], int npCredit[2], int cplCredit[2]);
};