#include "TLPHeader.h"


string TLPHeader::getBitRep() const {
    bitset<32> result;
    if (lengthInDoubleWord == 1024)
    {
    }
    else
    {  
        result |= lengthInDoubleWord ;
    }

    result |= (OHC << 16);
    result |= (TC << 21);
    result |= (TLPtype << 24);

    string nonBaseHeader = nonBase->getBitRep();
    string OHCHeader = ;

}