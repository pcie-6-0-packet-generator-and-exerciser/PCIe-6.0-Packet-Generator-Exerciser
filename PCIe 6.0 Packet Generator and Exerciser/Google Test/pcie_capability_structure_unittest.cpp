#include "pch.h"

#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/configuration_visitor_classes/configuration_write_visitor.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/configuration_visitor_classes/configuration_read_visitor.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/configuration_algorithm_classes/completion_construction_algorithms.h"

/****************************************************** Writing in the PCIe Capability Structure ********************************/

PCIECapability* pcie = PCIECapability::constructPCIECapability();

/* Test for Boundary register number */
TEST(WritingInThePCIeCapability, Boundary1)
{
	int returnVal;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();

	write->setRegisterNumber(-1);
	write->setData(0);

	returnVal = write->visitPcieCapabilityStructure(pcie);

	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out
}

/* Test for Boundary register number */
TEST(WritingInThePCIeCapability, Boundary2)
{
	int returnVal;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();

	write->setRegisterNumber(23);
	write->setData(0);

	returnVal = write->visitPcieCapabilityStructure(pcie);

	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out
}

/* Test to write in a RO Register */
TEST(WritingInThePCIeCapability, RO)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* temp = pcie->getHead();

	for (int i = 0; i < 3; i++)
		temp = temp->getRegisterNext();

	registerValBefore = temp->getRegisterValue();

	write->setRegisterNumber(20);
	write->setData((unsigned int)0xFF11);

	returnVal = write->visitPcieCapabilityStructure(pcie);
	registerValAfter = temp->getRegisterValue();

	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out
	EXPECT_EQ(registerValBefore, registerValAfter); // Make sure that the Register value isn't changed
}

/* Test to write in a RW Register with initial value = 0 */
TEST(WritingInThePCIeCapability, RW)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* temp = pcie->getHead();

	for (int i = 0; i < 5; i++)
		temp = temp->getRegisterNext();

	registerValBefore = temp->getRegisterValue();

	write->setRegisterNumber(22);
	write->setData((unsigned int)0xFFFFFFFF);

	returnVal = write->visitPcieCapabilityStructure(pcie);
	registerValAfter = temp->getRegisterValue();

	EXPECT_EQ(returnVal, 1); // Make sure that the Write operation is carried out
	EXPECT_NE(registerValBefore, registerValAfter); // Make sure that the Register value is changed
	EXPECT_EQ(registerValAfter, 4008636143); // Make sure that the Register value is correct

	temp->setRegisterValue(temp->getRegisterInitialValue());
}

/* Test to write in a RW Register with initial value != 0 */
TEST(WritingInThePCIeCapability, RW2)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();

	Register* temp = pcie->getHead();

	for (int i = 0; i < 4; i++)
		temp = temp->getRegisterNext();

	temp->setRegisterValue(0xBCDF1234);

	registerValBefore = temp->getRegisterValue();

	write->setRegisterNumber(21);
	write->setData((unsigned int)0xAF123EC0);

	returnVal = write->visitPcieCapabilityStructure(pcie);
	registerValAfter = temp->getRegisterValue();

	EXPECT_EQ(returnVal, 1); // Make sure that the Write operation is carried out
	EXPECT_NE(registerValBefore, registerValAfter); // Make sure that the Register value is changed
	EXPECT_EQ(registerValAfter, 3188931264); // Make sure that the Register value is correct

	temp->setRegisterValue(temp->getRegisterInitialValue());
}