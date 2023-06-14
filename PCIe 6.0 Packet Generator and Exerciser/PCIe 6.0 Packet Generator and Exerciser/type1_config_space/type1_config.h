#pragma once

#include "..\Endpoint\configuration_classes\configuration.h"
#include "..\Endpoint\configuration_visitor_classes\configuration_visitor.h"

/* Singleton Class */
class Type1Config : public Configuration
{
private:
    static Type1Config* t1;

    Type1Config();

    ~Type1Config();

public:
    static Type1Config* constructType1ConfigSpace();

    unsigned int accept(shared_ptr<ConfigurationVisitor> visitor) override;

    boost::dynamic_bitset<> convertToBitSet(unsigned int data);

    unsigned int convertToUnsignedInt(boost::dynamic_bitset<> data);

    boost::dynamic_bitset<> readType1Reg(int registerNumber);

    int writeType1Reg(int registerNumber, boost::dynamic_bitset<> data);
};