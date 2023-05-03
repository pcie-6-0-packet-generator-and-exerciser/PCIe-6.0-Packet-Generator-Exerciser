#include "tlp.h"

int TLP::getTotalLength() {
	int OHCLength = header->OHCVector.size() * 4;
	int header_length = header->nonBase->headerSizeInBytes;
	int payload_length = header->lengthInDoubleWord * 4;
	return (OHCLength + header_length + payload_length);
}
QString TLPenumToString(TLPType value)
{
	switch (value) {
	case TLPType::MemRead32:
		return "Memory Read 32b";
	case TLPType::MemRead64:
		return "Memory Read 64b";
	case TLPType::MemWrite32:
		return "Memory Write 32b";
	case TLPType::MemWrite64:
		return "Memory Write 64b";
	case TLPType::VendorMsg:
		return "Vendor Message";
	case TLPType::ConfigRead0:
		return "Configuration Read 0";
	case TLPType::ConfigWrite0:
		return "Configuration Write 0";
	case TLPType::ConfigRead1:
		return "Configuration Read 1";
	case TLPType::ConfigWrite1:
		return "Configuration Write 1";
	case TLPType::Cpl:
		return "Completion Without Data";
	case TLPType::CplD:
		return "Completion With Data";

	}
};

boost::dynamic_bitset<> TLP::getBitRep() {
	boost::dynamic_bitset<> result(getTotalLength() * 8);
	result |= (dataPayload);
	result |= ((boost::dynamic_bitset<>((header->getBitRep())) << getTotalLength()));

	return result;
}

/**
 * @brief Creates a MemRead32 TLP* with the given parameters.
 *
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP* header.
 * @param address The 32-bit address to read from.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @return A TLP* object representing the MemRead32 TLP.
 */
TLP*  TLP::createMemRead32Tlp(int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4> lastDWBE) {
	TLP*  memRead32Tlp = new TLP;
	memRead32Tlp->header->OHCVector.push_back(new OHCA1(firstDWBE, lastDWBE));
	memRead32Tlp->header->TLPtype = TLPType::MemRead32;
	memRead32Tlp->header->lengthInDoubleWord = 0;

		memRead32Tlp->header->nonBase = new AddressRouting32Bit(requesterId, tag, address);

	// clears out the data payload
	memRead32Tlp->dataPayload.reset();
	memRead32Tlp->creditConsumedType = Dllp::CreditType::NP;
	memRead32Tlp->headerConsumption = 1;
	memRead32Tlp->dataConsumption = 0;

	return memRead32Tlp;
}

/**
 * @brief Creates a MemWrite32 TLP* with the given parameters.
 *
 * @param dataPayloadLengthInDW The length of the data payload in bytes.
 * @param dataPayload The data payload as a string of bits.
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP* header.
 * @param address The 32-bit address to write to.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @return A TLP* object representing the MemWrite32 TLP.
 */
TLP*  TLP::createMemWrite32Tlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4>lastDWBE) {
	TLP*  memWrite32Tlp = new TLP;
	memWrite32Tlp->header->OHCVector.push_back(new OHCA1(firstDWBE, lastDWBE));
	memWrite32Tlp->header->TLPtype = TLPType::MemWrite32;
	memWrite32Tlp->header->lengthInDoubleWord = dataPayloadLengthInDW;
	memWrite32Tlp->header->nonBase = new AddressRouting32Bit(requesterId, tag, address);

	memWrite32Tlp->dataPayload = dataPayload;
	memWrite32Tlp->creditConsumedType = Dllp::CreditType::P;
	memWrite32Tlp->headerConsumption = 1;
	memWrite32Tlp->dataConsumption = ceil(dataPayloadLengthInDW / FC_UNIT_SIZE);

	return memWrite32Tlp;
}
/**
 * @brief Creates a MemRead64 TLP* with the given parameters.
 *
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP* header.
 * @param address The 64-bit address to read from.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @return A TLP* object representing the MemRead64 TLP.
 */
TLP*  TLP::createMemRead64Tlp(int requesterId, int tag, long long address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE) {
	TLP*  memRead64Tlp = new TLP;
	memRead64Tlp->header->OHCVector.push_back(new OHCA1(firstDWBE, lastDWBE));
	memRead64Tlp->header->TLPtype = TLPType::MemRead64;
	memRead64Tlp->header->lengthInDoubleWord = 0;
	memRead64Tlp->header->nonBase = new AddressRouting64Bit(requesterId, tag, address);;

	memRead64Tlp->dataPayload.reset();
	memRead64Tlp->creditConsumedType = Dllp::CreditType::NP;
	memRead64Tlp->headerConsumption = 1;
	memRead64Tlp->dataConsumption = 0;

	return memRead64Tlp;
}


/**
 * @brief Create a TLP* for 64-bit memory write
 *
 * @param dataPayloadLengthInDW Length of the data payload
 * @param dataPayload Data payload string
 * @param requesterId ID of the requester
 * @param tag Tag to associate with the TLP
 * @param address Address to write to
 * @param firstDWBE First DWBE array for OHC-A1
 * @param lastDWBE Last DWBE array for OHC-A1
 *
 * @return TLP* for 64-bit memory write
 */
TLP* TLP::createMemWrite64Tlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, long long address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE) {
	TLP* memWrite64Tlp = new TLP;
	memWrite64Tlp->header->OHCVector.push_back(new OHCA1(firstDWBE, lastDWBE));
	memWrite64Tlp->header->TLPtype = TLPType::MemWrite64;
	memWrite64Tlp->header->lengthInDoubleWord = dataPayloadLengthInDW;
	memWrite64Tlp->header->nonBase = new AddressRouting64Bit(requesterId, tag, address);

	memWrite64Tlp->dataPayload = dataPayload;
	memWrite64Tlp->creditConsumedType = Dllp::CreditType::P;
	memWrite64Tlp->headerConsumption = 1;
	memWrite64Tlp->dataConsumption = ceil(dataPayloadLengthInDW / FC_UNIT_SIZE);

	return memWrite64Tlp;
}
/**
 * @brief Creates a ConfigRead0 TLP* with the given parameters.
 *
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP* header.
 * @param registerNumber The register number to read from.
 * @param deviceNumber The device number of the target device.
 * @param busNumber The bus number of the target device.
 * @param functionNumber The function number of the target device.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @param destinationSegment The destination segment number for routing purposes.
 * @return A TLP* object representing the ConfigRead0 TLP.
 */
TLP* TLP::createConfigRead0Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment) {
	TLP* configRead0Tlp = new TLP;
	configRead0Tlp->header->OHCVector.push_back(new OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configRead0Tlp->header->TLPtype = TLPType::ConfigRead0;
	configRead0Tlp->header->lengthInDoubleWord = 0;
	configRead0Tlp->header->nonBase = new ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);

	configRead0Tlp->dataPayload.reset();
	configRead0Tlp->creditConsumedType = Dllp::CreditType::NP;
	configRead0Tlp->headerConsumption = 1;
	configRead0Tlp->dataConsumption = 0;

	return configRead0Tlp;
}
/**
 * @breif Creates a ConfigWrite0 TLP* with the given parameters.
 *
 * @param dataPayloadLengthInDW The length of the data payload in bytes.
 * @param dataPayload The data payload as a string of bits.
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP* header.
 * @param registerNumber The register number to write to.
 * @param deviceNumber The device number of the target device.
 * @param busNumber The bus number of the target device.
 * @param functionNumber The function number of the target device.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @param destinationSegment The destination segment number for routing purposes.
 * @return A TLP* object representing the ConfigWrite0 TLP.
 */
TLP* TLP::createConfigWrite0Tlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment) {
	TLP* configWrite0Tlp = new TLP;
	configWrite0Tlp->header->OHCVector.push_back(new OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configWrite0Tlp->header->TLPtype = TLPType::ConfigWrite0;
	configWrite0Tlp->header->lengthInDoubleWord = dataPayloadLengthInDW;
	configWrite0Tlp->header->nonBase = new ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);

	configWrite0Tlp->dataPayload = dataPayload;
	configWrite0Tlp->creditConsumedType = Dllp::CreditType::NP;
	configWrite0Tlp->headerConsumption = 1;
	configWrite0Tlp->dataConsumption = ceil(dataPayloadLengthInDW / FC_UNIT_SIZE);

	return configWrite0Tlp;
}

/**
 * @brief Creates a ConfigRead1 TLP* with the given parameters.
 *
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP* header.
 * @param registerNumber The register number to read from.
 * @param deviceNumber The device number of the target device.
 * @param busNumber The bus number of the target device.
 * @param functionNumber The function number of the target device.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @param destinationSegment The destination segment number for routing purposes.
 * @return A TLP* object representing the ConfigRead1 TLP.
 */
TLP* TLP::createConfigRead1Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment) {
	TLP* configRead1Tlp = new TLP;
	configRead1Tlp->header->OHCVector.push_back(new OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configRead1Tlp->header->TLPtype = TLPType::ConfigRead1;
	configRead1Tlp->header->lengthInDoubleWord = 0;
	configRead1Tlp->header->nonBase = new ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);

	configRead1Tlp->dataPayload.reset();
	configRead1Tlp->creditConsumedType = Dllp::CreditType::NP;
	configRead1Tlp->headerConsumption = 1;
	configRead1Tlp->dataConsumption = 0;

	return configRead1Tlp;
}
/**
* @brief Creates a ConfigWrite1 TLP* with the given parameters.
*
* @param dataPayloadLengthInDW The length of the data payload in bytes.
* @param dataPayload The data payload as a string of bits.
* @param requesterId The requester ID of the TLP.
* @param tag The tag field of the TLP.
* @param registerNumber The register number to write to.
* @param deviceNumber The device number to write to.
* @param functionNumber The function number to write to.
* @param busNumber The bus number to write to.
* @param lastDWBE An array of four integers representing the last DWBE field of the OHCA3 extension header.
* @param destinationSegment The destination segment field of the OHCA3 extension header.
* @return A TLP* object representing the ConfigWrite1 TLP.
*/
TLP* TLP::createConfigWrite1Tlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment) {
	TLP* configWrite1Tlp = new TLP;
	configWrite1Tlp->header->OHCVector.push_back(new OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configWrite1Tlp->header->TLPtype = TLPType::ConfigWrite1;
	configWrite1Tlp->header->lengthInDoubleWord = dataPayloadLengthInDW;
	configWrite1Tlp->header->nonBase = new ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);

	configWrite1Tlp->dataPayload = dataPayload;
	configWrite1Tlp->creditConsumedType = Dllp::CreditType::NP;
	configWrite1Tlp->headerConsumption = 1;
	configWrite1Tlp->dataConsumption = ceil(dataPayloadLengthInDW / FC_UNIT_SIZE);

	return configWrite1Tlp;
}
/**
 * @brief Creates a Cpl TLP* with the given parameters
 *
 * @param requesterId The requester ID of the original TLP
 * @param tag The tag field of the original TLP
 * @param completerId The completer ID of the Cpl TLP
 * @param byteCount The number of bytes transferred by the Cpl TLP
 * @param busNumber The bus number of the destination device
 * @param deviceNumber The device number of the destination device
 * @param functionNumber The function number of the destination device
 * @param lowerAddress The lower address field of the Cpl TLP
 * @param destinationSegment The destination segment field of the OHCA5 extension header
 * @param completerSegment The completer segment field of the OHCA5 extension header
 * @param lowerAddressArr An array of two integers representing the lower address fields of the OHCA5 extension header
 * @param cplStatus The completion status field of the OHCA5 extension header
 * @return A TLP* object representing the Cpl TLP
 */
TLP* TLP::createCplTlp(int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddress, OHCA5::CPLStatus cplStatus) {
	TLP* cplTlp = new TLP;
	cplTlp->header->OHCVector.push_back(new OHCA5(destinationSegment, completerSegment, lowerAddress, cplStatus));
	cplTlp->header->TLPtype = TLPType::Cpl;
	cplTlp->header->lengthInDoubleWord = 0;
	cplTlp->header->nonBase = new CompletionNonHeaderBase(requesterId, tag, completerId, byteCount, busNumber, deviceNumber, functionNumber, lowerAddress.to_ulong());

	cplTlp->dataPayload.reset();
	cplTlp->creditConsumedType = Dllp::CreditType::Cpl;
	cplTlp->headerConsumption = 1;
	cplTlp->dataConsumption = 0;

	return cplTlp;
}
/**
 * @brief Creates a CplD TLP* with the given parameters
 *
 * @param dataPayloadLengthInDW The length of the data payload in bytes
 * @param dataPayload The data payload as a string of bits
 * @param requesterId The requester ID of the original TLP
 * @param tag The tag field of the original TLP
 * @param completerId The completer ID of the CplD TLP
 * @param byteCount The number of bytes transferred by the CplD TLP
 * @param busNumber The bus number of the destination device
 * @param deviceNumber The device number of the destination device
 * @param functionNumber The function number of the destination device
 * @param lowerAddress The lower address field of the CplD TLP
 * @param destinationSegment The destination segment field of the OHCA5 extension header
 * @param completerSegment The completer segment field of the OHCA5 extension header
 * @param lowerAddressArr An array of two integers representing the lower address fields of the OHCA5 extension header
 * @param cplStatus The completion status field of the OHCA5 extension header
 * @return A TLP* object representing the CplD TLP* with the specified parameters and fields
 */

TLP* TLP::createCplDTlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddress, OHCA5::CPLStatus cplStatus) {
	TLP* cplDTlp = new TLP;
	cplDTlp->header->OHCVector.push_back(new OHCA5(destinationSegment, completerSegment, lowerAddress, cplStatus));
	cplDTlp->header->TLPtype = TLPType::CplD;
	cplDTlp->header->lengthInDoubleWord = dataPayloadLengthInDW;
	cplDTlp->header->nonBase = new CompletionNonHeaderBase(requesterId, tag, completerId, byteCount, busNumber, deviceNumber, functionNumber, lowerAddress.to_ulong());

	cplDTlp->dataPayload = dataPayload;
	cplDTlp->creditConsumedType = Dllp::CreditType::Cpl;
	cplDTlp->headerConsumption = 1;
	cplDTlp->dataConsumption = ceil(dataPayloadLengthInDW / FC_UNIT_SIZE);

	return cplDTlp;
}
/**
 * @brief Creates a VendorMsg TLP* with the given parameters
 * @param dataPayloadLengthInDW The length of the data payload in bytes
 * @param dataPayload The data payload as a string of bits
 * @param requesterId The requester ID of the VendorMsg TLP
 * @param messageCode The message code field of the VendorMsg TLP
 * @param destinationSegment The destination segment field of the OHCA4 extension header
 * @return A TLP* object representing the VendorMsg TLP* with the specified parameters and fields
 */
TLP* TLP::createVendorMsgTlp(int dataPayloadLengthInDW, boost::dynamic_bitset<> dataPayload, int requesterId, int messageCode, int destinationSegment) {
	TLP* vendorMsg = new TLP;
	vendorMsg->header->OHCVector.push_back(new OHCA4(destinationSegment));
	vendorMsg->header->TLPtype = TLPType::VendorMsg;
	vendorMsg->header->lengthInDoubleWord = dataPayloadLengthInDW;
	vendorMsg->header->nonBase = new MessageNonHeaderBase(requesterId, messageCode);

	vendorMsg->dataPayload = dataPayload;
	vendorMsg->creditConsumedType = Dllp::CreditType::P;
	vendorMsg->headerConsumption = 1;
	vendorMsg->dataConsumption = ceil(dataPayloadLengthInDW / FC_UNIT_SIZE);

	return vendorMsg;
}
