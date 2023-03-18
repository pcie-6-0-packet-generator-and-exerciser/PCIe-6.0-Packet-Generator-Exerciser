#include "completer_constructor.h"

/**
 * @brief Determining the TLP construction algorithm to be made
 * 
 * @param completion -> the class pointer to be used for applying its implementation
 */
void CompleterConstructor::setAlgorithm(shared_ptr<CompletionConstructionAlgorithms> completion)
{
    this->completion = completion;
}

/**
 * @brief Performing the TLP construction algorithm determined before
 * 
 * @return TLP -> The constructed TLP (Completion)
 */
TLP* CompleterConstructor::performAlgorithm()
{
    return completion->constructTLP();
}

/**
 * @brief Setting the data to be used in case of a Completion with Data Payload inside (CplD)
 * 
 * @param dataToBeReadBits -> the Data to be returned to handle the Read request
 */
void CompleterConstructor::setData(boost::dynamic_bitset<> dataToBeReadBits)
{
    completion->dataToBeReadBits = dataToBeReadBits;
}

void CompleterConstructor::setRegisterLength(int registerLength)
{
    completion->registerLengthInBytes = registerLength;
}

void CompleterConstructor::setTLP(TLP* tlp)
{
    completion->tlp = tlp;
}

void CompleterConstructor::setDeviceID(unsigned int deviceID)
{
    completion->deviceID = deviceID;
}