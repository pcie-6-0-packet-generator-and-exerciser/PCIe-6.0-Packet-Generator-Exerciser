#pragma once

#include "..\register_class\register.h"

class CompletionConstructionAlgorithms
{
    public:
        boost::dynamic_bitset<> dataToBeReadBits;

        CompletionConstructionAlgorithms();

        virtual TLP constructTLP() = 0;
};

class CompletionWithData: public CompletionConstructionAlgorithms
{
    public:
        TLP constructTLP() override;
};

class CompletionWithUR: public CompletionConstructionAlgorithms
{
    public:
        TLP constructTLP() override;
};

class CompletionWithoutData: public CompletionConstructionAlgorithms
{
    public:
        TLP constructTLP() override;
};