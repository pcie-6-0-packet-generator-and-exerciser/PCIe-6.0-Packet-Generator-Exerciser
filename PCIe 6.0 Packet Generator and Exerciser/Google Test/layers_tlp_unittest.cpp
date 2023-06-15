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

void setBits(boost::dynamic_bitset<>& bitset, int start, int end, long long value) {
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

TEST(TLPGetObjRep, NonHeaderAddressRouting32) {
	boost::dynamic_bitset<> nhbits = boost::dynamic_bitset<>(64);
	setBits(nhbits, 2, 31, 0x3465123F);
	setBits(nhbits, 32, 45, 15023);
	setBits(nhbits, 48, 63, 0xA6B9);
	AddressRouting32Bit* nh = (AddressRouting32Bit*)AddressRouting32Bit::getObjRep(nhbits);
	EXPECT_EQ(nh->address, 0x3465123F);
	EXPECT_EQ(nh->tag, 15023);
	EXPECT_EQ(nh->requestID, 0xA6B9);
}

TEST(TLPGetObjRep, NonHeaderAddressRouting64) {
	boost::dynamic_bitset<> nhbits = boost::dynamic_bitset<>(96);
	setBits(nhbits, 2, 63, 0x34651230A6B953F);
	setBits(nhbits, 64, 77, 14906);
	setBits(nhbits, 80, 95, 0x9FAB);
	AddressRouting64Bit* nh = (AddressRouting64Bit*)AddressRouting64Bit::getObjRep(nhbits);
	EXPECT_EQ(nh->address, 0x34651230A6B953F);
	EXPECT_EQ(nh->tag, 14906);
	EXPECT_EQ(nh->requestID, 0x9FAB);
}

TEST(TLPGetObjRep, NonHeaderConfig) {
	boost::dynamic_bitset<> nhbits = boost::dynamic_bitset<>(64);
	setBits(nhbits, 2, 11, 0x3B2);
	setBits(nhbits, 16, 18, 5);
	setBits(nhbits, 19, 23, 26);
	setBits(nhbits, 24, 31, 0xFF);
	setBits(nhbits, 32, 45, 15023);
	setBits(nhbits, 48, 63, 0xA6B9);
	ConfigNonHeaderBase* nh = (ConfigNonHeaderBase*)ConfigNonHeaderBase::getObjRep(nhbits);
	EXPECT_EQ(nh->registerNumber, 0x3B2);
	EXPECT_EQ(nh->functionNumber, 5);
	EXPECT_EQ(nh->deviceNumber, 26);
	EXPECT_EQ(nh->busNumber, 0xFF);
	EXPECT_EQ(nh->tag, 15023);
	EXPECT_EQ(nh->requestID, 0xA6B9);
}

TEST(TLPGetObjRep, NonHeaderMessage) {
	boost::dynamic_bitset<> nhbits = boost::dynamic_bitset<>(96);
	setBits(nhbits, 64, 71, 0xB3);
	setBits(nhbits, 80, 95, 0x9FAB);
	MessageNonHeaderBase* nh = (MessageNonHeaderBase*)MessageNonHeaderBase::getObjRep(nhbits);
	EXPECT_EQ(nh->messageCode, 0xB3);
	EXPECT_EQ(nh->requestID, 0x9FAB);
}

TEST(TLPGetObjRep, NonHeaderCompletion) {
	boost::dynamic_bitset<> nhbits = boost::dynamic_bitset<>(64);
	setBits(nhbits, 0, 11, 0x3B2);
	setBits(nhbits, 12, 15, 6);
	setBits(nhbits, 16, 18, 5);
	setBits(nhbits, 19, 23, 26);
	setBits(nhbits, 24, 31, 0xFF);
	setBits(nhbits, 32, 45, 15023);
	nhbits[46] = true;
	setBits(nhbits, 48, 63, 0xAB);
	CompletionNonHeaderBase* nh = (CompletionNonHeaderBase*)CompletionNonHeaderBase::getObjRep(nhbits);
	EXPECT_EQ(nh->byteCount, 0x3B2);
	EXPECT_EQ(nh->lowerAddress, 22);
	EXPECT_EQ(nh->busNumber, 0xFF);
	EXPECT_EQ(nh->deviceNumber, 26);
	EXPECT_EQ(nh->functionNumber, 5);
	EXPECT_EQ(nh->tag, 15023);
	EXPECT_EQ(nh->completerID, 0xAB);
}

TEST(TLPGetObjRep, HeaderMem32) {
	boost::dynamic_bitset<> hbits = boost::dynamic_bitset<>(128);
	setBits(hbits, 0, 3, 12);
	setBits(hbits, 4, 7, 5);
	setBits(hbits, 34, 63, 0x3465123F);
	setBits(hbits, 64, 77, 15023);
	setBits(hbits, 80, 95, 0xA6B9);
	setBits(hbits, 96, 105, 0x3FA);
	setBits(hbits, 112, 116, 26);
	setBits(hbits, 117, 119, 5);
	setBits(hbits, 120, 127, 3);
	TLPHeader* h = (TLPHeader*)TLPHeader::getObjRep(hbits);
	OHCA1* ohc = (OHCA1*)(h->OHCVector[0]);
	EXPECT_EQ(ohc->firstDWBE.to_ulong(), 12);
	EXPECT_EQ(ohc->lastDWBE.to_ulong(), 5);
	AddressRouting32Bit* nh = (AddressRouting32Bit*)(h->nonBase);
	EXPECT_EQ(nh->address, 0x3465123F);
	EXPECT_EQ(nh->tag, 15023);
	EXPECT_EQ(nh->requestID, 0xA6B9);
	EXPECT_EQ(h->lengthInDoubleWord, 0x3FA);
	EXPECT_EQ(h->OHC, 26);
	EXPECT_EQ(h->TC, 5);
	EXPECT_EQ(static_cast<int>(h->TLPtype), 3);
}

TEST(TLPGetObjRep, HeaderMem64) {
	boost::dynamic_bitset<> hbits = boost::dynamic_bitset<>(160);
	setBits(hbits, 0, 3, 12);
	setBits(hbits, 4, 7, 5);
	setBits(hbits, 34, 95, 0x34651230A6B953F);
	setBits(hbits, 96, 109, 14906);
	setBits(hbits, 112, 127, 0x9FAB);
	setBits(hbits, 128, 137, 0x3FA);
	setBits(hbits, 144, 148, 26);
	setBits(hbits, 149, 151, 5);
	setBits(hbits, 152, 159, 32);
	TLPHeader* h = (TLPHeader*)TLPHeader::getObjRep(hbits);
	OHCA1* ohc = (OHCA1*)(h->OHCVector[0]);
	EXPECT_EQ(ohc->firstDWBE.to_ulong(), 12);
	EXPECT_EQ(ohc->lastDWBE.to_ulong(), 5);
	AddressRouting64Bit* nh = (AddressRouting64Bit*)(h->nonBase);
	EXPECT_EQ(nh->address, 0x34651230A6B953F);
	EXPECT_EQ(nh->tag, 14906);
	EXPECT_EQ(nh->requestID, 0x9FAB);
	EXPECT_EQ(h->lengthInDoubleWord, 0x3FA);
	EXPECT_EQ(h->OHC, 26);
	EXPECT_EQ(h->TC, 5);
	EXPECT_EQ(static_cast<int>(h->TLPtype), 32);
}

TEST(TLPGetObjRep, HeaderConfig) {
	boost::dynamic_bitset<> hbits = boost::dynamic_bitset<>(128);
	setBits(hbits, 0, 3, 12);
	setBits(hbits, 4, 7, 5);
	setBits(hbits, 24, 31, 158);
	setBits(hbits, 34, 43, 0x3B2);
	setBits(hbits, 48, 50, 5);
	setBits(hbits, 51, 55, 26);
	setBits(hbits, 56, 63, 0xFF);
	setBits(hbits, 64, 77, 15023);
	setBits(hbits, 80, 95, 0xA6B9);
	setBits(hbits, 96, 105, 0x3FA);
	setBits(hbits, 112, 116, 26);
	setBits(hbits, 117, 119, 5);
	setBits(hbits, 120, 127, 4);
	TLPHeader* h = (TLPHeader*)TLPHeader::getObjRep(hbits);
	OHCA3* ohc = (OHCA3*)(h->OHCVector[0]);
	EXPECT_EQ(ohc->firstDWBE.to_ulong(), 12);
	EXPECT_EQ(ohc->lastDWBE.to_ulong(), 5);
	EXPECT_EQ(ohc->destinationSegment, 158);
	ConfigNonHeaderBase* nh = (ConfigNonHeaderBase*)(h->nonBase);
	EXPECT_EQ(nh->registerNumber, 0x3B2);
	EXPECT_EQ(nh->functionNumber, 5);
	EXPECT_EQ(nh->deviceNumber, 26);
	EXPECT_EQ(nh->busNumber, 0xFF);
	EXPECT_EQ(nh->tag, 15023);
	EXPECT_EQ(nh->requestID, 0xA6B9);
	EXPECT_EQ(h->lengthInDoubleWord, 0x3FA);
	EXPECT_EQ(h->OHC, 26);
	EXPECT_EQ(h->TC, 5);
	EXPECT_EQ(static_cast<int>(h->TLPtype), 4);
}

TEST(TLPGetObjRep, HeaderMessage) {
	boost::dynamic_bitset<> hbits = boost::dynamic_bitset<>(160);
	setBits(hbits, 24, 31, 255);
	setBits(hbits, 96, 103, 0xB3);
	setBits(hbits, 112, 127, 0x9FAB);
	setBits(hbits, 128, 137, 0x3FA);
	setBits(hbits, 144, 148, 26);
	setBits(hbits, 149, 151, 5);
	setBits(hbits, 152, 159, 75);
	TLPHeader* h = (TLPHeader*)TLPHeader::getObjRep(hbits);
	OHCA4* ohc = (OHCA4*)(h->OHCVector[0]);
	EXPECT_EQ(ohc->destinationSegment, 255);
	MessageNonHeaderBase* nh = (MessageNonHeaderBase*)(h->nonBase);
	EXPECT_EQ(nh->messageCode, 0xB3);
	EXPECT_EQ(nh->requestID, 0x9FAB);
	EXPECT_EQ(h->lengthInDoubleWord, 0x3FA);
	EXPECT_EQ(h->OHC, 26);
	EXPECT_EQ(h->TC, 5);
	EXPECT_EQ(static_cast<int>(h->TLPtype), 75);
}

TEST(TLPGetObjRep, HeaderCompletion) {
	boost::dynamic_bitset<> hbits = boost::dynamic_bitset<>(128);
	setBits(hbits, 0, 2, 1);
	setBits(hbits, 3, 4, 2);
	setBits(hbits, 16, 23, 72);
	setBits(hbits, 24, 31, 126);
	setBits(hbits, 32, 43, 0x3B2);
	setBits(hbits, 44, 47, 6);
	setBits(hbits, 48, 50, 5);
	setBits(hbits, 51, 55, 26);
	setBits(hbits, 56, 63, 0xFF);
	setBits(hbits, 64, 77, 15023);
	hbits[78] = true;
	setBits(hbits, 80, 95, 0xAB);
	setBits(hbits, 96, 105, 0x3FA);
	setBits(hbits, 112, 116, 26);
	setBits(hbits, 117, 119, 5);
	setBits(hbits, 120, 127, 10);
	TLPHeader* h = (TLPHeader*)TLPHeader::getObjRep(hbits);
	OHCA5* ohc = (OHCA5*)(h->OHCVector[0]);
	EXPECT_EQ(ohc->CPLStatusEnum, OHCA5::CPLStatus::True);
	EXPECT_EQ(ohc->lowerAddress, 2);
	EXPECT_EQ(ohc->completerSegment, 72);
	EXPECT_EQ(ohc->destinationSegment, 126);
	CompletionNonHeaderBase* nh = (CompletionNonHeaderBase*)(h->nonBase);
	EXPECT_EQ(nh->byteCount, 0x3B2);
	EXPECT_EQ(nh->lowerAddress, 22);
	EXPECT_EQ(nh->busNumber, 0xFF);
	EXPECT_EQ(nh->deviceNumber, 26);
	EXPECT_EQ(nh->functionNumber, 5);
	EXPECT_EQ(nh->tag, 15023);
	EXPECT_EQ(nh->completerID, 0xAB);
	EXPECT_EQ(h->lengthInDoubleWord, 0x3FA);
	EXPECT_EQ(h->OHC, 26);
	EXPECT_EQ(h->TC, 5);
	EXPECT_EQ(static_cast<int>(h->TLPtype), 10);
}

TEST(TLPGetObjRep, TLPwithNoPayload) {
	boost::dynamic_bitset<> tlpbits = boost::dynamic_bitset<>(128);
	setBits(tlpbits, 0, 3, 12);
	setBits(tlpbits, 4, 7, 5);
	setBits(tlpbits, 34, 63, 0x3465123F);
	setBits(tlpbits, 64, 77, 15023);
	setBits(tlpbits, 80, 95, 0xA6B9);
	setBits(tlpbits, 96, 105, 0x3FA);
	setBits(tlpbits, 112, 116, 26);
	setBits(tlpbits, 117, 119, 5);
	setBits(tlpbits, 120, 127, 3);
	TLP* tlp = (TLP*)TLP::getObjRep(tlpbits);
	OHCA1* ohc = (OHCA1*)(tlp->header->OHCVector[0]);
	EXPECT_EQ(ohc->firstDWBE.to_ulong(), 12);
	EXPECT_EQ(ohc->lastDWBE.to_ulong(), 5);
	AddressRouting32Bit* nh = (AddressRouting32Bit*)(tlp->header->nonBase);
	EXPECT_EQ(nh->address, 0x3465123F);
	EXPECT_EQ(nh->tag, 15023);
	EXPECT_EQ(nh->requestID, 0xA6B9);
	EXPECT_EQ(tlp->header->lengthInDoubleWord, 0x3FA);
	EXPECT_EQ(tlp->header->OHC, 26);
	EXPECT_EQ(tlp->header->TC, 5);
	EXPECT_EQ(static_cast<int>(tlp->header->TLPtype), 3);
}

TEST(TLPGetObjRep, TLPwithPayload) {
	boost::dynamic_bitset<> tlpbits = boost::dynamic_bitset<>(192);
	setBits(tlpbits, 0, 63, 0x3465123F2BC014DA);
	setBits(tlpbits, 64, 67, 12);
	setBits(tlpbits, 68, 71, 5);
	setBits(tlpbits, 98, 127, 0x3465123F);
	setBits(tlpbits, 128, 141, 15023);
	setBits(tlpbits, 144, 159, 0xA6B9);
	setBits(tlpbits, 160, 169, 2);
	setBits(tlpbits, 176, 180, 26);
	setBits(tlpbits, 181, 183, 5);
	setBits(tlpbits, 184, 191, 64);
	TLP* tlp = (TLP*)TLP::getObjRep(tlpbits);
	OHCA1* ohc = (OHCA1*)(tlp->header->OHCVector[0]);
	EXPECT_EQ(ohc->firstDWBE.to_ulong(), 12);
	EXPECT_EQ(ohc->lastDWBE.to_ulong(), 5);
	AddressRouting32Bit* nh = (AddressRouting32Bit*)(tlp->header->nonBase);
	EXPECT_EQ(nh->address, 0x3465123F);
	EXPECT_EQ(nh->tag, 15023);
	EXPECT_EQ(nh->requestID, 0xA6B9);
	EXPECT_EQ(tlp->header->lengthInDoubleWord, 2);
	EXPECT_EQ(tlp->header->OHC, 26);
	EXPECT_EQ(tlp->header->TC, 5);
	EXPECT_EQ(static_cast<int>(tlp->header->TLPtype), 64);
	boost::dynamic_bitset<> payloadMSBs = tlp->dataPayload.operator>>(32);
	boost::dynamic_bitset<> payloadLSBs = tlp->dataPayload;
	payloadMSBs.resize(32);
	payloadLSBs.resize(32);
	EXPECT_EQ(payloadLSBs.to_ulong(), 0x2BC014DA);
	EXPECT_EQ(payloadMSBs.to_ulong(), 0x3465123F);
}
