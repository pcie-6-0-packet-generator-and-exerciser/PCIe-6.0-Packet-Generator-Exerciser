#pragma once
#include <bitset>

class Dllp {
public:
    enum class Type {
        initFC1 = 1,
        initFC2 = 3,
        updateFC = 2
    };
    enum class CreditType {
        P = 0,
        NP = 1,
        Cpl = 2
    };
    int HdrScale;
    int DataScale;
    int DataFc;
    int HdrFC;
    int VC;
    bool shared;
    Type m_type;
    CreditType m_creditType;

    Dllp(int hdrScale, int dataScale, int dataFc, int hdrFC, int vc, bool share, Type type, CreditType creditType);

    ~Dllp();
    std::bitset<32> getBitRep() const;
};
