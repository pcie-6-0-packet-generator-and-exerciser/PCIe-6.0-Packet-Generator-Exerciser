#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/utils/tlp.h"

TEST(TLPGetBitRep, OHCA1firstDWBE) {
	OHCA1* ohc = new OHCA1(std::bitset<4>(), std::bitset<4>());
	for (int i = 0; i < 16; i++) {
		ohc->firstDWBE = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA1lastDWBE) {
	OHCA1* ohc = new OHCA1(std::bitset<4>(), std::bitset<4>());
	for (int i = 0; i < 16; i++) {
		ohc->lastDWBE = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(4));
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA1FullPacket) {
	OHCA1* ohc = new OHCA1(std::bitset<4>(9), std::bitset<4>(7));
	ohc->firstDWBE = 9;
	ohc->lastDWBE = 7;
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	EXPECT_EQ(bitRep.to_ulong(), 0x79);
}

TEST(TLPGetBitRep, OHCA3firstDWBE) {
	OHCA3* ohc = new OHCA3(std::bitset<4>(), std::bitset<4>(), 0);
	for (int i = 0; i < 16; i++) {
		ohc->firstDWBE = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA3lastDWBE) {
	OHCA3* ohc = new OHCA3(std::bitset<4>(), std::bitset<4>(), 0);
	for (int i = 0; i < 16; i++) {
		ohc->lastDWBE = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(4));
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA3destinationSegment) {
	OHCA3* ohc = new OHCA3(std::bitset<4>(), std::bitset<4>(), 0);
	for (int i = 0; i < 256; i++) {
		ohc->destinationSegment = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(24));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA3FullPacket) {
	OHCA3* ohc = new OHCA3(std::bitset<4>(9), std::bitset<4>(7), 186);
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	EXPECT_EQ(bitRep.to_ulong(), 0xBA000079);
}

TEST(TLPGetBitRep, OHCA4destinationSegment) {
	OHCA4* ohc = new OHCA4(0);
	for (int i = 0; i < 256; i++) {
		ohc->destinationSegment = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(24));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA4FullPacket) {
	OHCA4* ohc = new OHCA4(186);
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	EXPECT_EQ(bitRep.to_ulong(), 0xBA000000);
}

TEST(TLPGetBitRep, OHCA5cplStatus) {
	OHCA5* ohc = new OHCA5(0, 0, std::bitset<2>(), OHCA5::CPLStatus::True);
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	bitRep.resize(3);
	EXPECT_EQ(bitRep.to_ulong(), 1);
	ohc->CPLStatusEnum = OHCA5::CPLStatus::False;
	bitRep = ohc->getBitRep();
	bitRep.resize(3);
	EXPECT_EQ(bitRep.to_ulong(), 0);
}

TEST(TLPGetBitRep, OHCA5lowerAddress) {
	OHCA5* ohc = new OHCA5(0, 0, std::bitset<2>(), OHCA5::CPLStatus::True);
	for (int i = 0; i < 4; i++) {
		ohc->lowerAddress = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(3));
		bitRep.resize(2);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA5completerSegment) {
	OHCA5* ohc = new OHCA5(0, 0, std::bitset<2>(), OHCA5::CPLStatus::True);
	for (int i = 0; i < 256; i++) {
		ohc->completerSegment = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(16));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA5destinationSegment) {
	OHCA5* ohc = new OHCA5(0, 0, std::bitset<2>(), OHCA5::CPLStatus::True);
	for (int i = 0; i < 256; i++) {
		ohc->destinationSegment = i;
		boost::dynamic_bitset<> bitRep = ohc->getBitRep();
		bitRep.operator=(bitRep.operator>>(24));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, OHCA5FullPacket) {
	OHCA5* ohc = new OHCA5(91, 249, std::bitset<2>(1), OHCA5::CPLStatus::True);
	boost::dynamic_bitset<> bitRep = ohc->getBitRep();
	EXPECT_EQ(bitRep.to_ulong(), 0x5BF90009);
}

TEST(TLPGetBitRep, NonHeaderAddress32Address) {
	AddressRouting32Bit* nha = new AddressRouting32Bit(0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 30-bit number
		int random = rand() % 1073741824;
		nha->address = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(2));
		bitRep.resize(30);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderAddress32Tag) {
	AddressRouting32Bit* nha = new AddressRouting32Bit(0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 14-bit number
		int random = rand() % 16384;
		nha->tag = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(32));
		bitRep.resize(14);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderAddress32RequesterID) {
	AddressRouting32Bit* nha = new AddressRouting32Bit(0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 16-bit number
		int random = rand() % 65536;
		nha->requestID = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(48));
		bitRep.resize(16);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderAddress32FullPacket) {
	AddressRouting32Bit* nha = new AddressRouting32Bit(48169, 10254, 73741824);
	boost::dynamic_bitset<> bitRep = nha->getBitRep();
	boost::dynamic_bitset<> bitRep2(bitRep.operator>>(32));
	bitRep2.resize(32);
	bitRep.resize(32);
	EXPECT_EQ(bitRep2.to_ulong(), 0xBC29280E);
	EXPECT_EQ(bitRep.to_ulong(), 0x1194D800);
}

TEST(TLPGetBitRep, NonHeaderAddress64Address) {
	AddressRouting64Bit* nha = new AddressRouting64Bit(0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 62-bit number
		long long random = rand() % 4611686018427387904;
		nha->address = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(2));
		bitRep.resize(62);
		long long lower = random & 0x3FFFFFFF;
		long long upper = random >> 30;
		boost::dynamic_bitset<> bitRep2(bitRep);
		bitRep2.resize(30);
		boost::dynamic_bitset<> bitRep3(bitRep.operator>>(30));
		bitRep3.resize(32);
		EXPECT_EQ(bitRep2.to_ulong(), lower);
		EXPECT_EQ(bitRep3.to_ulong(), upper);
	}
}

TEST(TLPGetBitRep, NonHeaderAddress64Tag) {
	AddressRouting64Bit* nha = new AddressRouting64Bit(0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 14-bit number
		int random = rand() % 16384;
		nha->tag = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(64));
		bitRep.resize(14);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderAddress64RequesterID) {
	AddressRouting64Bit* nha = new AddressRouting64Bit(0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 16-bit number
		int random = rand() % 65536;
		nha->requestID = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(80));
		bitRep.resize(16);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderAddress64FullPacket) {
	AddressRouting64Bit* nha = new AddressRouting64Bit(48169, 10254, 4294967297);
	boost::dynamic_bitset<> bitRep = nha->getBitRep();
	boost::dynamic_bitset<> bitRep2(bitRep.operator>>(32));
	boost::dynamic_bitset<> bitRep3(bitRep.operator>>(64));
	bitRep.resize(32);
	bitRep2.resize(32);
	bitRep3.resize(32);
	EXPECT_EQ(bitRep3.to_ulong(), 0xBC29280E);
	EXPECT_EQ(bitRep2.to_ulong(), 0x00000001);
	EXPECT_EQ(bitRep.to_ulong(), 0x00000004);
}

TEST(TLPGetBitRep, NonHeaderConfigRegisterNumber) {
	ConfigNonHeaderBase* nha = new ConfigNonHeaderBase(0, 0, 0, 0, 0, 0);
	for (int i = 0; i <1024; i++) {
		nha->registerNumber = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(2));
		bitRep.resize(10);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, NonHeaderConfigBusNumber) {
	ConfigNonHeaderBase* nha = new ConfigNonHeaderBase(0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 256; i++) {
		nha->busNumber = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(24));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, NonHeaderConfigDeviceNumber) {
	ConfigNonHeaderBase* nha = new ConfigNonHeaderBase(0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 32; i++) {
		nha->deviceNumber = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(19));
		bitRep.resize(5);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, NonHeaderConfigFunctionNumber) {
	ConfigNonHeaderBase* nha = new ConfigNonHeaderBase(0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 8; i++) {
		nha->functionNumber = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(16));
		bitRep.resize(3);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, NonHeaderConfigTag) {
	ConfigNonHeaderBase* nha = new ConfigNonHeaderBase(0, 0, 0, 0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 14-bit number
		int random = rand() % 16384;
		nha->tag = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(32));
		bitRep.resize(14);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderConfigRequesterID) {
	ConfigNonHeaderBase* nha = new ConfigNonHeaderBase(0, 0, 0, 0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 16-bit number
		int random = rand() % 65536;
		nha->requestID = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(48));
		bitRep.resize(16);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderMessageMessageCode) {
	MessageNonHeaderBase* nha = new MessageNonHeaderBase(0, 0);
	for (int i = 0; i < 256; i++) {
		nha->messageCode = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(64));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, NonHeaderMessageRequesterID) {
	MessageNonHeaderBase* nha = new MessageNonHeaderBase(0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 16-bit number
		int random = rand() % 65536;
		nha->requestID = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(80));
		bitRep.resize(16);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderCompletionByteCount) {
	CompletionNonHeaderBase* nha = new CompletionNonHeaderBase(0, 0, 0, 0, 0, 0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 12-bit number
		long random = rand() % 4096;
		nha->byteCount = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.resize(12);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderCompletionLowerAddress) {
	CompletionNonHeaderBase* nha = new CompletionNonHeaderBase(0, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 32; i++) {
		nha->lowerAddress = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		EXPECT_EQ(bitRep[46], i >> 4);
		bitRep.operator=(bitRep.operator>>(12));
		bitRep.resize(4);
		EXPECT_EQ(bitRep.to_ulong(), i & 0xF);
	}
}

TEST(TLPGetBitRep, NonHeaderCompletionBusNumber) {
	CompletionNonHeaderBase* nha = new CompletionNonHeaderBase(0, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 256; i++) {
		nha->busNumber = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(24));
		bitRep.resize(8);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, NonHeaderCompletionDeviceNumber) {
	CompletionNonHeaderBase* nha = new CompletionNonHeaderBase(0, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 32; i++) {
		nha->deviceNumber = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(19));
		bitRep.resize(5);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, NonHeaderCompletionFunctionNumber) {
	CompletionNonHeaderBase* nha = new CompletionNonHeaderBase(0, 0, 0, 0, 0, 0, 0, 0);
	for (int i = 0; i < 8; i++) {
		nha->functionNumber = i;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(16));
		bitRep.resize(3);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, NonHeaderCompletionTag) {
	CompletionNonHeaderBase* nha = new CompletionNonHeaderBase(0, 0, 0, 0, 0, 0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 14-bit number
		int random = rand() % 16384;
		nha->tag = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(32));
		bitRep.resize(14);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, NonHeaderCompletionCompleterID) {
	CompletionNonHeaderBase* nha = new CompletionNonHeaderBase(0, 0, 0, 0, 0, 0, 0, 0);
	srand(1);
	for (int i = 0; i < 256; i++) {
		// generate random 16-bit number
		int random = rand() % 65536;
		nha->completerID = random;
		boost::dynamic_bitset<> bitRep = nha->getBitRep();
		bitRep.operator=(bitRep.operator>>(48));
		bitRep.resize(16);
		EXPECT_EQ(bitRep.to_ulong(), random);
	}
}

TEST(TLPGetBitRep, HeaderTC) {
	TLPHeader* h = new TLPHeader();
	for (int i = 0; i < 8; i++) {
		h->TC = i;
		h->nonBase = new AddressRouting32Bit(0, 0, 0);
		boost::dynamic_bitset<> bitRep = h->getBitRep();
		bitRep.operator=(bitRep.operator>>(21 + 64));
		bitRep.resize(3);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, HeaderOHC) {
	TLPHeader* h = new TLPHeader();
	for (int i = 0; i < 32; i++) {
		h->OHC = i;
		h->nonBase = new AddressRouting32Bit(0, 0, 0);
		boost::dynamic_bitset<> bitRep = h->getBitRep();
		bitRep.operator=(bitRep.operator>>(16 + 64));
		bitRep.resize(5);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
}

TEST(TLPGetBitRep, HeaderLength) {
	TLPHeader* h = new TLPHeader();
	for (int i = 1; i < 1024; i++) {
		h->lengthInDoubleWord = i;
		h->nonBase = new AddressRouting32Bit(0, 0, 0);
		boost::dynamic_bitset<> bitRep = h->getBitRep();
		bitRep.operator=(bitRep.operator>>(64));
		bitRep.resize(10);
		EXPECT_EQ(bitRep.to_ulong(), i);
	}
	h->lengthInDoubleWord = 1024;
	boost::dynamic_bitset<> bitRep = h->getBitRep();
	bitRep.operator=(bitRep.operator>>(64));
	bitRep.resize(10);
	EXPECT_EQ(bitRep.to_ulong(), 0);
}

TEST(TLPGetBitRep, HeaderType) {
	TLPHeader* h = new TLPHeader();
	h->TLPtype = TLPType::MemRead32;
	h->nonBase = new AddressRouting32Bit(0, 0, 0);
	boost::dynamic_bitset<> bitRep = h->getBitRep();
	bitRep.operator=(bitRep.operator>>(24 + 64));
	bitRep.resize(8);
	EXPECT_EQ(bitRep.to_ulong(), static_cast<int>(TLPType::MemRead32));
}

TEST(TLPGetBitRep, HeaderFullPacketNoOHC) {
	TLPHeader* h = new TLPHeader();
	h->TLPtype = TLPType::MemWrite64;
	h->lengthInDoubleWord = 781;
	h->OHC = 26;
	h->TC = 0;
	h->nonBase = new AddressRouting64Bit(48169, 10254, 4294967297);
	boost::dynamic_bitset<> bitRep = h->getBitRep();
	boost::dynamic_bitset<> bitRep2(bitRep.operator>>(32));
	boost::dynamic_bitset<> bitRep3(bitRep.operator>>(64));
	boost::dynamic_bitset<> bitRep4(bitRep.operator>>(96));
	bitRep.resize(32);
	bitRep2.resize(32);
	bitRep3.resize(32);
	bitRep4.resize(32);
	EXPECT_EQ(bitRep4.to_ulong(), 0x601A030D);
	EXPECT_EQ(bitRep3.to_ulong(), 0xBC29280E);
	EXPECT_EQ(bitRep2.to_ulong(), 0x00000001);
	EXPECT_EQ(bitRep.to_ulong(), 0x00000004);
}

TEST(TLPGetBitRep, HeaderFullPacketWithOHC) {
	TLPHeader* h = new TLPHeader();
	h->TLPtype = TLPType::MemWrite64;
	h->lengthInDoubleWord = 781;
	h->OHC = 26;
	h->TC = 0;
	h->nonBase = new AddressRouting64Bit(48169, 10254, 4294967297);
	OHCA3* ohc = new OHCA3(std::bitset<4>(9), std::bitset<4>(7), 186);
	h->OHCVector.push_back(ohc);
	boost::dynamic_bitset<> bitRep = h->getBitRep();
	boost::dynamic_bitset<> bitRep2(bitRep.operator>>(32));
	boost::dynamic_bitset<> bitRep3(bitRep.operator>>(64));
	boost::dynamic_bitset<> bitRep4(bitRep.operator>>(96));
	boost::dynamic_bitset<> bitRep5(bitRep.operator>>(128));
	bitRep.resize(32);
	bitRep2.resize(32);
	bitRep3.resize(32);
	bitRep4.resize(32);
	bitRep5.resize(32);
	EXPECT_EQ(bitRep5.to_ulong(), 0x601A030D);
	EXPECT_EQ(bitRep4.to_ulong(), 0xBC29280E);
	EXPECT_EQ(bitRep3.to_ulong(), 0x00000001);
	EXPECT_EQ(bitRep2.to_ulong(), 0x00000004);
	EXPECT_EQ(bitRep.to_ulong(), 0xBA000079);
}

TEST(TLPGetBitRep, TLPFullPacketNoDatapayload) {
	TLP* tlp = new TLP();
	TLPHeader* h = new TLPHeader();
	h->TLPtype = TLPType::MemRead64;
	h->lengthInDoubleWord = 0;
	h->OHC = 26;
	h->TC = 0;
	OHCA3* ohc = new OHCA3(std::bitset<4>(9), std::bitset<4>(7), 186);
	h->OHCVector.push_back(ohc);
	h->nonBase = new AddressRouting64Bit(48169, 10254, 4294967297);
	tlp->header = h;
	boost::dynamic_bitset<> bitRep = tlp->getBitRep();
	boost::dynamic_bitset<> bitRep2(bitRep.operator>>(32));
	boost::dynamic_bitset<> bitRep3(bitRep.operator>>(64));
	boost::dynamic_bitset<> bitRep4(bitRep.operator>>(96));
	boost::dynamic_bitset<> bitRep5(bitRep.operator>>(128));
	bitRep.resize(32);
	bitRep2.resize(32);
	bitRep3.resize(32);
	bitRep4.resize(32);
	EXPECT_EQ(bitRep5.to_ulong(), 0x201A0000);
	EXPECT_EQ(bitRep4.to_ulong(), 0xBC29280E);
	EXPECT_EQ(bitRep3.to_ulong(), 0x00000001);
	EXPECT_EQ(bitRep2.to_ulong(), 0x00000004);
	EXPECT_EQ(bitRep.to_ulong(), 0xBA000079);
}

TEST(TLPGetBitRep, TLPFullPacketWithDatapayload) {
	TLP* tlp = new TLP();
	TLPHeader* h = new TLPHeader();
	h->TLPtype = TLPType::MemWrite64;
	h->lengthInDoubleWord = 2;
	h->OHC = 26;
	h->TC = 0;
	OHCA3* ohc = new OHCA3(std::bitset<4>(9), std::bitset<4>(7), 186);
	h->OHCVector.push_back(ohc);
	h->nonBase = new AddressRouting64Bit(48169, 10254, 4294967297);
	tlp->header = h;
	tlp->dataPayload = boost::dynamic_bitset<>(64, 0x00000001);
	tlp->dataPayload.operator|=(boost::dynamic_bitset<>(64, 0x00000001) << 32);
	boost::dynamic_bitset<> bitRep = tlp->getBitRep();
	boost::dynamic_bitset<> bitRep2(bitRep.operator>>(32));
	boost::dynamic_bitset<> bitRep3(bitRep.operator>>(64));
	boost::dynamic_bitset<> bitRep4(bitRep.operator>>(96));
	boost::dynamic_bitset<> bitRep5(bitRep.operator>>(128));
	boost::dynamic_bitset<> bitRep6(bitRep.operator>>(160));
	boost::dynamic_bitset<> bitRep7(bitRep.operator>>(192));
	bitRep.resize(32);
	bitRep2.resize(32);
	bitRep3.resize(32);
	bitRep4.resize(32);
	bitRep5.resize(32);
	bitRep6.resize(32);
	EXPECT_EQ(bitRep7.to_ulong(), 0x601A0002);
	EXPECT_EQ(bitRep6.to_ulong(), 0xBC29280E);
	EXPECT_EQ(bitRep5.to_ulong(), 0x00000001);
	EXPECT_EQ(bitRep4.to_ulong(), 0x00000004);
	EXPECT_EQ(bitRep3.to_ulong(), 0xBA000079);
	EXPECT_EQ(bitRep2.to_ulong(), 0x00000001);
	EXPECT_EQ(bitRep.to_ulong(), 0x00000001);
}

void setBits(boost::dynamic_bitset<>& bitset, int start, int end, int value) {
	for (int i = start; i <= end; i++) {
		bitset[i] = value & 1;
		value = value >> 1;
	}
}

TEST(TLPGetObjRep, OHCA1) {
	boost::dynamic_bitset<> ohcbits = boost::dynamic_bitset<>(32);
	setBits(ohcbits, 0, 3, 12);
	setBits(ohcbits, 4, 7, 5);
	OHCA1* ohc = (OHCA1*)OHCA1::getObjRep(ohcbits);
	EXPECT_EQ(ohc->firstDWBE.to_ulong(), 12);
	EXPECT_EQ(ohc->lastDWBE.to_ulong(), 5);
}

TEST(TLPGetObjRep, OHCA3) {
	boost::dynamic_bitset<> ohcbits = boost::dynamic_bitset<>(32);
	setBits(ohcbits, 0, 3, 12);
	setBits(ohcbits, 4, 7, 5);
	setBits(ohcbits, 24, 31, 158);
	OHCA3* ohc = (OHCA3*)OHCA3::getObjRep(ohcbits);
	EXPECT_EQ(ohc->firstDWBE.to_ulong(), 12);
	EXPECT_EQ(ohc->lastDWBE.to_ulong(), 5);
	EXPECT_EQ(ohc->destinationSegment, 158);
}

TEST(TLPGetObjRep, OHCA4) {
	boost::dynamic_bitset<> ohcbits = boost::dynamic_bitset<>(32);
	setBits(ohcbits, 24, 31, 255);
	OHCA4* ohc = (OHCA4*)OHCA4::getObjRep(ohcbits);
	EXPECT_EQ(ohc->destinationSegment, 255);
}

TEST(TLPGetObjRep, OHCA5) {
	boost::dynamic_bitset<> ohcbits = boost::dynamic_bitset<>(32);
	setBits(ohcbits, 0, 2, 1);
	setBits(ohcbits, 3, 4, 2);
	setBits(ohcbits, 16, 23, 72);
	setBits(ohcbits, 24, 31, 126);
	OHCA5* ohc = (OHCA5*)OHCA5::getObjRep(ohcbits);
	EXPECT_EQ(ohc->CPLStatusEnum, OHCA5::CPLStatus::True);
	EXPECT_EQ(ohc->lowerAddress, 2);
	EXPECT_EQ(ohc->completerSegment, 72);
	EXPECT_EQ(ohc->destinationSegment, 126);
}
