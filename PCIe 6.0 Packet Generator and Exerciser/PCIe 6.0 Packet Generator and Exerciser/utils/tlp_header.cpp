#include "tlp_header.h"


boost::dynamic_bitset<> TLPHeader::getBitRep() const {
    int OHCLength = OHCVector.size() * 32;
    boost::dynamic_bitset<> result (nonBase->headerSizeInBytes * 8 + OHCLength) ;
    
    result |= ((boost::dynamic_bitset<>((nonBase->headerSizeInBytes * 8, (static_cast<int>(TLPtype)  << ((nonBase->headerSizeInBytes * 8) - 8))))));
    result |= ((boost::dynamic_bitset<>((nonBase->headerSizeInBytes * 8, TC) << (nonBase->headerSizeInBytes * 8) -11)));
    result |= ((boost::dynamic_bitset<>((nonBase->headerSizeInBytes * 8, OHC) << ((nonBase->headerSizeInBytes * 8) - 16))));
    if (lengthInDoubleWord != 1024)
    {
        result |= ((boost::dynamic_bitset<>(nonBase->headerSizeInBytes * 8, lengthInDoubleWord) << ((nonBase->headerSizeInBytes * 8) - 32)));
    }
    boost::dynamic_bitset<> nonBaseHeader = nonBase->getBitRep();
    result |= ((nonBaseHeader) << OHCLength);
    for (int i = 0; i < OHCVector.size(); i++) {
        boost::dynamic_bitset<> OHC_header = OHCVector[i].getBitRep();
        result |= (OHC_header << ( OHCLength - i * 32));
    }
    return result;

}
