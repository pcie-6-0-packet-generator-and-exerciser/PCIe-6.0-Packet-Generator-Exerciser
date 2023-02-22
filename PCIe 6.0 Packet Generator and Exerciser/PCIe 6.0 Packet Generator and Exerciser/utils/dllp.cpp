#include "dllp.h"


Dllp::Dllp(int hdrScale, int dataScale, int dataFc, int hdrFC, int vc, bool share, Type type, CreditType creditType) {
    HdrScale = hdrScale;
    DataScale = dataScale;
    DataFc = dataFc;
    HdrFC = hdrFC;
    VC = vc;
    m_type = type;
    m_creditType = creditType;
    shared = share;
}

Dllp::~Dllp() {
    // destructor
}

std::bitset<32> Dllp::getBitRep() const {
    // Create an unsigned int with all bits set to 0
    unsigned int bitRep = 0;

    // Add the value of DataFC in the first 12 bits (0-11)
    bitRep |= DataFc;

    // Add the value of DataScale in the next 2 bits (12-13)
    bitRep |= (DataScale << 12);

    // Add the value of HdrFC in the next 8 bits (14-21)
    bitRep |= (HdrFC << 14);

    // Add the value of HdrScale in the next 2 bits (22-23)
    bitRep |= (HdrScale << 22);

    // Add the value of VC in the next 3 bits (24-26)
    bitRep |= (VC << 24);

    // Add the value of Shared in the next bit (27)
    bitRep |= (shared << 27);

    // Add the value of CreditType in the next 2 bits (28-29)
    bitRep |= (static_cast<int>(m_creditType) << 28);

    // Add the value of Type in the last 2 bits (30-31)
    bitRep |= (static_cast<int>(m_type) << 30);

    // Return a std::bitset<32> object initialized with bitRep
    return std::bitset<32>(bitRep);
}