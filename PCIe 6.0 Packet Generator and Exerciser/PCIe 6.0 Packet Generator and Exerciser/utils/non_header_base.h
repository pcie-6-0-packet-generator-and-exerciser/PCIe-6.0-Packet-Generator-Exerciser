#pragma once
#include <bitset>
#include <string>
using namespace std;
// Abstact class
class NonHeaderBase {
public:
	int requestID;
	int headerSizeInBytes;
	virtual string getBitRep() const = 0; // pure virtual function, making this an abstract class

};
// Concrete class AddressRouting32Bit from NonHeaderBase
class AddressRouting32Bit : public	NonHeaderBase {
public:
	int tag;
	int address;
	// Constructor that take tag and address and set them
	AddressRouting32Bit(int tag_, int address_) {
		tag = tag_;
		address = address_;
		headerSizeInBytes = 12;
	}
	string getBitRep() const override;
};
// Concrete class AddressRouting64Bit from NonHeaderBase
class AddressRouting64Bit : public	NonHeaderBase {
public:
	int tag;
	long long address;
	
	// Constructor that take tag and address and set them
	AddressRouting64Bit(int tag_, long long address_) {
		tag = tag_;
		address = address_;
		headerSizeInBytes = 16;
	}
	string getBitRep() const override;

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
	ConfigNonHeaderBase(int tag_, int registerNumber_, int busNumber_ ,int deviceNumber_,int functionNumber_ ) {
		headerSizeInBytes = 12;
		tag = tag_;
		registerNumber = registerNumber_;
		busNumber = busNumber_;
		deviceNumber = deviceNumber_;
		functionNumber = functionNumber_;
	}
	string getBitRep() const override;

};
// Concrete class MessageNonHeaderBase from NonHeaderBase
class MessageNonHeaderBase : public	NonHeaderBase {
public:
	int messageCode;
	// Constructor that tage messagecode and set it
	MessageNonHeaderBase(int messageCode_) {
		headerSizeInBytes = 16;
		messageCode = messageCode_;
	}
	string getBitRep() const override;

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
	CompletionNonHeaderBase(int tag_, int completerID_,	long byteCount_, int busNumber_, int deviceNumber_ ,int functionNumber_,int lowerAddress_) {
		headerSizeInBytes = 12;
		tag = tag_;
		completerID = completerID_;
		byteCount = byteCount_;
		busNumber = busNumber_;
		deviceNumber = deviceNumber_;
		functionNumber = functionNumber_;
		lowerAddress = lowerAddress_;
	}
	string getBitRep() const override;

};