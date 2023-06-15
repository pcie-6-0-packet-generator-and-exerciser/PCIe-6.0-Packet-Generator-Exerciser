#include "tlp_header.h"


boost::dynamic_bitset<> TLPHeader::getBitRep() const {
    int OHCLength = OHCVector.size() * 32;
    int totalLength = nonBase->headerSizeInBytes * 8 + OHCLength;
    boost::dynamic_bitset<> result (totalLength) ;
    
    result |= (boost::dynamic_bitset<>(totalLength, static_cast<int>(TLPtype))  << (totalLength - 8));
    result |= (boost::dynamic_bitset<>(totalLength, TC) << (totalLength - 11));
    result |= (boost::dynamic_bitset<>(totalLength, OHC) << (totalLength - 16));
    if (lengthInDoubleWord != 1024)
    {
        result |= ((boost::dynamic_bitset<>(totalLength, lengthInDoubleWord) << (totalLength - 32)));
    }
    boost::dynamic_bitset<> nonBaseHeader = nonBase->getBitRep();
    nonBaseHeader.resize(totalLength);
    result |= (nonBaseHeader << OHCLength);
    for (int i = 0; i < OHCVector.size(); i++) {
        boost::dynamic_bitset<> OHC_header = OHCVector[i]->getBitRep();
        OHC_header.resize(totalLength);
        result |= (OHC_header << (OHCLength - 32 - i * 32));
    }
    return result;

}

TLPHeader* TLPHeader::getObjRep(boost::dynamic_bitset<> bitset) {
    int size = bitset.size();
    boost::dynamic_bitset<> TLPType_bitset = get_bits(bitset, size - 8, size - 1);
    TLPHeader* tlpHeader = new TLPHeader();
    int OHCVector = 1;
    switch (TLPType_bitset.to_ulong())
    {
        case 3: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = AddressRouting32Bit::getObjRep(nonHeader_sub_bits);

            tlpHeader->TLPtype = TLPType::MemRead32;

            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA1::getObjRep(OHCVector_sub_bits));
            break;
        }
        case 64: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = AddressRouting32Bit::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::MemWrite32;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA1::getObjRep(OHCVector_sub_bits));
            break; }
        case 32: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 128 - 1);
            tlpHeader->nonBase = AddressRouting64Bit::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::MemRead64;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA1::getObjRep(OHCVector_sub_bits));
            break; }
        case 96: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 128 - 1);
            tlpHeader->nonBase = AddressRouting64Bit::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::MemWrite64;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA1::getObjRep(OHCVector_sub_bits));
            break; }
        case 10: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = CompletionNonHeaderBase::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::Cpl;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA5::getObjRep(OHCVector_sub_bits));
            break; }
        case 74: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = CompletionNonHeaderBase::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::CplD;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA5::getObjRep(OHCVector_sub_bits));
            break; }
        case 4: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = ConfigNonHeaderBase::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::ConfigRead0;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA3::getObjRep(OHCVector_sub_bits));
            break; }
        case 68: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = ConfigNonHeaderBase::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::ConfigWrite0;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA3::getObjRep(OHCVector_sub_bits));
            break; }
        case 5: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = ConfigNonHeaderBase::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::ConfigRead1;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA3::getObjRep(OHCVector_sub_bits));
            break; }
        case 69: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = ConfigNonHeaderBase::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::ConfigWrite1;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA3::getObjRep(OHCVector_sub_bits));
            break; }
        case 75: {
            boost::dynamic_bitset<> nonHeader_sub_bits = get_bits(bitset, OHCVector * 32, (OHCVector * 32) + 96 - 1);
            tlpHeader->nonBase = MessageNonHeaderBase::getObjRep(nonHeader_sub_bits);
            tlpHeader->TLPtype = TLPType::VendorMsg;
            boost::dynamic_bitset<> OHCVector_sub_bits = get_bits(bitset, 0, (OHCVector * 32) - 1);
            tlpHeader->OHCVector.push_back(OHCA4::getObjRep(OHCVector_sub_bits));
        }
    }


    //TC
    boost::dynamic_bitset<> TC_sub_bits = get_bits(bitset, size - 11, size - 9);
    int TCValue = TC_sub_bits.to_ulong();
    tlpHeader->TC = TCValue;
    //OHC
    boost::dynamic_bitset<> OHC_sub_bits = get_bits(bitset, size - 16, size - 12);
    int OHCValue = OHC_sub_bits.to_ulong();
    tlpHeader->OHC = OHCValue;
    //Length
    boost::dynamic_bitset<> length_bitset = get_bits(bitset, size - 32, size - 23);
    int lengthValue = length_bitset.to_ulong();
    if (lengthValue == 0) {
        tlpHeader->lengthInDoubleWord = 1024;
    }
    else {
        tlpHeader->lengthInDoubleWord = lengthValue;
    }
    return tlpHeader;
}
