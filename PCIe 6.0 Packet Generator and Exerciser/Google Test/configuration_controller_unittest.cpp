#include "pch.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/controller_class/configuration_controller.h"

ConfigurationController* controler = ConfigurationController::constructConfigurationController();

TEST(HandlingConfigurationRequests, RegisterNumber)
{
	boost::dynamic_bitset<> data(8);
	data.push_back(1); data.push_back(1); data.push_back(0); data.push_back(0);

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 7, 0, 0, 0, 0, 0, 0);
	TLP* tlp2 = TLP::createConfigRead0Tlp(0, 0, -1, 0, 0, 0, 0, 0, 0);

	EXPECT_EQ(controler->getRegisterNumber(tlp), 7);
	EXPECT_EQ(controler->getRegisterNumber(tlp2), -1);
}

TEST(HandlingConfigurationRequests, TLPType)
{
	boost::dynamic_bitset<> data(8);
	data.push_back(1); data.push_back(1); data.push_back(0); data.push_back(0);

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 7, 0, 0, 0, 0, 0, 0);
	TLP* tlp2 = TLP::createConfigRead0Tlp(0, 0, -1, 0, 0, 0, 0, 0, 0);

	EXPECT_EQ(controler->getTLPType(tlp), TLPType::ConfigWrite0);
	EXPECT_EQ(controler->getTLPType(tlp2), TLPType::ConfigRead0);
}

TEST(HandlingConfigurationRequests, TLPData)
{
	TLP* tlp;
	boost::dynamic_bitset<> data(8, 0b11001001), data2(16, 0b1100100111001001), data3(32), data4(32);
	unsigned int d1, d2, d3, d4, d5;

	data3.set();
	data4.reset();

	tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 7, 0, 0, 0, 0, 0, 0);
	d1 = controler->getTLPData(tlp);

	tlp = TLP::createConfigWrite0Tlp(1, data2, 0, 0, 7, 0, 0, 0, 0, 0, 0);
	d2 = controler->getTLPData(tlp);

	tlp = TLP::createConfigWrite0Tlp(1, data3, 0, 0, 7, 0, 0, 0, 0, 0, 0);
	d3 = controler->getTLPData(tlp);

	tlp = TLP::createConfigWrite0Tlp(1, data4, 0, 0, 7, 0, 0, 0, 0, 0, 0);
	d4 = controler->getTLPData(tlp);

	tlp = TLP::createConfigRead0Tlp(0, 0, -1, 0, 0, 0, 0, 0, 0);
	d5 = controler->getTLPData(tlp);

	EXPECT_EQ(d1, 201);
	EXPECT_EQ(d2, 51657);
	EXPECT_EQ(d3, 4294967295);
	EXPECT_EQ(d4, 0);
	EXPECT_EQ(d5, 0);
}

TEST(HandlingConfigurationRequests, Conversion)
{
	boost::dynamic_bitset<> data, data2, data3;
	boost::dynamic_bitset<> data11(1), data22(17, 0b11110001001000000), data33(32, 0xFFFFFFFF);

	data11.reset();

	data = controler->convertToBitSet(0);
	data2 = controler->convertToBitSet(123456);
	data3 = controler->convertToBitSet(4294967295);

	EXPECT_EQ(data, data11);
	EXPECT_EQ(data2, data22);
	EXPECT_EQ(data3, data33);
}

TEST(HandlingConfigurationRequests, InvalidRegisterNumber)
{
	TLP* configReadTlp = TLP::createConfigRead0Tlp(0, 0, -1, 0, 0, 0, 0, 0, 0);

	TLP* urTlp = controler->handleConfigurationRequest(configReadTlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(urTlp->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
	EXPECT_EQ(urTlp->header->TLPtype, TLPType::Cpl);
}

TEST(HandlingConfigurationRequests, InvalidRegisterNumber2)
{
	TLP* configReadTlp = TLP::createConfigRead0Tlp(0, 0, 32, 0, 0, 0, 0, 0, 0);

	TLP* urTlp = controler->handleConfigurationRequest(configReadTlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(urTlp->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
	EXPECT_EQ(urTlp->header->TLPtype, TLPType::Cpl);
}

TEST(HandlingConfigurationRequests, ValidConfigurationRead)
{
	TLP* tlp = TLP::createConfigRead0Tlp(0, 0, 3, 0, 0, 0, 0, 0, 0);

	TLP* cplD = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cplD->header->OHCVector[0]);
	boost::dynamic_bitset<> data(16, 0b0000000000010001);

	EXPECT_EQ(cplD->dataPayload, data);
	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::True);
	EXPECT_EQ(cplD->header->TLPtype, TLPType::CplD);
}

TEST(HandlingConfigurationRequests, ValidCapabilityRead)
{
	TLP* tlp = TLP::createConfigRead0Tlp(0, 0, 17, 0, 0, 0, 0, 0, 0);
	TLP* tlp2 = TLP::createConfigRead0Tlp(0, 0, 18, 0, 0, 0, 0, 0, 0);

	TLP* cplD = controler->handleConfigurationRequest(tlp);
	TLP* cplD2 = controler->handleConfigurationRequest(tlp2);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cplD->header->OHCVector[0]);
	OHCA5* ohcA52 = dynamic_cast<OHCA5*>(cplD2->header->OHCVector[0]);
	boost::dynamic_bitset<> data(8, 0b00000001);
	boost::dynamic_bitset<> data2(8, 0b10000000);

	EXPECT_EQ(cplD->dataPayload, data);
	EXPECT_EQ(cplD2->dataPayload, data2);
	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::True);
	EXPECT_EQ(ohcA52->CPLStatusEnum, OHCA5::CPLStatus::True);
	EXPECT_EQ(cplD->header->TLPtype, TLPType::CplD);
	EXPECT_EQ(cplD2->header->TLPtype, TLPType::CplD);
}

TEST(HandlingConfigurationRequests, ValidConfigurationWrite)
{
	boost::dynamic_bitset<> data(8, 0b11110011);
	std::bitset<4> fbe, lbe;
	ConfigurationSpace* config = controler->configuration;
	Register* reg = config->getHead()->getRegisterNext()->getRegisterNext();
	unsigned int regValueBefore = reg->getRegisterValue();

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 2, 0, 0, 0, fbe, lbe, 0);

	TLP* cpl = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cpl->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::True);
	EXPECT_EQ(cpl->header->TLPtype, TLPType::Cpl);
	EXPECT_EQ(reg->getRegisterValue(), 67);
	EXPECT_NE(reg->getRegisterValue(), regValueBefore);

	reg->setRegisterValue(reg->getRegisterInitialValue());
}

TEST(HandlingConfigurationRequests, ValidConfigurationWrite2)
{
	boost::dynamic_bitset<> data(32, 0xEEFFFFFF);
	std::bitset<4> fbe, lbe;
	ConfigurationSpace* config = controler->configuration;
	Register* reg = config->getHead();

	for (int i = 0; i < 7; i++)
		reg = reg->getRegisterNext();

	unsigned int regValueBefore = reg->getRegisterValue();

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 7, 0, 0, 0, fbe, lbe, 0);

	TLP* cpl = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cpl->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::True);
	EXPECT_EQ(cpl->header->TLPtype, TLPType::Cpl);
	EXPECT_EQ(reg->getRegisterValue(), 3221225484);
	EXPECT_NE(reg->getRegisterValue(), regValueBefore);

	reg->setRegisterValue(reg->getRegisterInitialValue());
}

TEST(HandlingConfigurationRequests, ValidCapabilityWrite)
{
	boost::dynamic_bitset<> data(16, 0b0011101000111010);
	std::bitset<4> fbe, lbe;
	PCIECapability* pcie = controler->capability;
	Register* reg = pcie->getHead();

	for (int i = 0; i < 4; i++)
		reg = reg->getRegisterNext();

	unsigned int regValueBefore = reg->getRegisterValue();

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 21, 0, 0, 0, fbe, lbe, 0);

	TLP* cpl = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cpl->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::True);
	EXPECT_EQ(cpl->header->TLPtype, TLPType::Cpl);
	EXPECT_EQ(reg->getRegisterValue(), 14394);
	EXPECT_NE(reg->getRegisterValue(), regValueBefore);

	reg->setRegisterValue(reg->getRegisterInitialValue());
}

TEST(HandlingConfigurationRequests, InvalidConfigurationWrite)
{
	boost::dynamic_bitset<> data(8, 0b11110011);
	std::bitset<4> fbe, lbe;
	ConfigurationSpace* config = controler->configuration;
	Register* reg = config->getHead()->getRegisterNext();
	unsigned int regValueBefore = reg->getRegisterValue();

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 1, 0, 0, 0, fbe, lbe, 0);

	TLP* cpl = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cpl->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
	EXPECT_EQ(cpl->header->TLPtype, TLPType::Cpl);
	EXPECT_EQ(reg->getRegisterValue(), regValueBefore);
	EXPECT_EQ(reg->getRegisterValue(), 0);
}

TEST(HandlingConfigurationRequests, InvalidConfigurationWrite2)
{
	boost::dynamic_bitset<> data(8, 0b11110011);
	std::bitset<4> fbe, lbe;
	ConfigurationSpace* config = controler->configuration;
	Register* reg = config->getHead()->getRegisterNext()->getRegisterNext()->getRegisterNext()->getRegisterNext()->getRegisterNext();
	unsigned int regValueBefore = reg->getRegisterValue();

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 5, 0, 0, 0, fbe, lbe, 0);

	TLP* cpl = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cpl->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
	EXPECT_EQ(cpl->header->TLPtype, TLPType::Cpl);
	EXPECT_EQ(reg->getRegisterValue(), regValueBefore);
	EXPECT_EQ(reg->getRegisterValue(), 557056);
}

TEST(HandlingConfigurationRequests, InvalidCapabilityWrite)
{
	boost::dynamic_bitset<> data(8, 0b10111000);
	std::bitset<4> fbe, lbe;
	PCIECapability* pcie = controler->capability;
	Register* reg = pcie->getHead()->getRegisterNext()->getRegisterNext();
	unsigned int regValueBefore = reg->getRegisterValue();

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 19, 0, 0, 0, fbe, lbe, 0);

	TLP* cpl = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cpl->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
	EXPECT_EQ(cpl->header->TLPtype, TLPType::Cpl);
	EXPECT_EQ(reg->getRegisterValue(), regValueBefore);
	EXPECT_EQ(reg->getRegisterValue(), 3);
}

TEST(HandlingConfigurationRequests, UnknownRequest)
{
	boost::dynamic_bitset<> data(8, 0b11110011);
	std::bitset<4> fbe, lbe;
	ConfigurationSpace* config = controler->configuration;
	Register* reg = config->getHead()->getRegisterNext()->getRegisterNext()->getRegisterNext();
	unsigned int regValueBefore = reg->getRegisterValue();

	TLP* tlp = TLP::createConfigWrite1Tlp(1, data, 0, 0, 3, 0, 0, 0, fbe, lbe, 0);

	TLP* cpl = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cpl->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
	EXPECT_EQ(cpl->header->TLPtype, TLPType::Cpl);
	EXPECT_EQ(reg->getRegisterValue(), regValueBefore);
}

TEST(HandlingConfigurationRequests, UnknownRequest2)
{
	TLP* tlp = TLP::createConfigRead1Tlp(0, 0, 6, 0, 0, 0, 0, 0, 0);

	TLP* cpl = controler->handleConfigurationRequest(tlp);

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(cpl->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
	EXPECT_EQ(cpl->header->TLPtype, TLPType::Cpl);
}