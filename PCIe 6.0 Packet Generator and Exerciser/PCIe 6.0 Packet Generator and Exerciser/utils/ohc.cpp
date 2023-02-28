#include "ohc.h"

std::bitset<32> OHCA1::getBitRep() const {
    std::bitset<32> result;
    for (int i = 0; i < 4; i++) {
        result[i] = firstDWBE[i];
    }
    for (int i = 0; i < 4; i++) {
        result[i + 4] = lastDWBE[i];
    }
    return result;
}

std::bitset<32> OHCA3::getBitRep() const {
    std::bitset<32> result;
    for (int i = 0; i < 4; i++) {
        result[i] = firstDWBE[i];
    }
    for (int i = 0; i < 4; i++) {
        result[i + 4] = lastDWBE[i];
    }
    result |= (destinationSegment << 24);
    return result;
}

std::bitset<32> OHCA4::getBitRep() const {
    std::bitset<32> result;
    result |= (destinationSegment << 24);
    return result;
}

std::bitset<32> OHCA5::getBitRep() const {
    std::bitset<32> result;

    result |= static_cast<int>(CPLStatusEnum);

    for (int i = 0; i < 2; i++) {
        result[i+3] = lowerAddress[i];
    }
    result |= (completerSegment << 16);

    result |= (destinationSegment << 24);
    return result;
}

