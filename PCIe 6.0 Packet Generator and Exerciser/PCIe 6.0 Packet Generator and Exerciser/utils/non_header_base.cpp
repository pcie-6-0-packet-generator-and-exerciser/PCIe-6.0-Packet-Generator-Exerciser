#include "non_header_base.h"

boost::dynamic_bitset<> AddressRouting32Bit::getBitRep() const {
    boost::dynamic_bitset<> result ((headerSizeInBytes * 8) - 32) ;
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, address));
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, tag) << 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, requestID) << 48);
    return result;
}

boost::dynamic_bitset<> AddressRouting64Bit::getBitRep() const {
    boost::dynamic_bitset<> result ((headerSizeInBytes * 8) - 32) ;
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, address));
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, tag) << 64);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, requestID) << 80);
    return result;
}

boost::dynamic_bitset<> MessageNonHeaderBase::getBitRep() const {
    boost::dynamic_bitset<> result((headerSizeInBytes * 8) - 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, messageCode) << 64);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, requestID) << 80);
    return result;
}

boost::dynamic_bitset<> ConfigNonHeaderBase::getBitRep() const {
    boost::dynamic_bitset<> result((headerSizeInBytes * 8) - 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, registerNumber) << 2);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, functionNumber) << 16);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, deviceNumber) << 19);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, busNumber) << 24);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, tag) << 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, requestID) << 48);
    return result;
}
boost::dynamic_bitset<> CompletionNonHeaderBase::getBitRep() const {
    boost::dynamic_bitset<> result((headerSizeInBytes * 8) - 32);

    std::bitset<6> myBitset(lowerAddress);  // convert integer to bitset
    std::bitset<1> lastBit;  // bitset to hold last 1 bits

    lastBit[0] = myBitset[5];
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, byteCount));
    //Add the lowerAddress
    for (int i = 0; i < 5; i++) {
        result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, myBitset[i] << (12 + i)));
    }
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, functionNumber) << 16);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, deviceNumber) << 19);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, busNumber) << 24);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, tag) << 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, lastBit[0]) << 46);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, completerID) << 48);

    return result;
}