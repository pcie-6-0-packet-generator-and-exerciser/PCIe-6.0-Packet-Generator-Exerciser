#include "tlp_constructor.h"

/**
 * @brief Determining the TLP construction algorithm to be made
 * 
 * @param completion -> the class pointer to be used for applying its implementation
 */
void TLPConstructor::setAlgorithm(shared_ptr<CompletionConstructionAlgorithms> completion)
{
    this->completion = completion;
}

/**
 * @brief Performing the TLP construction algorithm determined before
 * 
 * @return TLP -> The constructed TLP (Completion)
 */
TLP TLPConstructor::performAlgorithm()
{
    return completion->constructTLP();
}

/**
 * @brief Setting the data to be used in case of a Completion with Data Payload inside (CplD)
 * 
 * @param dataToBeReadBits -> the Data to be returned to handle the Read request
 */
void TLPConstructor::setData(boost::dynamic_bitset<> dataToBeReadBits)
{
    completion->dataToBeReadBits = dataToBeReadBits;
}

void TLPConstructor::setRegisterLength(int registerLength)
{
    completion->registerLengthInBytes = registerLength;
}

void TLPConstructor::setTLP(TLP* tlp)
{
    completion->tlp = tlp;
}

void TLPConstructor::setDeviceID(unsigned int deviceID)
{
    completion->deviceID = deviceID;
}