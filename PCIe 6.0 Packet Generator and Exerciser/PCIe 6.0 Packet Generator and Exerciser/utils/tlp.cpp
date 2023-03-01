#include "tlp.h"
int getTotalLength() {
	int OHCLength = TLPHeader::OHCVector.size() * 32;
	int header_length = TLPHeader::nonBase->headerSizeInBytes * 8;
	int payload_length = TLPHeader::lengthInDoubleWord * 32;
	return OHCLength + header_length + payload_length;
}

boost::dynamic_bitset<> TLPHeader::getBitRep() const {
    boost::dynamic_bitset<> result(getTotalLength());

    result |= ((boost::dynamic_bitset<>(getTotalLength() , dataPayload)));
    result |= ((boost::dynamic_bitset<>((TLPHeader::getBitRep() << getTotalLength()))));
    
    return result;

}
