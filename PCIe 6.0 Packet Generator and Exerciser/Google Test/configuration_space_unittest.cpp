#include "pch.h"

#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/configuration_visitor_classes/configuration_write_visitor.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/configuration_visitor_classes/configuration_read_visitor.h"
#include "../PCIe 6.0 Packet Generator and Exerciser/Endpoint/configuration_algorithm_classes/completion_construction_algorithms.h"

/********************************************************** Writing in the Configuration Space ********************************/

ConfigurationSpace* config = ConfigurationSpace::constructConfigurationSpace();

/* Test for Boundary register number */
TEST(WritingInTheConfigurationSpace, Boundary1)
{
	int returnVal;
	unsigned int masterAbort;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* status = config->getHead();

	for (int i = 0; i < 3; i++)
		status = status->getRegisterNext();

	write->setRegisterNumber(-1);
	write->setData(0);
	returnVal = write->visitConfigurationSpace(config);
	masterAbort = status->getRegisterValue();
	masterAbort &= 0x00002000;
	masterAbort = masterAbort >> 13;

	EXPECT_EQ(masterAbort, 1); // Make sure that the Recieved Master Abort bit is set
	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for Boundary register number */
TEST(WritingInTheConfigurationSpace, Boundary2)
{
	int returnVal;
	unsigned int masterAbort;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* status = config->getHead();

	for (int i = 0; i < 3; i++)
		status = status->getRegisterNext();

	write->setRegisterNumber(17);
	write->setData(0);
	returnVal = write->visitConfigurationSpace(config);
	masterAbort = status->getRegisterValue();
	masterAbort &= 0x00002000;
	masterAbort = masterAbort >> 13;

	EXPECT_EQ(masterAbort, 1); // Make sure that the Recieved Master Abort bit is set
	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for writing in BAR4 which isn't used */
TEST(WritingInTheConfigurationSpace, BAR4)
{
	int returnVal;
	unsigned int masterAbort, registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* status = config->getHead(), * temp = config->getHead();

	for (int i = 0; i < 11; i++)
	{
		temp = temp->getRegisterNext();

		if (i < 3)
			status = status->getRegisterNext();
	}

	registerValBefore = temp->getRegisterValue();

	write->setRegisterNumber(11);
	write->setData((unsigned int)0xA56C);
	returnVal = write->visitConfigurationSpace(config);
	masterAbort = status->getRegisterValue();
	registerValAfter = temp->getRegisterValue();
	masterAbort &= 0x00002000;
	masterAbort = masterAbort >> 13;

	EXPECT_EQ(registerValBefore, registerValAfter); // Making sure that the register value isn't changed
	EXPECT_EQ(masterAbort, 1); // Make sure that the Recieved Master Abort bit is set
	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for writing in BAR5 which isn't used */
TEST(WritingInTheConfigurationSpace, BAR5)
{
	int returnVal;
	unsigned int masterAbort, registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* status = config->getHead(), * temp = config->getHead();

	for (int i = 0; i < 12; i++)
	{
		temp = temp->getRegisterNext();

		if (i < 3)
			status = status->getRegisterNext();
	}

	registerValBefore = temp->getRegisterValue();

	write->setRegisterNumber(12);
	write->setData(0);
	returnVal = write->visitConfigurationSpace(config);
	masterAbort = status->getRegisterValue();
	registerValAfter = temp->getRegisterValue();

	masterAbort &= 0x00002000;
	masterAbort = masterAbort >> 13;

	EXPECT_EQ(registerValBefore, registerValAfter); // Making sure that the register value isn't changed
	EXPECT_EQ(masterAbort, 1); // Make sure that the Recieved Master Abort bit is set
	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for writing in a Hardware Initialized Register */
TEST(WritingInTheConfigurationSpace, HwInit)
{
	int returnVal;
	unsigned int masterAbort, registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* status = config->getHead(), * temp = config->getHead();

	for (int i = 0; i < 3; i++)
		status = status->getRegisterNext();

	registerValBefore = temp->getRegisterValue();
	write->setRegisterNumber(0);
	write->setData((unsigned int)0xAC520);
	returnVal = write->visitConfigurationSpace(config);
	masterAbort = status->getRegisterValue();
	registerValAfter = temp->getRegisterValue();
	masterAbort &= 0x00002000;
	masterAbort = masterAbort >> 13;

	EXPECT_EQ(registerValBefore, registerValAfter); // Making sure that the register value isn't changed
	EXPECT_EQ(masterAbort, 1); // Make sure that the Recieved Master Abort bit is set
	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for writing in a Read Only Register */
TEST(WritingInTheConfigurationSpace, RO)
{
	int returnVal;
	unsigned int masterAbort, registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* status = config->getHead(), * temp = config->getHead();

	for (int i = 0; i < 5; i++)
	{
		temp = temp->getRegisterNext();

		if (i < 3)
			status = status->getRegisterNext();
	}

	registerValBefore = temp->getRegisterValue();
	write->setRegisterNumber(5);
	write->setData(0);
	returnVal = write->visitConfigurationSpace(config);
	masterAbort = status->getRegisterValue();
	registerValAfter = temp->getRegisterValue();

	masterAbort &= 0x00002000;
	masterAbort = masterAbort >> 13;

	EXPECT_EQ(registerValBefore, registerValAfter); // Making sure that the register value isn't changed
	EXPECT_EQ(masterAbort, 1); // Make sure that the Recieved Master Abort bit is set
	EXPECT_EQ(returnVal, 0); // Make sure that the Write operation isn't carried out

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for writing in the Signaled System Error bit inside the Status Register */
TEST(WritingInTheConfigurationSpace, SignaledSystemErrorBit)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* status = config->getHead(), * temp = config->getHead();

	for (int i = 0; i < 3; i++)
		status = status->getRegisterNext();

	registerValBefore = status->getRegisterValue();
	write->setRegisterNumber(3);
	write->setData((unsigned int)0x00004000);// Writing in the Signaled System Error bit
	returnVal = write->visitConfigurationSpace(config);
	registerValAfter = status->getRegisterValue();

	EXPECT_EQ(returnVal, 1);// Make sure that the Write operation is carried out
	EXPECT_EQ(registerValBefore, registerValAfter); // Making sure that the Signaled System Error bit inside the Status Register value isn't changed as the SERR# Enable bit in the Command Register is = 0

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for writing in the Signaled System Error bit inside the Status Register */
TEST(WritingInTheConfigurationSpace, SignaledSystemErrorBit2)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* command = config->getHead(), * status = config->getHead();

	for (int i = 0; i < 3; i++)
	{
		status = status->getRegisterNext();

		if (i < 2)
			command = command->getRegisterNext();
	}

	command->setRegisterValue((unsigned int)0x100);

	registerValBefore = status->getRegisterValue();
	write->setRegisterNumber(3);
	write->setData((unsigned int)0x4000);// Writing in the Signaled System Error bit
	returnVal = write->visitConfigurationSpace(config);
	registerValAfter = command->getRegisterValue();

	EXPECT_EQ(returnVal, 1);// Make sure that the Write operation is carried out
	EXPECT_NE(registerValBefore, registerValAfter); // Making sure that the Signaled System Error bit inside the Status Register value is changed as the SERR# Enable bit in the Command Register is = 1

	status->setRegisterValue(status->getRegisterInitialValue());
	command->setRegisterValue(0);
}

/* Test for writing in the Master Data Parity Error bit inside the Status Register */
TEST(WritingInTheConfigurationSpace, MasterDataParityErrorBit)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register * status = config->getHead();

	for (int i = 0; i < 3; i++)
		status = status->getRegisterNext();

	registerValBefore = status->getRegisterValue();
	write->setRegisterNumber(3);
	write->setData((unsigned int)0x100);// Writing in the Master Data Parity Error bit
	returnVal = write->visitConfigurationSpace(config);
	registerValAfter = status->getRegisterValue();

	EXPECT_EQ(returnVal, 1);// Make sure that the Write operation is carried out
	EXPECT_EQ(registerValBefore, registerValAfter); // Making sure that the Master Data Parity Error bit inside the Status Register value isn't changed as the Parity Error Response bit in the Command Register is = 0

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for writing in the Master Data Parity Error bit bit inside the Status Register */
TEST(WritingInTheConfigurationSpace, MasterDataParityErrorBit2)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* command = config->getHead(), * status = config->getHead();

	for (int i = 0; i < 3; i++)
	{
		status = status->getRegisterNext();

		if (i < 2)
			command = command->getRegisterNext();
	}

	command->setRegisterValue((unsigned int)0x00000040);
	registerValBefore = status->getRegisterValue();
	write->setRegisterNumber(3);
	write->setData((unsigned int)0x00000100);// Writing in the Signaled System Error bit
	returnVal = write->visitConfigurationSpace(config);
	registerValAfter = status->getRegisterValue();

	EXPECT_EQ(returnVal, 1);// Make sure that the Write operation is carried out
	EXPECT_NE(registerValBefore, registerValAfter); // Making sure that the Master Data Parity Error bit inside the Status Register value is changed as the Parity Error Response bit in the Command Register is = 1

	status->setRegisterValue(status->getRegisterInitialValue());
	command->setRegisterValue(0);
}

/* Test for writing in the Expansion ROM Base Address Register while the Memory Space isn't Enabled */
TEST(WritingInTheConfigurationSpace, ExpansionROMBaseAddressRegister)
{
	int returnVal, masterAbort;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* temp = config->getHead(), * status = config->getHead();

	for (int i = 0; i < 15; i++)
	{
		temp = temp->getRegisterNext();

		if(i < 3)
			status = status->getRegisterNext();
	}

	registerValBefore = temp->getRegisterValue();
	write->setRegisterNumber(15);
	write->setData(0xFF);
	registerValAfter = temp->getRegisterValue();
	returnVal = write->visitConfigurationSpace(config);
	masterAbort = status->getRegisterValue();
	masterAbort &= 0x00002000;
	masterAbort = masterAbort >> 13;

	EXPECT_EQ(masterAbort, 1); // Make sure that the Recieved Master Abort bit is set
	EXPECT_EQ(returnVal, 0);
	EXPECT_EQ(registerValBefore, registerValAfter);

	status->setRegisterValue(status->getRegisterInitialValue());
}

/* Test for writing in the Expansion ROM Base Address Register while the Memory Space is Enabled */
TEST(WritingInTheConfigurationSpace, ExpansionROMBaseAddressRegister2)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* temp = config->getHead(), * command = config->getHead();

	for (int i = 0; i < 15; i++)
	{
		temp = temp->getRegisterNext();

		if (i < 2)
			command = command->getRegisterNext();
	}

	command->setRegisterValue((unsigned int)0x2);
	registerValAfter = temp->getRegisterValue();
	write->setRegisterNumber(15);
	write->setData(0xFF);
	returnVal = write->visitConfigurationSpace(config);
	registerValBefore = temp->getRegisterValue();

	EXPECT_NE(registerValBefore, registerValAfter);
	EXPECT_EQ(returnVal, 1); // Make sure that the Write operation is carried out

	command->setRegisterValue(0);
}

/* Test for writing in a normal Read Write Register with initial value = 0 */
TEST(WritingInTheConfigurationSpace, RW)
{
	int returnVal;
	unsigned int registerVal;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* command = config->getHead();
	
	command = command->getRegisterNext()->getRegisterNext();
	write->setRegisterNumber(2);
	write->setData(0xFFFFFFFF);
	returnVal = write->visitConfigurationSpace(config);
	registerVal = command->getRegisterValue();

	EXPECT_EQ(registerVal, 1347); // Make sure that we only write in the read write bits
	EXPECT_EQ(returnVal, 1); // Make sure that the Write operation is carried out

	command->setRegisterValue(0);
}

/* Test for writing in a normal Read Write Register with initial value != 0 */
TEST(WritingInTheConfigurationSpace, RW2)
{
	int returnVal;
	unsigned int registerVal;

	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();
	Register* command = config->getHead();

	command = command->getRegisterNext()->getRegisterNext();
	command->setRegisterValue(0xF0123);
	write->setRegisterNumber(2);
	write->setData(0x0C3642);
	returnVal = write->visitConfigurationSpace(config);
	registerVal = command->getRegisterValue();

	EXPECT_EQ(registerVal, 984162); // Make sure that we only write in the read write bits
	EXPECT_EQ(returnVal, 1); // Make sure that the Write operation is carried out

	command->setRegisterValue(0);
}

/******************************************************** Reading from the Configuration Space ********************************/

/* Test for reading from a RW Register */
TEST(ReadingFromTheConfigurationSpace, RW)
{
	unsigned int registerVal;

	ConfigurationReadVisitor* read = new ConfigurationReadVisitor();

	read->setRegisterNumber(3);
	registerVal = read->visitConfigurationSpace(config);

	EXPECT_EQ(registerVal, 17);
}

/* Test for reading from a RO Register */
TEST(ReadingFromTheConfigurationSpace, RO)
{
	unsigned int registerVal;

	ConfigurationReadVisitor* read = new ConfigurationReadVisitor();

	read->setRegisterNumber(5);
	registerVal = read->visitConfigurationSpace(config);

	EXPECT_EQ(registerVal, 557056);
}

/* Test for reading from a HwInit Register */
TEST(ReadingFromTheConfigurationSpace, HwInit)
{
	unsigned int registerVal;

	ConfigurationReadVisitor* read = new ConfigurationReadVisitor();

	read->setRegisterNumber(14);
	registerVal = read->visitConfigurationSpace(config);

	EXPECT_EQ(registerVal, 0);
}

/* Test for reading from a Register after writing a value inside */
TEST(ReadingFromTheConfigurationSpace, WriteThenRead)
{
	unsigned int registerVal;

	ConfigurationReadVisitor* read = new ConfigurationReadVisitor();
	Register* temp = config->getHead();

	for (int i = 0; i < 10; i++)
		temp = temp->getRegisterNext();

	temp->setRegisterValue((unsigned int)0x100ABC);

	read->setRegisterNumber(10);
	registerVal = read->visitConfigurationSpace(config);

	EXPECT_EQ(registerVal, 1051324);
}

/* Test for reading from a HwInit Register */
TEST(ReadingFromTheConfigurationSpace, WriteThenRead2)
{
	int returnVal;
	unsigned int registerValBefore, registerValAfter;

	ConfigurationReadVisitor* read = new ConfigurationReadVisitor();
	ConfigurationWriteVisitor* write = new ConfigurationWriteVisitor();

	read->setRegisterNumber(7);
	registerValBefore = read->visitConfigurationSpace(config);

	write->setRegisterNumber(7);
	write->setData((unsigned int)0xF33CDFFF);
	returnVal = write->visitConfigurationSpace(config);

	registerValAfter = read->visitConfigurationSpace(config);

	EXPECT_EQ(returnVal, 1);
	EXPECT_EQ(registerValBefore, 12);
	EXPECT_EQ(registerValAfter, 3221225484);
}

/* Test for the initial value and mask of a register */
TEST(ConfigurationSpaceFunctions, InitialValueAndMask)
{
	Register* temp = config->getHead();

	for (int i = 0; i < 7; i++)
		temp = temp->getRegisterNext();

	temp->setRegisterValue(temp->getRegisterInitialValue());

	EXPECT_EQ(temp->getRegisterValue(), 12);
	EXPECT_EQ(temp->getRegisterMask(), 0x3FFFFFFF);
}

/* Test for the initial value and mask of a register */
TEST(ConfigurationSpaceFunctions, InitialValueAndMask2)
{
	Register* temp = config->getHead();

	for (int i = 0; i < 5; i++)
		temp = temp->getRegisterNext();

	EXPECT_EQ(temp->getRegisterValue(), 557056);
	EXPECT_EQ(temp->getRegisterMask(), 0);
}

/* Test the setRegisterValue() function */
TEST(ConfigurationSpaceFunctions, SetRegisterValue)
{
	Register* temp = config->getHead();

	for (int i = 0; i < 9; i++)
		temp = temp->getRegisterNext();

	temp->setRegisterValue(0x259A);

	EXPECT_EQ(temp->getRegisterValue(), 9626);
}

/* Test for setReceivedMasterAbortBit() function */
TEST(ConfigurationSpaceFunctions, SetReceivedMasterAbortBit)
{
	unsigned int statusValBefore, statusValAfter;

	Register* status = config->getHead();

	status = status->getRegisterNext()->getRegisterNext()->getRegisterNext();
	statusValBefore = status->getRegisterValue();
	config->setReceivedMasterAbortBit();
	statusValAfter = status->getRegisterValue();

	EXPECT_NE(statusValBefore, statusValAfter);
}

/* Test for the initial state of the Memory Space Enable bit */
TEST(ConfigurationSpaceFunctions, IsMemorySpaceEnabled)
{
	EXPECT_EQ(config->isMemorySpaceEnabled(), 0);
}

/* Test for the state of the Memory Space Enable bit after manipulating it */
TEST(ConfigurationSpaceFunctions, IsMemorySpaceEnabled2)
{
	Register* command = config->getHead();

	command = command->getRegisterNext()->getRegisterNext();
	command->setRegisterValue((unsigned int)0x2);

	EXPECT_EQ(config->isMemorySpaceEnabled(), 1);
}

/* Test for the initial state of the IO Space Enable bit */
TEST(ConfigurationSpaceFunctions, isIOSpaceEnabled)
{
	EXPECT_EQ(config->isIOSpaceEnabled(), 0);
}

/* Test for the state of the IO Space Enable bit after manipulating it */
TEST(ConfigurationSpaceFunctions, IsIOSpaceEnabled2)
{
	Register* command = config->getHead();

	command = command->getRegisterNext()->getRegisterNext();
	command->setRegisterValue((unsigned int)0x1);

	EXPECT_EQ(config->isIOSpaceEnabled(), 1);
}