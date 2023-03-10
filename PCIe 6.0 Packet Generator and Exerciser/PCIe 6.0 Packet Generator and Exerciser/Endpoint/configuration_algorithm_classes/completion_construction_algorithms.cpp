#include "completion_construction_algorithms.h"

CompletionConstructionAlgorithms::CompletionConstructionAlgorithms(): dataToBeReadBits(0){}

/**
 * @brief Constructing a Completion TLP with Data Payload inside (return of a Configuration Read request)
 * 
 * @return TLP -> The Constructed TLP (CplD)
 */
TLP CompletionWithData::constructTLP()
{
    
}

/**
 * @brief Constructing a Completion TLP without Data Payload inside (return of a Successful Configuration Write request)
 * 
 * @return TLP -> The Constructed TLP (Cpl)
 */
TLP CompletionWithoutData::constructTLP()
{
    
}

/**
 * @brief Constructing a Completion TLP with Unsupported request (OHC-A5) (return of an Unsuccessful Read or Write request)
 * 
 * @return TLP -> The Constructed TLP (CplUR)
 */
TLP CompletionWithUR::constructTLP()
{
    
}

