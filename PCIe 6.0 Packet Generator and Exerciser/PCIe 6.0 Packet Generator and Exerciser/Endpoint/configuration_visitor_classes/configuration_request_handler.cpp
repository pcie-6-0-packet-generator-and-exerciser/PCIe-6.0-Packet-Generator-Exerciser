#include "configuration_request_handler.h"

ConfigurationRequestHandler::ConfigurationRequestHandler(ConfigurationSpace * configuration, PCIECapability * capability)
{
    this->configuration = configuration;
    this->capability = capability;

    readVisitor = make_shared<ConfigurationReadVisitor>();
    writeVisitor = make_shared<ConfigurationWriteVisitor>();
}

/**
 * @brief Handling the coming Configuration Read requests
 * 
 * @param registerNumber -> The register number which we will read Data from
 * @return unsigned int -> The read Data
 */
unsigned int ConfigurationRequestHandler::handleConfigurationRead(int registerNumber)
{
    readVisitor->setRegisterNumber(registerNumber);

    /* Identifying either we should read from the Configuration Space or the PCIE Capability structure */
    if(registerNumber <= 16)
        return configuration->accept(readVisitor);

    /* To be used after making the PCIE Capability structure */
    //return capability->accept(readVisitor);

    return 0;
}

/**
 * @brief Handling the coming Configuration Write requests
 * 
 * @param registerNumber -> The register number which we will read Data from 
 * @param data -> data to be written inside the register
 * @return int -> To know whether the request is handled correctly (return 1), otherwise (return 0)
 */
int ConfigurationRequestHandler::handleConfigurationWrite(int registerNumber, unsigned int data)
{
    writeVisitor->setRegisterNumber(registerNumber);
    writeVisitor->setData(data);

    if(registerNumber <= 16)
        return configuration->accept(writeVisitor);
    
    /* To be used after making the PCIE Capability structure */
    //return capability->accept(writeVisitor);
}