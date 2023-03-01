#include "./tlp.h"
/**
 * @brief Creates a MemRead32 TLP with the given parameters.
 * 
 * @param requesterId The requester ID of the TLP.
 * @param tag The tag field of the TLP header.
 * @param address The 32-bit address to read from.
 * @param firstDWBE An array of four integers indicating which bytes are enabled in the first data word (DW).
 * @param lastDWBE An array of four integers indicating which bytes are enabled in the last DW.
 * @return A Tlp object representing the MemRead32 TLP.
 */
Tlp Tlp::createMemRead32Tlp(int requesterId, int tag, int address, int  firstDWBE[4], int  lastDWBE[4]) {
	Tlp memRead32Tlp;
	memRead32Tlp.header.ohcs.push_back(OHCA1(firstDWBE, lastDWBE));
	memRead32Tlp.header.type = TlpHeader::TlpType::MemRead32;
	memRead32Tlp.header.length = 0;
	memRead32Tlp.header.nonBase = AddressRouting32bit(requesterId, tag, address);

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
 * @return A Tlp object representing the MemWrite32 TLP.
 */
Tlp Tlp::createMemWrite32Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int address, int  firstDWBE[4], int  lastDWBE[4]) {
	Tlp memWrite32Tlp;
	memWrite32Tlp.header.ohcs.push_back(OHCA1(firstDWBE, lastDWBE));
	memWrite32Tlp.header.type = TlpHeader::TlpType::MemWrite32;
	memWrite32Tlp.header.length = dataPayloadLength;
	memWrite32Tlp.header.nonBase = AddressRouting32bit(requesterId, tag, address);

	memWrite32Tlp.dataPayload = std::bitset<MAX_DATA_PAYLOAD_LENGTH>(dataPayload);
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
 * @return A Tlp object representing the MemRead64 TLP.
 */
Tlp Tlp::createMemRead64Tlp(int requesterId, int tag, long long address, int  firstDWBE[4], int  lastDWBE[4]) {
	Tlp memRead64Tlp;
	memRead64Tlp.header.ohcs.push_back(OHCA1(firstDWBE, lastDWBE));
	memRead64Tlp.header.type = TlpHeader::TlpType::MemRead64;
	memRead64Tlp.header.length = 0;
	memRead64Tlp.header.nonBase = AddressRouting64bit(requesterId, tag, address);

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
Tlp Tlp::createMemWrite64Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, long long address, int  firstDWBE[4], int  lastDWBE[4]) {
	Tlp memWrite64Tlp;
	memWrite64Tlp.header.ohcs.push_back(OHCA1(firstDWBE, lastDWBE));
	memWrite64Tlp.header.type = TlpHeader::TlpType::MemWrite64;
	memWrite64Tlp.header.length = dataPayloadLength;
	memWrite64Tlp.header.nonBase = AddressRouting64bit(requesterId, tag, address);

	memWrite64Tlp.dataPayload = std::bitset<MAX_DATA_PAYLOAD_LENGTH>(dataPayload);
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
 * @return A Tlp object representing the ConfigRead0 TLP.
 */
Tlp Tlp::createConfigRead0Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, int  firstDWBE[4], int  lastDWBE[4], int destinationSegment) {
	Tlp configRead0Tlp;
	configRead0Tlp.header.ohcs.push_back(OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configRead0Tlp.header.type = TlpHeader::TlpType::ConfigRead0;
	configRead0Tlp.header.length = 0;
	configRead0Tlp.header.nonBase = ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);

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
 * @return A Tlp object representing the ConfigWrite0 TLP.
 */
Tlp Tlp::createConfigWrite0Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, int  firstDWBE[4], int  lastDWBE[4], int destinationSegment) {
	Tlp configWrite0Tlp;
	configWrite0Tlp.header.ohcs.push_back(OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configWrite0Tlp.header.type = TlpHeader::TlpType::ConfigWrite0;
	configWrite0Tlp.header.length = dataPayloadLength;
	configWrite0Tlp.header.nonBase = ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);

	configWrite0Tlp.dataPayload = std::bitset<MAX_DATA_PAYLOAD_LENGTH>(dataPayload);
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
 * @return A Tlp object representing the ConfigRead1 TLP.
 */
Tlp Tlp::createConfigRead1Tlp(int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, int  firstDWBE[4], int  lastDWBE[4], int destinationSegment) {
	Tlp configRead1Tlp;
	configRead1Tlp.header.ohcs.push_back(OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configRead1Tlp.header.type = TlpHeader::TlpType::ConfigRead1;
	configRead1Tlp.header.length = 0;
	configRead1Tlp.header.nonBase = ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);

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
* @return A Tlp object representing the ConfigWrite1 TLP.
*/
Tlp Tlp::createConfigWrite1Tlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int registerNumber, int deviceNumber, int busNumber, int functionNumber, int  firstDWBE[4], int  lastDWBE[4], int destinationSegment) {
	Tlp configWrite1Tlp;
	configWrite1Tlp.header.ohcs.push_back(OHCA3(firstDWBE, lastDWBE, destinationSegment));
	configWrite1Tlp.header.type = TlpHeader::TlpType::ConfigWrite1;
	configWrite1Tlp.header.length = dataPayloadLength;
	configWrite1Tlp.header.nonBase = ConfigNonHeaderBase(requesterId, tag, registerNumber, busNumber, deviceNumber, functionNumber);

	configWrite1Tlp.dataPayload = std::bitset<MAX_DATA_PAYLOAD_LENGTH>(dataPayload);
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
 * @return A Tlp object representing the Cpl TLP 
 */
Tlp Tlp::createCplTlp(int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int lowerAddress, int destinationSegment, int completerSegment, int lowerAddressArr[2], Tlp::CplStatus cplStatus) {
	Tlp cplTlp;
	cplTlp.header.ohcs.push_back(OHCA5(destinationSegment, completerSegment, lowerAddressArr, cplStatus));
	cplTlp.header.type = TlpHeader::TlpType::Cpl;
	cplTlp.header.length = 0;
	cplTlp.header.nonBase = CompletionNonHeaderBase(requesterId, tag, completerId, byteCount, busNumber, deviceNumber, functionNumber, lowerAddress);

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
 * @return A Tlp object representing the CplD TLP with the specified parameters and fields
 */

Tlp Tlp::createCplDTlp(int dataPayloadLength, std::string dataPayload, int requesterId, int tag, int completerId, long byteCount, int busNumber, int deviceNumber, int functionNumber, int lowerAddress, int destinationSegment, int completerSegment, int lowerAddressArr[2], Tlp::CplStatus cplStatus) {
	Tlp cplDTlp;
	cplDTlp.header.ohcs.push_back(OHCA5(destinationSegment, completerSegment, lowerAddressArr, cplStatus));
	cplDTlp.header.type = TlpHeader::TlpType::CplD;
	cplDTlp.header.length = dataPayloadLength;
	cplDTlp.header.nonBase = CompletionNonHeaderBase(requesterId, tag, completerId, byteCount, busNumber, deviceNumber, functionNumber, lowerAddress);

	cplDTlp.dataPayload = std::bitset<MAX_DATA_PAYLOAD_LENGTH>(dataPayload);
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
 * @return A Tlp object representing the VendorMsg TLP with the specified parameters and fields
 */
Tlp Tlp::createVendorMsgTlp(int dataPayloadLength, std::string dataPayload, int requesterId, int messageCode, int destinationSegment) {
	Tlp vendorMsg;
	vendorMsg.header.ohcs.push_back(OHCA4(destinationSegment));
	vendorMsg.header.type = TlpHeader::TlpType::VendorMsg;
	vendorMsg.header.length = dataPayloadLength;
	vendorMsg.header.nonBase = MessageNonHeaderBase(requesterId, messageCode);

	vendorMsg.dataPayload = std::bitset<MAX_DATA_PAYLOAD_LENGTH>(dataPayload);
	vendorMsg.creditConsumedType = Dllp::CreditType::P;
	vendorMsg.headerConsumption = 1;
	vendorMsg.dataConsumption = (int)(dataPayloadLength / FC_UNIT_SIZE);

	return vendorMsg;
}