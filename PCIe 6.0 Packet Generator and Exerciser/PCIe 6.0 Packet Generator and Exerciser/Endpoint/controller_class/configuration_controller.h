#pragma once

#include "..\configuration_visitor_classes\configuration_request_handler.h"
#include "..\configuration_algorithm_classes\tlp_constructor.h"
#include "..\configuration_classes\configuration.h"
#include "..\configuration_algorithm_classes\completion_construction_algorithms.h"
#include "..\..\utils\tlp.h"

class ConfigurationController
{
    private:
        shared_ptr<ConfigurationRequestHandler> handler;
        shared_ptr<TLPConstructor> tlpConstructor;
        
        ConfigurationSpace * configuration;
        PCIECapability * capability;
        
        shared_ptr<CompletionWithData> cplD;
        shared_ptr<CompletionWithoutData> cpl;
        shared_ptr<CompletionWithUR> cplUR;

        /* Any function that needs to perform something on the TLP should take a pointer to it */

        int getRegisterNumber(TLP * tlp);

        int isValidRegisterNumber(int registerNumber);

        TLPType getTLPType(TLP * tlp);

        unsigned int getTLPData(TLP * tlp);

        unsigned int convertToUnsignedInt(boost::dynamic_bitset<> bits);

        boost::dynamic_bitset<> convertToBitSet(unsigned int uintValue);
    
    public:
        ConfigurationController();

        TLP handleConfigurationRequest(TLP * tlp);
};