#include "configuration_controller.h"

/**
 * @brief Construct a new Configuration Controller and initializing some needed pointers to be used inside it 
 */
ConfigurationController::ConfigurationController()
{
    configuration = ConfigurationSpace::constructConfigurationSpace();
    capability =  PCIECapability::constructPCIECapability();

    handler = make_shared<ConfigurationRequestHandler>(configuration, capability);
    tlpConstructor = make_shared<TLPConstructor>();

    cplD = make_shared<CompletionWithData>();
    cpl = make_shared<CompletionWithoutData>();
    cplUR = make_shared<CompletionWithUR>();
}

/**
 * @brief Getting the Register number which we need to apply the Configuration request on
 * 
 * @param tlp -> The TLP coming to be handled
 * @return int -> The Register Number to apply the Configuration request on
 */
int ConfigurationController::getRegisterNumber(TLP * tlp)
{
    /* Explicit casting to change the nonBase pointer to a ConfigNonHeaderBase pointer */
    ConfigNonHeaderBase * configNonHeader = dynamic_cast<ConfigNonHeaderBase*>(tlp->header->nonBase);

    return configNonHeader->registerNumber;
}

/**
 * @brief Knowing whether the Configuration request carries a valid Register number to be handled or not
 *        Also notice that we have 23 Registers numbered from 0 -> 22
 * 
 * @param registerNumber -> Taken from the coming TLP
 * @return int -> 1 for valid Register number, 0 otherwise
 */
int ConfigurationController::isValidRegisterNumber(int registerNumber)
{
    /* This number will be changed when the PCIE Capability Structure ends */
    if(registerNumber <= 22)
        return 1;
    
    return 0;
}

/**
 * @brief Identifying the Configuration request type
 * 
 * @param tlp -> The TLP coming to be handled
 * @return TLPType -> Configuration Read, or Write
 */
TLPType ConfigurationController::getTLPType(TLP * tlp)
{
    return tlp->header->TLPtype;
}

/**
 * @brief Getting the Data Payload (to be written in a Register) from the coming TLP in case of a Configuration Write request
 * 
 * @param tlp -> The TLP coming to be handled
 * @return unsigned int -> Data inside the TLP
 */
unsigned int ConfigurationController::getTLPData(TLP * tlp)
{
    boost::dynamic_bitset<> dataPayloadBits;

    unsigned int dataPayloadUint;

    dataPayloadBits = tlp -> dataPayload;

    dataPayloadUint = convertToUnsignedInt(dataPayloadBits);

    return dataPayloadUint;
}

/**
 * @brief Converting the coming data inside the TLP from dynamic_bitset to unsigned int
 * 
 * @param bits -> Data Payload inside the TLP
 * @return unsigned int -> the data converted into unsigned int
 */
unsigned int ConfigurationController::convertToUnsignedInt(boost::dynamic_bitset<> bits)
{
    unsigned int uintValue = static_cast<unsigned int>(bits.to_ulong());

    return uintValue;
}

/**
 * @brief Doing the exact opposite of the above
 * 
 * @param uintValue 
 * @return boost::dynamic_bitset<> 
 */
boost::dynamic_bitset<> ConfigurationController::convertToBitSet(unsigned int uintValue)
{
    boost::dynamic_bitset<> bits(uintValue);

    return bits;
}

/**
 * @brief Handling the coming Configuration request through:
 * 
 * Getting Register Number -> Checking its validness -> if it's not valid, construct a completion TLP with Unsupported request
 * if valid, continue to the next steps:
 * Getting TLP Type (Configuration Read, or Write)
 * a) Configuration Read:
 * Get the Data to be read from the given Register number -> convert this unsigned int data to dynamic_bitset -> Determine the TLP construction
 * algorithm to be made (in this case will be CplD) -> Perform this algorithm and return the TLP result
 * 
 * b) Configuration Write:
 * Get Data to be written to the given register from the given TLP -> Perform the write operation inside the regiser, and if it's not a valid
 * write operation construct a completion TLP with Unsupported request and return it, otherwise, Determine the TLP construction
 * algorithm to be made (in this case will be Cpl) -> Perform this algorithm and return the TLP result 
 * 
 * @param tlp -> TLP to be handled
 * @return TLP -> the resultant TLP
 */
TLP ConfigurationController::handleConfigurationRequest(TLP * tlp)
{
    int Registernumber, validWriteOperation = 0;
    TLPType configType;

    boost::dynamic_bitset<> dataToBeReadBits;
    unsigned int dataToBeReadUint; // data which we will read from the Configuration Space / PCIE Capability structure
    unsigned int dataToBeWrittenUint; // data which we will write to the Configuration Space / PCIE Capability structure

    /* Send pointers to the TLP */
    Registernumber = getRegisterNumber(tlp);

    if(!isValidRegisterNumber(Registernumber))
    {
        tlpConstructor->setAlgorithm(cplUR);
        return tlpConstructor->performAlgorithm();
    }
    
    configType = getTLPType(tlp); // Get the TLP type

    /* 1st, getting the register length (in bytes), 2nd setting this length to be used while constructing the TLP */
    tlpConstructor->setRegisterLength(configuration->getRegisterLengthInBytes(Registernumber));
    tlpConstructor->setTLP(tlp);
    tlpConstructor->setDeviceID(configuration->getDeviceID());

    switch (configType)
    {
    case TLPType::ConfigRead0:
        dataToBeReadUint = handler->handleConfigurationRead(Registernumber);

        dataToBeReadBits = convertToBitSet(dataToBeReadUint);

        tlpConstructor->setData(dataToBeReadBits);
        tlpConstructor->setAlgorithm(cplD);
        
        return tlpConstructor->performAlgorithm();

    case TLPType::ConfigWrite0:
        dataToBeWrittenUint = getTLPData(tlp);
        
        validWriteOperation = handler->handleConfigurationWrite(Registernumber, dataToBeWrittenUint);
        
        /* That should return a TLP to be returned */
        if(validWriteOperation)
            tlpConstructor->setAlgorithm(cpl);
            return tlpConstructor->performAlgorithm();
        
        tlpConstructor->setAlgorithm(cplUR);
        return tlpConstructor->performAlgorithm();

    default:
        tlpConstructor->setAlgorithm(cplUR);
        return tlpConstructor->performAlgorithm();
    }
}