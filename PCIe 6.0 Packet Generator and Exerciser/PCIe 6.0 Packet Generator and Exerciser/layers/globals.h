#pragma once
class Globals {
public:
    int P_SHARED_CREDIT[2];
    int NP_SHARED_CREDIT[2];
    int CPL_SHARED_CREDIT[2];
    int P_DEDICATED_CREDIT[2];
    int NP_DEDICATED_CREDIT[2];
    int CPL_DEDICATED_CREDIT[2];
    bool Fl1 = false;
    bool Fl2 = false;
    int P_SHARED_CREDIT_LIMIT[2] = {-1, -1 };
    int NP_SHARED_CREDIT_LIMIT[2] = {-1, -1 };
    int CPL_SHARED_CREDIT_LIMIT[2] = {-1, -1 };
    int P_DEDICATED_CREDIT_LIMIT[2] = {-1, -1 };
    int NP_DEDICATED_CREDIT_LIMIT[2] = {-1, -1 };
    int CPL_DEDICATED_CREDIT_LIMIT[2] = {-1, -1 };
    int P_SHARED_CREDITS_CONSUMED[2] = {0, 0};
    int NP_SHARED_CREDITS_CONSUMED[2] = {0, 0};
    int CPL_SHARED_CREDITS_CONSUMED[2] = {0, 0};
    int P_DEDICATED_CREDITS_CONSUMED[2] = {0, 0};
    int NP_DEDICATED_CREDITS_CONSUMED[2] = {0, 0};
    int CPL_DEDICATED_CREDITS_CONSUMED[2] = {0, 0};

    Globals(int pSharedCredit[2], int npSharedCredit[2], int cplSharedCredit[2], int pDedicatedCredit[2], int npDedicatedCredit[2], int cplDedicatedCredit[2]);
};