#include "tlp.h"
int TLP::getTotalLength() {
	int OHCLength = header->OHCVector.size()*4;
	int header_length = header->nonBase->headerSizeInBytes;
	int payload_length = header->lengthInDoubleWord * 4;
	return (OHCLength + header_length + payload_length);
}

boost::dynamic_bitset<> TLP::getBitRep() {
    boost::dynamic_bitset<> result(getTotalLength()*8);
    result |=  (dataPayload) ;
    result |= ((boost::dynamic_bitset<>((header->getBitRep())) << getTotalLength() ));
    
    return result;
}
