#include "ohc.h"

boost::dynamic_bitset<> OHCA1::getBitRep() const {
    boost::dynamic_bitset<> result(sizeInBytes * 8);
    //int result1[4] = {0};
    for (int i = 0; i < 4; i++) {
        result[i] = firstDWBE[i];
        //result1[i] = firstDWBE[i];
    }
    //result |= (boost::dynamic_bitset<>((sizeInBytes * 8, result1))) ;
    for (int i = 0; i < 4; i++) {
        result[i + 4] = lastDWBE[i];
        //result1[i] = firstDWBE[i];
    }
    //result |= ((boost::dynamic_bitset<>((sizeInBytes * 8, result1)) << 4);
    return result;
}

 OHC* OHCA1::getObjRep(boost::dynamic_bitset<> bitset) {
	unsigned long Ohc1Values = bitset.to_ulong();
    std::bitset<4> firstDWBEBitset;
    std::bitset<4> lastDWBEBitset;
	boost::dynamic_bitset<> firstDWBE(4, (Ohc1Values & 0xf));

	boost::dynamic_bitset<> lastDWBE(4, (Ohc1Values >> 4) & 0xf);

    for (int i = 0; i < 4; i++) {
        firstDWBEBitset[i] = firstDWBE[i];
        lastDWBEBitset[i] = lastDWBE[i];
    }
	OHC* recievedOHC=new OHCA1(firstDWBEBitset, lastDWBEBitset);

	return recievedOHC;
}

boost::dynamic_bitset<>  OHCA3::getBitRep() const {
    boost::dynamic_bitset<> result(sizeInBytes * 8);
    //int result1[4] = {0};
    for (int i = 0; i < 4; i++) {
        result[i] = firstDWBE[i];
        //result1[i] = firstDWBE[i];
    }
    //result |= (boost::dynamic_bitset<>((sizeInBytes * 8, result1))) ;
    for (int i = 0; i < 4; i++) {
        result[i + 4] = lastDWBE[i];
        //result1[i] = firstDWBE[i];
    }
    //result |= ((boost::dynamic_bitset<>((sizeInBytes * 8, result1)) << 4);
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), destinationSegment) << 24);
    return result;
}

OHC* OHCA3::getObjRep(boost::dynamic_bitset<> bitset) {
    unsigned long Ohc3Values = bitset.to_ulong();

    std::bitset<4> firstDWBEBitset;
    std::bitset<4> lastDWBEBitset;
    boost::dynamic_bitset<> firstDWBE(4, (Ohc3Values & 0xf));

    boost::dynamic_bitset<> lastDWBE(4, (Ohc3Values >> 4) & 0xf);

    for (int i = 0; i < 4; i++) {
        firstDWBEBitset[i] = firstDWBE[i];
        lastDWBEBitset[i] = lastDWBE[i];
    }

    int destinationSegmentValue =( (Ohc3Values >> 24) & 0xff);

    OHC* recievedOHC = new OHCA3(firstDWBEBitset, lastDWBEBitset, destinationSegmentValue);

    return recievedOHC;
}

boost::dynamic_bitset<>  OHCA4::getBitRep() const {
    boost::dynamic_bitset<> result(sizeInBytes * 8);
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), destinationSegment) << 24);
    return result;
}

OHC* OHCA4::getObjRep(boost::dynamic_bitset<> bitset) {
    unsigned long Ohc4Values = bitset.to_ulong();

    int destinationSegmentValue = ((Ohc4Values >> 24) & 0xff);

    OHC* recievedOHC = new OHCA4(destinationSegmentValue);

    return recievedOHC;
}

boost::dynamic_bitset<> OHCA5::getBitRep() const {
    boost::dynamic_bitset<> result(sizeInBytes * 8);
    //int result1[2]={0};
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), static_cast<int>(CPLStatusEnum)));
    for (int i = 0; i < 2; i++) {
        result[i+3] = lowerAddress[i];
        //result1[i]=lowerAddress[i];
    }
    //result |= ((boost::dynamic_bitset<>((sizeInBytes * 8, result1)) << 3);
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), completerSegment) << 16);
    result |= (boost::dynamic_bitset<>((sizeInBytes * 8), destinationSegment) << 24);
    return result;
}

//OHCA5(int destinationSeg, int completerSeg, std::bitset<2> lowerAddresssetter, CPLStatus myEnumsetter) :

OHC* OHCA5::getObjRep(boost::dynamic_bitset<> bitset) {
    unsigned long Ohc5Values = bitset.to_ulong();
    std::bitset<2> lowerAddresssetterBitset;
    int destinationSegmentValue = ((Ohc5Values >> 24) & 0xff);
    int completerSegmentValue = ((Ohc5Values >> 16) & 0xff);
    boost::dynamic_bitset<> lowerAddresssetterValue(2, ((Ohc5Values >> 3 ) & 0x3));
    for (int i = 0; i < 2; i++) {
        lowerAddresssetterBitset[i] = lowerAddresssetterValue[i];
    }
    boost::dynamic_bitset<> CPLStatusValue(3, (Ohc5Values  & 0x7));
    CPLStatus myEnumsetter;
    switch (CPLStatusValue.to_ulong()) {
    case 0b000:
        myEnumsetter = CPLStatus::False;
    case 0b001:
        myEnumsetter = CPLStatus::True;
    }

    OHC* recievedOHC = new OHCA5(destinationSegmentValue, completerSegmentValue, lowerAddresssetterBitset, myEnumsetter);

    return recievedOHC;
}

