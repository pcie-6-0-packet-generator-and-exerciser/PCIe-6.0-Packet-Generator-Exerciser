#include "./tlp.h"

/**
 * @brief Creates a MemRead32 TLP with the given parameters.
 * 
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP header.
 * @param address The 32-bit address to read from.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @return A TLP object representing the MemRead32 TLP.
 */
TLP TLP::createMemRead32Tlp(int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4> lastDWBE) {
	TLP memRead32Tlp;
	memRead32Tlp.header.OHCVector.push_back(new OHCA1(firstDWBE, lastDWBE));
	memRead32Tlp.header.TLPtype = TLPType::MemRead32;
	memRead32Tlp.header.lengthInDoubleWord = 0;

	// this is done because & requires a Ivalue 
	auto nonBase = AddressRouting32Bit(requesterId, tag, address);
	memRead32Tlp.header.nonBase = &nonBase;

	// clears out the data payload
	memRead32Tlp.dataPayload.reset();
	memRead32Tlp.creditConsumedType = Dllp::CreditType::NP;
	memRead32Tlp.headerConsumption = 1;
	memRead32Tlp.dataConsumption = 0;

	return memRead32Tlp;
}

/**
 * @brief Creates a MemWrite32 TLP with the given parameters.
 * 
 * @param dataPayloadLength The length of the data payload in bytes.
 * @param dataPayload The data payload as a string of bits.
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP header.
 * @param address The 32-bit address to write to.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @return A TLP object representing the MemWrite32 TLP.
 */
TLP TLP::createMemWrite32Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int address, std::bitset<4>  firstDWBE, std::bitset<4>lastDWBE) {
	TLP memWrite32Tlp;
	memWrite32Tlp.header.OHCVector.push_back(new OHCA1(firstDWBE, lastDWBE));
	memWrite32Tlp.header.TLPtype = TLPType::MemWrite32;
	memWrite32Tlp.header.lengthInDoubleWord = dataPayloadLength;

	// this is done because & requires a Ivalue 
	auto nonBase = AddressRouting32Bit(requesterId, tag, address);
	memWrite32Tlp.header.nonBase = &nonBase;

	memWrite32Tlp.dataPayload = boost::dynamic_bitset<>(dataPayload);
	memWrite32Tlp.creditConsumedType = Dllp::CreditType::P;
	memWrite32Tlp.headerConsumption = 1;
	memWrite32Tlp.dataConsumption = (int)(dataPayloadLength / FC_UNIT_SIZE);

	return memWrite32Tlp;
}
/**
 * @brief Creates a MemRead64 TLP with the given parameters.
 * 
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP header.
 * @param address The 64-bit address to read from.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @return A TLP object representing the MemRead64 TLP.
 */
TLP TLP::createMemRead64Tlp(int requesterId, int tag, long long address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE) {
	TLP memRead64Tlp;
	memRead64Tlp.header.OHCVector.push_back(new OHCA1(firstDWBE, lastDWBE));
	memRead64Tlp.header.TLPtype = TLPType::MemRead64;
	memRead64Tlp.header.lengthInDoubleWord = 0;

	// this is done because & requires a Ivalue
	auto nonBase = AddressRouting64Bit(requesterId, tag, address);;
	memRead64Tlp.header.nonBase = &nonBase;

	memRead64Tlp.dataPayload.reset();
	memRead64Tlp.creditConsumedType = Dllp::CreditType::NP;
	memRead64Tlp.headerConsumption = 1;
	memRead64Tlp.dataConsumption = 0;

	return memRead64Tlp;
}


/**
 * @brief Create a TLP for 64-bit memory write
 *
 * @param dataPayloadLength Length of the data payload
 * @param dataPayload Data payload string
 * @param requesterId ID of the requester
 * @param tag Tag to associate with the TLP
 * @param address Address to write to
 * @param firstDWBE First DWBE array for OHC-A1
 * @param lastDWBE Last DWBE array for OHC-A1
 *
 * @return TLP for 64-bit memory write
 */
TLP TLP::createMemWrite64Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, long long address, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE) {
	TLP memWrite64Tlp;
	memWrite64Tlp.header.OHCVector.push_back(new OHCA1(firstDWBE, lastDWBE));
	memWrite64Tlp.header.TLPtype = TLPType::MemWrite64;
	memWrite64Tlp.header.lengthInDoubleWord = dataPayloadLength;

	// this is done because & requires a Ivalue
	auto nonBase = AddressRouting64Bit(requesterId, tag, address);
	memWrite64Tlp.header.nonBase = &nonBase;

	memWrite64Tlp.dataPayload = boost::dynamic_bitset<>(dataPayload);
	memWrite64Tlp.creditConsumedType = Dllp::CreditType::P;
	memWrite64Tlp.headerConsumption = 1;
	memWrite64Tlp.dataConsumption = (int)(dataPayloadLength / FC_UNIT_SIZE);

	return memWrite64Tlp;
}
/**
 * @brief Creates a ConfigRead0 TLP with the given parameters.
 * 
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP header.
 * @param registerNumber The register number to read from.
 * @param deviceNumber The device number of the target device.
 * @param busNumber The bus number of the target device.
 * @param functionNumber The function number of the target device.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @param destinationSegment The destination segment number for routing purposes.
 * @return A TLP object representing the ConfigRead0 TLP.
 */
TLP TLP::createConfigRead0Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment) {
	TLP configRead0Tlp;
	configRead0Tlp.header.OHCVector.push_back(new OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configRead0Tlp.header.TLPtype = TLPType::ConfigRead0;
	configRead0Tlp.header.lengthInDoubleWord = 0;

	// this is done because & requires a Ivalue 
	auto nonBase = ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);
	configRead0Tlp.header.nonBase = &nonBase;

	configRead0Tlp.dataPayload.reset();
	configRead0Tlp.creditConsumedType = Dllp::CreditType::NP;
	configRead0Tlp.headerConsumption = 1;
	configRead0Tlp.dataConsumption = 0;

	return configRead0Tlp;
}
/**
 * @breif Creates a ConfigWrite0 TLP with the given parameters.
 * 
 * @param dataPayloadLength The length of the data payload in bytes.
 * @param dataPayload The data payload as a string of bits.
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP header.
 * @param registerNumber The register number to write to.
 * @param deviceNumber The device number of the target device.
 * @param busNumber The bus number of the target device.
 * @param functionNumber The function number of the target device.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @param destinationSegment The destination segment number for routing purposes.
 * @return A TLP object representing the ConfigWrite0 TLP.
 */
TLP TLP::createConfigWrite0Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment) {
	TLP configWrite0Tlp;
	configWrite0Tlp.header.OHCVector.push_back(new OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configWrite0Tlp.header.TLPtype = TLPType::ConfigWrite0;
	configWrite0Tlp.header.lengthInDoubleWord = dataPayloadLength;

	// this is done because & requires a Ivalue 
	auto nonBase = ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);
	configWrite0Tlp.header.nonBase = &nonBase;

	configWrite0Tlp.dataPayload = boost::dynamic_bitset<>(dataPayload);
	configWrite0Tlp.creditConsumedType = Dllp::CreditType::NP;
	configWrite0Tlp.headerConsumption = 1;
	configWrite0Tlp.dataConsumption = (int)(dataPayloadLength / FC_UNIT_SIZE);

	return configWrite0Tlp;
}

/**
 * @brief Creates a ConfigRead1 TLP with the given parameters.
 * 
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP header.
 * @param registerNumber The register number to read from.
 * @param deviceNumber The device number of the target device.
 * @param busNumber The bus number of the target device.
 * @param functionNumber The function number of the target device.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @param destinationSegment The destination segment number for routing purposes.
 * @return A TLP object representing the ConfigRead1 TLP.
 */
TLP TLP::createConfigRead1Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment) {
	TLP configRead1Tlp;
	configRead1Tlp.header.OHCVector.push_back(new OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configRead1Tlp.header.TLPtype = TLPType::ConfigRead1;
	configRead1Tlp.header.lengthInDoubleWord = 0;

	// this is done because & requires a Ivalue 
	auto nonBase = ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);
	configRead1Tlp.header.nonBase = &nonBase;

	// clears out the data payload
	configRead1Tlp.dataPayload.reset();
	configRead1Tlp.creditConsumedType = Dllp::CreditType::NP;
	configRead1Tlp.headerConsumption = 1;
	configRead1Tlp.dataConsumption = 0;

	return configRead1Tlp;
}
/**
* @brief Creates a ConfigWrite1 TLP with the given parameters.
* 
* @param dataPayloadLength The length of the data payload in bytes.
* @param dataPayload The data payload as a string of bits.
* @param requesterId The requester ID of the TLP.
* @param tag The tag field of the TLP.
* @param registerNumber The register number to write to.
* @param deviceNumber The device number to write to.
* @param functionNumber The function number to write to.
* @param busNumber The bus number to write to.
* @param lastDWBE An array of four integers representing the last DWBE field of the OHCA3 extension header.
* @param destinationSegment The destination segment field of the OHCA3 extension header.
* @return A TLP object representing the ConfigWrite1 TLP.
*/
TLP TLP::createConfigWrite1Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, std::bitset<4> firstDWBE, std::bitset<4> lastDWBE, int destinationSegment) {
	TLP configWrite1Tlp;
	configWrite1Tlp.header.OHCVector.push_back(new OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configWrite1Tlp.header.TLPtype = TLPType::ConfigWrite1;
	configWrite1Tlp.header.lengthInDoubleWord = dataPayloadLength;

	// this is done because & requires a Ivalue 
	auto nonBase = ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);
	configWrite1Tlp.header.nonBase = &nonBase;

	configWrite1Tlp.dataPayload = boost::dynamic_bitset<>(dataPayload);
	configWrite1Tlp.creditConsumedType = Dllp::CreditType::NP;
	configWrite1Tlp.headerConsumption = 1;
	configWrite1Tlp.dataConsumption = (int)(dataPayloadLength / FC_UNIT_SIZE);

	return configWrite1Tlp;
}
/**
 * @brief Creates a Cpl TLP with the given parameters
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
 * @return A TLP object representing the Cpl TLP
 */
TLP TLP::createCplTlp(int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddress, OHCA5::CPLStatus cplStatus) {
	TLP cplTlp;
	cplTlp.header.OHCVector.push_back(new OHCA5(destinationSegment, completerSegment, lowerAddress, cplStatus));
	cplTlp.header.TLPtype = TLPType::Cpl;
	cplTlp.header.lengthInDoubleWord = 0;
	// this is done because & requires a Ivalue 
	auto nonBase = CompletionNonHeaderBase(requesterId, tag, completerId, byteCount, busNumber, deviceNumber, functionNumber, lowerAddress.to_ulong());
	cplTlp.header.nonBase = &nonBase;

	// clears out the data payload
	cplTlp.dataPayload.reset();
	cplTlp.creditConsumedType = Dllp::CreditType::Cpl;
	cplTlp.headerConsumption = 1;
	cplTlp.dataConsumption = 0;

	return cplTlp;
}
/**
 * @brief Creates a CplD TLP with the given parameters
 * 
 * @param dataPayloadLength The length of the data payload in bytes
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
 * @return A TLP object representing the CplD TLP with the specified parameters and fields
 */

TLP TLP::createCplDTlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int destinationSegment, int completerSegment, std::bitset<2> lowerAddress, OHCA5::CPLStatus cplStatus) {
	TLP cplDTlp;
	cplDTlp.header.OHCVector.push_back(new OHCA5(destinationSegment, completerSegment, lowerAddress, cplStatus));
	cplDTlp.header.TLPtype = TLPType::CplD;
	cplDTlp.header.lengthInDoubleWord = dataPayloadLength;

	// this is done because & requires a Ivalue 
	auto nonBase = CompletionNonHeaderBase(requesterId, tag, completerId, byteCount, busNumber, deviceNumber, functionNumber, lowerAddress.to_ulong());
	cplDTlp.header.nonBase = &nonBase;

	cplDTlp.dataPayload = boost::dynamic_bitset<>(dataPayload);
	cplDTlp.creditConsumedType = Dllp::CreditType::Cpl;
	cplDTlp.headerConsumption = 1;
	cplDTlp.dataConsumption = (int)(dataPayloadLength / FC_UNIT_SIZE);

	return cplDTlp;
}
/**
 * @brief Creates a VendorMsg TLP with the given parameters
 * @param dataPayloadLength The length of the data payload in bytes
 * @param dataPayload The data payload as a string of bits
 * @param requesterId The requester ID of the VendorMsg TLP
 * @param messageCode The message code field of the VendorMsg TLP
 * @param destinationSegment The destination segment field of the OHCA4 extension header
 * @return A TLP object representing the VendorMsg TLP with the specified parameters and fields
 */
TLP TLP::createVendorMsgTlp(int dataPayloadLength, std::string dataPayload, int requesterId, int messageCode, int destinationSegment) {
	TLP vendorMsg;
	vendorMsg.header.OHCVector.push_back(new OHCA4(destinationSegment));
	vendorMsg.header.TLPtype = TLPType::VendorMsg;
	vendorMsg.header.lengthInDoubleWord = dataPayloadLength;

	// this is done because & requires a Ivalue 
	auto nonBase = MessageNonHeaderBase(requesterId, messageCode);
	vendorMsg.header.nonBase = &nonBase;

	vendorMsg.dataPayload = boost::dynamic_bitset<>(dataPayload);
	vendorMsg.creditConsumedType = Dllp::CreditType::P;
	vendorMsg.headerConsumption = 1;
	vendorMsg.dataConsumption = (int)(dataPayloadLength / FC_UNIT_SIZE);

	return vendorMsg;
}