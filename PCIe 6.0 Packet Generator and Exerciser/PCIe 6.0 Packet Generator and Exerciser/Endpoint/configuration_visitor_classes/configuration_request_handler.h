#pragma once 

#include "configuration_read_visitor.h"
#include "configuration_write_visitor.h"

class ConfigurationRequestHandler
{
    private:
        /* They are shared (not unique) because they will be passed functions so that they can visit our Configuration Space and 
           PCIE Capability classes, and they aren't weak because they are owned by this class, so their life time should
           be only end when the class's life time ends. */
        shared_ptr<ConfigurationReadVisitor> readVisitor;
        shared_ptr<ConfigurationWriteVisitor> writeVisitor;


        ConfigurationSpace * configuration;
        PCIECapability * capability;
    
    public:
        ConfigurationRequestHandler(ConfigurationSpace* configuration, PCIECapability* capability);
        
        unsigned int handleConfigurationRead(int registerNumber);

        int handleConfigurationWrite(int registerNumber, unsigned int data);
};