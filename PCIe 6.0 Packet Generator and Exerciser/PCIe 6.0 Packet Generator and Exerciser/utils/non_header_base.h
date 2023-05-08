#pragma once
#include <bitset>
#include <string>
#include "boost/dynamic_bitset.hpp"
using namespace std;
// Abstact class
class NonHeaderBase {
public:
	int requestID;
	int headerSizeInBytes;
	virtual boost::dynamic_bitset<> getBitRep() const = 0; // pure virtual function, making this an abstract class
	virtual int getTag() const = 0;
	virtual void setTag(int tag) = 0;
};
// Concrete class AddressRouting32Bit from NonHeaderBase
class AddressRouting32Bit : public	NonHeaderBase {
public:
	int tag;
	int address;
	// Constructor that take tag and address and set them
	AddressRouting32Bit(int requestID, int tg, int adres) {
		this->requestID = requestID;
		tag = tg;
		address = adres;
		headerSizeInBytes = 12;
	}
	boost::dynamic_bitset<> getBitRep() const override;
	static NonHeaderBase* getObjRep(boost::dynamic_bitset<> nonheaderbaseBits);
	int getTag() const override;
	void setTag(int tag) override;
};
// Concrete class AddressRouting64Bit from NonHeaderBase
class AddressRouting64Bit : public	NonHeaderBase {
public:
	int tag;
	long long address;
	
	// Constructor that take tag and address and set them
	AddressRouting64Bit(int requestID, int tg, long long adres) {
		this->requestID = requestID;
		tag = tg;
		address = adres;
		headerSizeInBytes = 16;
	}
	boost::dynamic_bitset<> getBitRep() const override;
	static NonHeaderBase* getObjRep(boost::dynamic_bitset<> nonheaderbaseBits);
	int getTag() const override;
	void setTag(int tag);

};
// Concrete class ConfigNonHeaderBase from NonHeaderBase
class ConfigNonHeaderBase : public	NonHeaderBase {
public:
	int tag;
	int registerNumber;
	int busNumber;
	int deviceNumber;
	int functionNumber;
	// Constructor that take tag, registerNumberint, busNumberint, deviceNumber and functionNumber and set them
	ConfigNonHeaderBase(int requestID, int tg, int register_Number, int bus_Number ,int device_Number,int function_Number ) {
		this->requestID = requestID;
		headerSizeInBytes = 12;
		tag = tg;
		registerNumber = register_Number;
		busNumber = bus_Number;
		deviceNumber = device_Number;
		functionNumber = function_Number;
	}
	boost::dynamic_bitset<> getBitRep() const override;
	static NonHeaderBase* getObjRep(boost::dynamic_bitset<> nonheaderbaseBits);
	int getTag() const override;
	void setTag(int tag);

};
// Concrete class MessageNonHeaderBase from NonHeaderBase
class MessageNonHeaderBase : public	NonHeaderBase {
public:
	int messageCode;
	// Constructor that tage messagecode and set it
	MessageNonHeaderBase(int requestID, int message_Code) {
		this->requestID = requestID;
		headerSizeInBytes = 16;
		messageCode = message_Code;
	}
	boost::dynamic_bitset<> getBitRep() const override;
	static NonHeaderBase* getObjRep(boost::dynamic_bitset<> nonheaderbaseBits);
	int getTag() const override;
	void setTag(int tag);

};
// Concrete class CompletionNonHeaderBase from NonHeaderBase
class CompletionNonHeaderBase : public	NonHeaderBase {
public:
	int tag;
	int completerID;
	long byteCount;
	int busNumber;
	int deviceNumber;
	int functionNumber;
	int lowerAddress;
	// Constructor that take variables and set them
	CompletionNonHeaderBase(int requestID, int tg, int completer_ID,	long byte_Count, int bus_Number, int device_Number ,int function_Number,int lower_Address) {
		this->requestID = requestID;
		headerSizeInBytes = 12;
		tag = tg;
		completerID = completer_ID;
		byteCount = byte_Count;
		busNumber = bus_Number;
		deviceNumber = device_Number;
		functionNumber = function_Number;
		lowerAddress = lower_Address;
	}
	boost::dynamic_bitset<> getBitRep() const override;
	static NonHeaderBase* getObjRep(boost::dynamic_bitset<> nonheaderbaseBits);
	int getTag() const override;
	void setTag(int tag);

};