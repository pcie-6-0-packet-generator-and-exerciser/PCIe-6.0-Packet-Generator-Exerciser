#pragma once

#include "..\Endpoint\configuration_classes\configuration.h"
#include "..\Endpoint\configuration_visitor_classes\configuration_visitor.h"

/* Singleton Class */
class Type1Config : public Configuration
{
private:
    static Type1Config* type1Config;

    Type1Config();

    ~Type1Config();

public:
    static Type1Config* constructType1ConfigSpace();

    unsigned int accept(shared_ptr<ConfigurationVisitor> visitor) override;
};