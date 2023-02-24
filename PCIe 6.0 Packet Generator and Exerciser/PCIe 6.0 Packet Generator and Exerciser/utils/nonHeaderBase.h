#pragma once
// Abstact class
class NonHeaderBase {
public:
	int requestID;
};
// Concrete class AddressRouting32Bit from NonHeaderBase
class AddressRouting32Bit : public	NonHeaderBase {
public:
	int tag;
	int address;
	int size = 12;
	// Constructor that take tag and address and set them
	AddressRouting32Bit(int tag_, int address_) {
		tag = tag_;
		address = address_;
	}
};
// Concrete class AddressRouting64Bit from NonHeaderBase
class AddressRouting64Bit : public	NonHeaderBase {
public:
	int tag;
	long long address;
	int size = 16;
	// Constructor that take tag and address and set them
	AddressRouting64Bit(int tag_, long long address_) {
		tag = tag_;
		address = address_;
	}
};
// Concrete class ConfigNonHeaderBase from NonHeaderBase
class ConfigNonHeaderBase : public	NonHeaderBase {
public:
	int tag;
	int registerNumber;
	int busNumber;
	int deviceNumber;
	int functionNumber;
	int size = 12;
	// Constructor that take tag, registerNumberint, busNumberint, deviceNumber and functionNumber and set them
	ConfigNonHeaderBase(int tag_, int registerNumber_, int busNumber_ ,int deviceNumber_,int functionNumber_ ) {
		tag = tag_;
		registerNumber = registerNumber_;
		busNumber = busNumber_;
		deviceNumber = deviceNumber_;
		functionNumber = functionNumber_;
	}
};
// Concrete class MessageNonHeaderBase from NonHeaderBase
class MessageNonHeaderBase : public	NonHeaderBase {
public:
	int messageCode;
	int size = 16;
	// Constructor that tage messagecode and set it
	MessageNonHeaderBase(int messageCode_) {
		messageCode = messageCode_;
	}
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
	int size = 12;
	// Constructor that take variables and set them
	CompletionNonHeaderBase(int tag_, int completerID_,	long byteCount_, int busNumber_, int deviceNumber_ ,int functionNumber_,int lowerAddress_) {
		tag = tag_;
		completerID = completerID_;
		byteCount = byteCount_;
		busNumber = busNumber_;
		deviceNumber = deviceNumber_;
		functionNumber = functionNumber_;
		lowerAddress = lowerAddress_;
	}
};