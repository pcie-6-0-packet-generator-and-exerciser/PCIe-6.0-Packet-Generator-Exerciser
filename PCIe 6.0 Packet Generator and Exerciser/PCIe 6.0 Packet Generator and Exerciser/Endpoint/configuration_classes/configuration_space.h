#pragma once

#include "configuration.h"
#include "..\configuration_visitor_classes\configuration_visitor.h"

/* Singleton Class */
class ConfigurationSpace: public Configuration
{
private:
    static ConfigurationSpace * configurationSpace;

    ConfigurationSpace();

    ~ConfigurationSpace();

public:
    static ConfigurationSpace * constructConfigurationSpace();

    unsigned int accept(shared_ptr<ConfigurationVisitor> visitor) override;

    bool isMemorySpaceEnabled();

    bool isIOSpaceEnabled();
    
    void setReceivedMasterAbortBit();
};