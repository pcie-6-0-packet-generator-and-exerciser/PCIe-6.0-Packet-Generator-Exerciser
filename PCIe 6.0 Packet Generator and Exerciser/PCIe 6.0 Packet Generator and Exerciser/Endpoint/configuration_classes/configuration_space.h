#pragma once

#include "configuration.h"

class ConfigurationVisitor;

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

    int isMemorySpaceEnabled();

    int isIOSpaceEnabled();

    int getNumberOfRegisters();
    
    void setReceivedMasterAbortBit();
};