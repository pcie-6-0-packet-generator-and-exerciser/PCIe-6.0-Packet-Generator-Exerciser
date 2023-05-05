#include "pch.h"

#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/configuration_algorithm_classes/completion_construction_algorithms.h"

/***************************************** Constructing our three types of Completions (TLPs) *********************************/

/* Test for constructing a Completion without Data */
TEST(ConstructingCompletions, Cpl)
{
	CompletionWithoutData* completion = new CompletionWithoutData();
	boost::dynamic_bitset<> data(8);
	std::bitset<2> lowerAddress(0b00);
	data.push_back(1); data.push_back(1); data.push_back(0); data.push_back(0);

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	completion->tlp = tlp;

	TLP* complete = completion->constructTLP();

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(complete->header->OHCVector[0]);

	EXPECT_EQ(1, 1);

	EXPECT_EQ(complete->header->TLPtype, TLPType::Cpl);
	EXPECT_EQ(complete->header->lengthInDoubleWord, 0);
	EXPECT_EQ(ohcA5->lowerAddress, lowerAddress);
	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::True);
}

/* Test for constructing a Completion with Data */
TEST(ConstructingCompletions, cplD)
{
	CompletionWithData* completion = new CompletionWithData();
	std::bitset<2> lowerAddress(0b00);

	TLP* tlp = TLP::createConfigRead0Tlp(0, 0, 0, 0, 0, 0, 0, 0, 0);

	completion->tlp = tlp;

	TLP* complete = completion->constructTLP();

	TLPType type = complete->header->TLPtype;

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(complete->header->OHCVector[0]);

	EXPECT_EQ(type, TLPType::CplD);
	EXPECT_EQ(ohcA5->lowerAddress, lowerAddress);
	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::True);
}

/* Test for constructing a Completion without Data and with Unsupported Request */
TEST(ConstructingCompletions, CplUR)
{
	CompletionWithUR* completion = new CompletionWithUR();
	std::bitset<2> lowerAddress(0b00);

	TLP* tlp = TLP::createConfigRead0Tlp(0, 0, 0, 0, 0, 0, 0, 0, 0);

	completion->tlp = tlp;

	TLP* complete = completion->constructTLP();

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(complete->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->lowerAddress, lowerAddress);
	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
}

/* Test for constructing a Completion without Data and with Unsupported Request for unhandled Configuration Write */
TEST(ConstructingCompletions, CplUR2)
{
	CompletionWithUR* completion = new CompletionWithUR();
	boost::dynamic_bitset<> data(8);
	std::bitset<2> lowerAddress(0b00);

	data.push_back(1); data.push_back(1); data.push_back(0); data.push_back(0);

	TLP* tlp = TLP::createConfigWrite0Tlp(1, data, 0, 0, 0, 0, 0, 0, 0, 0, 0);

	completion->tlp = tlp;

	TLP* complete = completion->constructTLP();

	OHCA5* ohcA5 = dynamic_cast<OHCA5*>(complete->header->OHCVector[0]);

	EXPECT_EQ(ohcA5->lowerAddress, lowerAddress);
	EXPECT_EQ(ohcA5->CPLStatusEnum, OHCA5::CPLStatus::False);
}