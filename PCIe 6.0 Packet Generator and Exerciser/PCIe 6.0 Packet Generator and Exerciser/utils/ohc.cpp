#include "ohc.h"

boost::dynamic_bitset<> OHCA1::getBitRep() const {
    boost::dynamic_bitset<> result(sizeInBytes * 8);

    for (int i = 0; i < 4; i++) {
        result[i] = firstDWBE[i];
    }
    for (int i = 0; i < 4; i++) {
        result[i + 4] = lastDWBE[i];
    }
    return result;
}

boost::dynamic_bitset<>  OHCA3::getBitRep() const {
    boost::dynamic_bitset<> result(sizeInBytes * 8);
    for (int i = 0; i < 4; i++) {
        result[i] = firstDWBE[i];
    }
    for (int i = 0; i < 4; i++) {
        result[i + 4] = lastDWBE[i];
    }
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), destinationSegment) << 24);
    return result;
}

boost::dynamic_bitset<>  OHCA4::getBitRep() const {
    boost::dynamic_bitset<> result(sizeInBytes * 8);
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), destinationSegment) << 24);
    return result;
}

boost::dynamic_bitset<> OHCA5::getBitRep() const {
    boost::dynamic_bitset<> result(sizeInBytes * 8);
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), static_cast<int>(CPLStatusEnum)));
    for (int i = 0; i < 2; i++) {
        result[i+3] = lowerAddress[i];
    }
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), completerSegment) << 16);
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), destinationSegment) << 24);
    return result;
}

