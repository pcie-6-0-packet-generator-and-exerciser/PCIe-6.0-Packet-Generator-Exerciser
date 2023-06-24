#include "pch.h"

#include "..\PCIe 6.0 Packet Generator and Exerciser\type1_config_space\type1_config.h"

Type1Config* t1 = Type1Config::constructType1ConfigSpace();

TEST(ReadFromType1Config, validRead)
{
	boost::dynamic_bitset<> expected1(16, 0b0000000000001100), expected2, expected3;

	expected2.resize(32);
	expected3.resize(16);

	boost::dynamic_bitset<> data =	t1->readType1Reg(0);
	boost::dynamic_bitset<> data2 =	t1->readType1Reg(11);
	boost::dynamic_bitset<> data3 =	t1->readType1Reg(32);

	EXPECT_EQ(data, expected1);
	EXPECT_EQ(data2, expected2);
	EXPECT_EQ(data3, expected3);
}

TEST(ReadFromType1Config, inValidRead)
{
	boost::dynamic_bitset<> expected;
	expected.push_back(0);

	boost::dynamic_bitset<> data = t1->readType1Reg(-1);
	boost::dynamic_bitset<> data2 = t1->readType1Reg(33);

	EXPECT_EQ(data.size(), 0);
	EXPECT_NE(data, expected);
	EXPECT_EQ(data2.size(), 0);
}

TEST(WriteInType1Config, validWrite)
{
	boost::dynamic_bitset<> data1(16, 0b0000000010100111), data2(8, 0b11000101), data3(16, 0b0000001010000011);

	int returnVal1 = 0, returnVal2 = 0, returnVal3 = 0;

	//returnVal1 = t1->writeType1Reg(2, data1);
	returnVal2 = t1->writeType1Reg(16, data2);
	returnVal3 = t1->writeType1Reg(25, data3);

	//EXPECT_EQ(returnVal1, 1);
	EXPECT_EQ(returnVal2, 1);
	EXPECT_EQ(returnVal3, 1);

	//EXPECT_EQ(data1, t1->readType1Reg(2));
	EXPECT_NE(data2, t1->readType1Reg(16));
	EXPECT_EQ(data3, t1->readType1Reg(25));
}

TEST(WriteInType1Config, InvalidWrite)
{
	boost::dynamic_bitset<> data1(16, 0b0101011100110000), data2(24, 0b000000000011000000000011), data3(8, 0b01010101);

	int returnVal1 = 1, returnVal2 = 1, returnVal3 = 1, returnVal4 = 1;

	returnVal1 = t1->writeType1Reg(-1, data1);
	returnVal2 = t1->writeType1Reg(5, data2);
	returnVal3 = t1->writeType1Reg(28, data1);
	returnVal4 = t1->writeType1Reg(33, data3);

	EXPECT_EQ(returnVal1, 0);
	EXPECT_EQ(returnVal2, 0);
	EXPECT_EQ(returnVal3, 0);
	EXPECT_EQ(returnVal4, 0);

	EXPECT_NE(data1, t1->readType1Reg(28));
	EXPECT_NE(data2, t1->readType1Reg(5));
}

TEST(Type1RegSize, size1)
{
	boost::dynamic_bitset<> data1, data2, data3, data4;

	data1 = t1->readType1Reg(10); // 32-bits
	data2 = t1->readType1Reg(5); // 24-bits
	data3 = t1->readType1Reg(3); // 16-bits
	data4 = t1->readType1Reg(12); // 8-bits

	EXPECT_EQ(data1.size(), 32);
	EXPECT_EQ(data2.size(), 24);
	EXPECT_EQ(data3.size(), 16);
	EXPECT_EQ(data4.size(), 8);
}

TEST(Type1RegSize, size2)
{
	int returnVal = 0;

	boost::dynamic_bitset<> data1, data2(8, 0x0F), data3(32, 0xFFFFFF0F);

	returnVal = t1->writeType1Reg(9, data3);

	data1 = t1->readType1Reg(9);

	EXPECT_EQ(data1.size(), 8);
}