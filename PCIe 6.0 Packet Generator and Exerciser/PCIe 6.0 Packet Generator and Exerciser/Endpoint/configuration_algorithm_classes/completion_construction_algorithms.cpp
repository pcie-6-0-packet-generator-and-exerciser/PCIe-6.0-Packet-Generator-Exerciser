#include "completion_construction_algorithms.h"

CompletionConstructionAlgorithms::CompletionConstructionAlgorithms() : dataToBeReadBits(0), registerLengthInBytes(0), deviceID(0), tlp(nullptr) {}

/**
 * @brief Constructing a Completion TLP with Data Payload inside (return of a Configuration Read request)
 *
 * @return TLP -> The Constructed TLP (CplD)
 */

TLP* CompletionWithData::constructTLP()
{
	TLP* tlpHolder; // This will be the return value 

	double registerLengthInDW = (double)(registerLengthInBytes / 4);

	bitset<2> lowerAddressOHC = 0b00; // For any Completion for a Configuration Request
	bitset<5> lowerAddressHeaderBase = 0b00000;

	OHCA5::CPLStatus cplStatus = OHCA5::CPLStatus::True; // Since the Configuration Request have been handled

	int destinationSegment, completerSegment;

	/* Explicit casting to change the nonBase pointer to a ConfigNonHeaderBase pointer */
	OHCA3* ohcA3 = dynamic_cast<OHCA3*>(tlp->header->OHCVector[0]);

	/* The completer segment (my Configuration Space) is sent as a destination segment in the upcoming TLP (the Configuration
	   Space is the destination with respect to the Sender "Requester")
	   the comment of the function createCplDTlp() says about the destinationSegment: he destination segment number for routing
	   purposes  "routing for the handling device" */
	completerSegment = ohcA3->destinationSegment;

	/* The Destination segment will be set to 0 as there is only one requester */
	destinationSegment = 0;

	if (registerLengthInDW < 0)
		registerLengthInDW = 1;

	/* Explicit casting to change the nonBase pointer to a ConfigNonHeaderBase pointer */
	ConfigNonHeaderBase* configNonHeader = dynamic_cast<ConfigNonHeaderBase*>(tlp->header->nonBase);

	tlpHolder = TLP::createCplDTlp(registerLengthInDW, dataToBeReadBits, configNonHeader->tag, deviceID, registerLengthInBytes, configNonHeader->busNumber, configNonHeader->deviceNumber, 0, destinationSegment, completerSegment, lowerAddressOHC, lowerAddressHeaderBase, cplStatus);

	return tlpHolder;
}

/**
 * @brief Constructing a Completion TLP without Data Payload inside (return of a Successful Configuration Write request)
 *
 * @return TLP -> The Constructed TLP (Cpl)
 */
TLP* CompletionWithoutData::constructTLP()
{
	TLP* tlpHolder; // This will be the return value

	int destinationSegment, completerSegment;
	/* Explicit casting to change the nonBase pointer to a ConfigNonHeaderBase pointer */
	ConfigNonHeaderBase* configNonHeader = dynamic_cast<ConfigNonHeaderBase*>(tlp->header->nonBase);

	OHCA3* ohcA3 = dynamic_cast<OHCA3*>(tlp->header->OHCVector[0]);

	completerSegment = ohcA3->destinationSegment;

	/* The Destination segment will be set to 0 as there is only one requester */
	destinationSegment = 0;

	bitset<2> lowerAddressOHC = 0b00; // For any Completion for a Configuration Request
	bitset<5> lowerAddressHeaderBase = 0b00000;

	OHCA5::CPLStatus cplStatus = OHCA5::CPLStatus::True; // Since the Configuration Request have been handled

	tlpHolder = TLP::createCplTlp(configNonHeader->tag, deviceID, 0, configNonHeader->busNumber, configNonHeader->deviceNumber, 0, destinationSegment, completerSegment, lowerAddressOHC, lowerAddressHeaderBase, cplStatus);

	return tlpHolder;
}

/**
 * @brief Constructing a Completion TLP with Unsupported request (OHC-A5) (return of an Unsuccessful Read or Write request)
 *
 * @return TLP -> The Constructed TLP (CplUR)
 */
TLP* CompletionWithUR::constructTLP()
{
	TLP* tlpHolder; // This will be the return value

	int destinationSegment, completerSegment;

	/* Explicit casting to change the nonBase pointer to a ConfigNonHeaderBase pointer */
	ConfigNonHeaderBase* configNonHeader = dynamic_cast<ConfigNonHeaderBase*>(tlp->header->nonBase);

	OHCA3* ohcA3 = dynamic_cast<OHCA3*>(tlp->header->OHCVector[0]);

	completerSegment = ohcA3->destinationSegment;

	/* The Destination segment will be set to 0 as there is only one requester */
	destinationSegment = 0;

	bitset<2> lowerAddressOHC = 0b00; // For any Completion for a Configuration Request
	bitset<5> lowerAddressHeaderBase = 0b00000;

	OHCA5::CPLStatus cplStatus = OHCA5::CPLStatus::False; // Since the Configuration Request haven't been handled

	tlpHolder = TLP::createCplTlp(configNonHeader->tag, deviceID, 0, configNonHeader->busNumber, configNonHeader->deviceNumber, 0, destinationSegment, completerSegment, lowerAddressOHC, lowerAddressHeaderBase, cplStatus);

	return tlpHolder;
}

