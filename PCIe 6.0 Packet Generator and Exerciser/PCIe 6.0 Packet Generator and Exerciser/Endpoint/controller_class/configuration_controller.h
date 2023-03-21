#pragma once

#include "..\configuration_visitor_classes\configuration_request_handler.h"
#include "..\configuration_algorithm_classes\completer_constructor.h"
#include "..\configuration_classes\configuration.h"
#include "..\configuration_algorithm_classes\completion_construction_algorithms.h"
#include "..\..\utils\tlp.h"

/* Singleton class */
class ConfigurationController
{
    private:
        static ConfigurationController* configurationController;

        ConfigurationController(); // Making a private constructor to avoid the new operators

        shared_ptr<CompleterConstructor> completerConstructor;
        shared_ptr<ConfigurationRequestHandler> handler;
        
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
        static ConfigurationController* constructConfigurationController();

        TLP handleConfigurationRequest(TLP * tlp);

        int IsMemorySpaceEnabled();

        int IsIOSpaceEnabled();
};