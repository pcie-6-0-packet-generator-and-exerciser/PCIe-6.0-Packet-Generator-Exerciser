#include "dllp.h"

Dllp::Dllp(int HdrScale, bool shared, int VC, int HdrFC, int DataScale, int DataFC, CreditType credType, Type dataType) {
    
    this->HdrScale = HdrScale;
    this->shared = shared;
    this->VC = VC;
    this->HdrFC = HdrFC;
    this->DataScale = DataScale;
    this->DataFC = DataFC;
    this->creditType = credType;
    this->type = dataType;
}

Dllp::~Dllp() {
}

std::array<bool, 32> Dllp::getBitRep() const {
    std::array<bool, 32> result;
    int idx = 0;
    std::bitset<12> datafc_bits(DataFC);
    for (int i = 0; i <12 ; i++) {
        result[idx++] = datafc_bits[i];
    }
    std::bitset<2> datascale_bits(DataScale);
    for (int i = 0; i < 2 ; i++) {
        result[idx++] = datascale_bits[i];
    }
    std::bitset<8> hdrfc_bits(HdrFC);
    for (int i = 0; i < 8 ; i++) {
        result[idx++] = hdrfc_bits[i];
    }
    std::bitset<2> hdrscale_bits(HdrScale);
    for (int i = 0; i < 2 ; i++) {
        result[idx++] = hdrscale_bits[i];
    }
    std::bitset<3> vc_bits(VC);
    for (int i = 0; i < 3 ; i++) {
        result[idx++] = vc_bits[i];
    }
    result[idx++] = shared;
    std::bitset<2> fctype_bits(static_cast<int>(creditType));
    for (int i = 0; i < 2 ; i++) {
        result[idx++] = fctype_bits[i];
    }
    std::bitset<2> datatype_bits(static_cast<int>(type));
    for (int i = 0; i < 2 ; i++) {
        result[idx++] = datatype_bits[i];
    }
    return result;
}