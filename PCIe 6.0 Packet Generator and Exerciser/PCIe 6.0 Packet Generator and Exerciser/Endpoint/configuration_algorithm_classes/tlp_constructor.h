#pragma once

#include "completion_construction_algorithms.h"

class CompletionConstructionAlgorithms;

class TLPConstructor
{
    private:
        shared_ptr<CompletionConstructionAlgorithms> completion;

    public:
        void setData(boost::dynamic_bitset<> dataToBeReadBits);

        void setAlgorithm(shared_ptr<CompletionConstructionAlgorithms> completion);

        TLP performAlgorithm();
};