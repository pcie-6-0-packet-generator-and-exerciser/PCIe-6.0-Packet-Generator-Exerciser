#include "non_header_base.h"
#include "bitset_utils.h"



boost::dynamic_bitset<> AddressRouting32Bit::getBitRep() const {
    boost::dynamic_bitset<> result ((headerSizeInBytes * 8) - 32) ;
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, address));
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, tag) << 32);
    result |= (boost::dynamic_bitset<>((headerSizeInBytes * 8) - 32, requestID) << 48);
    return result;
}

NonHeaderBase* AddressRouting32Bit::getObjRep(boost::dynamic_bitset<> bitset){
    boost::dynamic_bitset<> addressValue_sub_bits = get_bits(bitset,2,31);
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

NonHeaderBase* AddressRouting64Bit::getObjRep(boost::dynamic_bitset<> bitset) {
    boost::dynamic_bitset<> addressValue_sub_bits = get_bits(bitset, 2, 63);
    int addressValue = addressValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> tagValue_sub_bits = get_bits(bitset, 64, 77);
    int tagValue = tagValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> requestIDValue_sub_bits = get_bits(bitset, 80, 95);
    int requestIDValue = requestIDValue_sub_bits.to_ulong();

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

NonHeaderBase* MessageNonHeaderBase::getObjRep(boost::dynamic_bitset<> bitset) {
    boost::dynamic_bitset<> messageCodeValue_sub_bits = get_bits(bitset, 64, 71);
    int messageCodeValue = messageCodeValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> requestIDValue_sub_bits = get_bits(bitset, 80, 95);
    int requestIDValue = requestIDValue_sub_bits.to_ulong();

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

NonHeaderBase* ConfigNonHeaderBase::getObjRep(boost::dynamic_bitset<> bitset) {
    
    boost::dynamic_bitset<> registerNumberValue_sub_bits = get_bits(bitset, 2, 11);
    int registerNumberValue = registerNumberValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> functionNumberValue_sub_bits = get_bits(bitset, 16, 18);
    int functionNumberValue = functionNumberValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> deviceNumberValue_sub_bits = get_bits(bitset, 19, 23);
    int deviceNumberValue = deviceNumberValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> busNumberValue_sub_bits = get_bits(bitset, 24, 31);
    int busNumberValue = busNumberValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> tagValue_sub_bits = get_bits(bitset, 32, 45);
    int tagValue = tagValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> requestIDValue_sub_bits = get_bits(bitset, 48, 63);
    int requestIDValue = requestIDValue_sub_bits.to_ulong();

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

NonHeaderBase* CompletionNonHeaderBase::getObjRep(boost::dynamic_bitset<> bitset) {
    boost::dynamic_bitset<> byteCountValue_sub_bits = get_bits(bitset, 0, 11);
    long byteCountValue = byteCountValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> functionNumberValue_sub_bits = get_bits(bitset, 16, 18);
    int functionNumberValue = functionNumberValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> deviceNumberValue_sub_bits = get_bits(bitset, 19, 23);
    int deviceNumberValue = deviceNumberValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> busNumberValue_sub_bits = get_bits(bitset, 24, 31);
    int busNumberValue = busNumberValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> tagValue_sub_bits = get_bits(bitset, 32, 45);
    int tagValue = tagValue_sub_bits.to_ulong();

    boost::dynamic_bitset<> completerIDValue_sub_bits = get_bits(bitset, 48, 63);
    int completerIDValue = completerIDValue_sub_bits.to_ulong();

    std::bitset<6> lowerAddressValuesbits;
    lowerAddressValuesbits[2] = bitset[12];
    lowerAddressValuesbits[3] = bitset[13];
    lowerAddressValuesbits[4] = bitset[14];
    lowerAddressValuesbits[5] = bitset[15];
    lowerAddressValuesbits[6] = bitset[46];
    int lowerAddressValues = lowerAddressValuesbits.to_ulong();

//	CompletionNonHeaderBase(int requestID, int tg, int completer_ID,long byte_Count, int bus_Number, int device_Number ,int function_Number,int lower_Address) {

    NonHeaderBase* recievedCompletionNonHeaderBase = new CompletionNonHeaderBase(0, tagValue, completerIDValue, byteCountValue, busNumberValue, deviceNumberValue, functionNumberValue, lowerAddressValues);
    return recievedCompletionNonHeaderBase;
}