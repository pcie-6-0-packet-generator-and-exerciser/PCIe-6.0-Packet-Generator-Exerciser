#include "non_header_base.h"

boost::dynamic_bitset<> get_bits(const boost::dynamic_bitset<>& bits, size_t start_index, size_t end_index) {
    size_t length = end_index - start_index + 1;
    boost::dynamic_bitset<> result(length);
    for (size_t i = 0; i < length; ++i) {
        result[i] = bits[start_index + i];
    }
    return result;
}


boost::dynamic_bitset<> AddressRouting32Bit::getBitRep() const {
    boost::dynamic_bitset<> result ((headerSizeInBytes * 8) - 32) ;
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, address));
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, tag) << 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, requestID) << 48);
    return result;
}

NonHeaderBase* AddressRouting32Bit::getObjRep(boost::dynamic_bitset<> bitset)const {
    boost::dynamic_bitset<> addressValue_sub_bits = get_bits(bitset,0,15);
    int addressValue = addressValue_sub_bits.to_ulong();

    //int tagValue = ((AddressRouting32BitValues >> 32) & 0x3fff);
    boost::dynamic_bitset<> tagValue_sub_bits = get_bits(bitset, 32, 45);
    int tagValue = tagValue_sub_bits.to_ulong();

    //int requestID((AddressRouting32BitValues >> 48) & 0xffff);
    boost::dynamic_bitset<> requestID_sub_bits = get_bits(bitset, 48, 63);
    int requestID = requestID_sub_bits.to_ulong();

    NonHeaderBase* recievedAddressRouting32Bit = new AddressRouting32Bit(requestID, tagValue, addressValue);
    return recievedAddressRouting32Bit;
}

boost::dynamic_bitset<> AddressRouting64Bit::getBitRep() const {
    boost::dynamic_bitset<> result ((headerSizeInBytes * 8) - 32) ;
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, address));
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, tag) << 64);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, requestID) << 80);
    return result;
}

NonHeaderBase* AddressRouting64Bit::getObjRep(boost::dynamic_bitset<> bitset)const {
    unsigned long AddressRouting64BitValues = bitset.to_ulong();

    int addressValue = (AddressRouting64BitValues & 0xffffffffffffffff);
    int tagValue = ((AddressRouting64BitValues >> 64) & 0x3fff);
    int requestIDValue((AddressRouting64BitValues >> 80) & 0xffff);
    //	AddressRouting64Bit(int requestID, int tg, long long adres) {

    NonHeaderBase* recievedAddressRouting64Bit = new AddressRouting64Bit(requestIDValue, tagValue, addressValue);
    return recievedAddressRouting64Bit;
}

boost::dynamic_bitset<> MessageNonHeaderBase::getBitRep() const {
    boost::dynamic_bitset<> result((headerSizeInBytes * 8) - 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, messageCode) << 64);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, requestID) << 80);
    return result;
}

NonHeaderBase* MessageNonHeaderBase::getObjRep(boost::dynamic_bitset<> bitset)const {
    unsigned long MessageNonHeaderBaseValue = bitset.to_ulong();

    int messageCodeValue = ((MessageNonHeaderBaseValue >> 64) & 0xff);
    int requestIDValue((MessageNonHeaderBaseValue >> 80) & 0xffff);
//	MessageNonHeaderBase(int requestID, int message_Code) {

    NonHeaderBase* recievedMessageNonHeaderBase = new MessageNonHeaderBase(requestIDValue, messageCodeValue);
    return recievedMessageNonHeaderBase;
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

NonHeaderBase* ConfigNonHeaderBase::getObjRep(boost::dynamic_bitset<> bitset)const {
    unsigned long ConfigNonHeaderBaseValue = bitset.to_ulong();

    int registerNumberValue = ((ConfigNonHeaderBaseValue >> 2) & 0x3ff);
    int functionNumberValue = ((ConfigNonHeaderBaseValue >> 16) & 0x07);
    int deviceNumberValue = ((ConfigNonHeaderBaseValue >> 19) & 0x1f);
    int busNumberValue = ((ConfigNonHeaderBaseValue >> 24) & 0xff);
    int tagValue = ((ConfigNonHeaderBaseValue >> 32) & 0x3fff);
    int requestIDValue = ((ConfigNonHeaderBaseValue >> 48) & 0xffff);


//	ConfigNonHeaderBase(int requestID, int tg, int register_Number, int bus_Number ,int device_Number,int function_Number ) {

    NonHeaderBase* recievedConfigNonHeaderBase = new ConfigNonHeaderBase(requestIDValue, tagValue, registerNumberValue, busNumberValue, deviceNumberValue, functionNumberValue);
    return recievedConfigNonHeaderBase;
}

boost::dynamic_bitset<> CompletionNonHeaderBase::getBitRep() const {
    boost::dynamic_bitset<> result((headerSizeInBytes * 8) - 32);

    std::bitset<6> myBitset(lowerAddress);  // convert integer to bitset
    std::bitset<1> lastBit;  // bitset to hold last 1 bits

    lastBit[0] = myBitset[5];
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, byteCount));
    //Add the lowerAddress
    int y = 2;
    for (int i = 0; i < 4; i++) {
        result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, myBitset[y] << (12 + i)));
        y++;
    }
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, functionNumber) << 16);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, deviceNumber) << 19);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, busNumber) << 24);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, tag) << 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, lastBit[0]) << 46);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, completerID) << 48);

    return result;
}

NonHeaderBase* CompletionNonHeaderBase::getObjRep(boost::dynamic_bitset<> bitset)const {
    boost::dynamic_bitset<> CompletionNonHeaderBaseValue = bitset;
    long byteCountValue = (CompletionNonHeaderBaseValue.resize(12)); 
    int registerNumberValue = ((CompletionNonHeaderBaseValue >> 2) & 0x3ff);
    int functionNumberValue = ((CompletionNonHeaderBaseValue >> 16) & 0x07);
    int deviceNumberValue = ((CompletionNonHeaderBaseValue >> 19) & 0x1f);
    int busNumberValue = ((CompletionNonHeaderBaseValue >> 24) & 0xff);
    int tagValue = ((CompletionNonHeaderBaseValue >> 32) & 0x3fff);
    int completerIDValue = ((CompletionNonHeaderBaseValue >> 48) & 0xffff);
    std::bitset<6> lowerAddressValuesbits;
    lowerAddressValuesbits[2]= ((CompletionNonHeaderBaseValue >> 12) & 0x1);
    lowerAddressValuesbits[3] = ((CompletionNonHeaderBaseValue >> 13) & 0x1);
    lowerAddressValuesbits[4] = ((CompletionNonHeaderBaseValue >> 14) & 0x1);
    lowerAddressValuesbits[5] = ((CompletionNonHeaderBaseValue >> 15) & 0x1);
    lowerAddressValuesbits[6] = ((CompletionNonHeaderBaseValue >> 46) & 0x1);
    int lowerAddressValues = lowerAddressValuesbits.to_ulong();

//	CompletionNonHeaderBase(int requestID, int tg, int completer_ID,long byte_Count, int bus_Number, int device_Number ,int function_Number,int lower_Address) {

    NonHeaderBase* recievedCompletionNonHeaderBase = new CompletionNonHeaderBase(0, tagValue, completerIDValue, byteCountValue, busNumberValue, deviceNumberValue, functionNumberValue, lowerAddressValues);
    return recievedCompletionNonHeaderBase;
}