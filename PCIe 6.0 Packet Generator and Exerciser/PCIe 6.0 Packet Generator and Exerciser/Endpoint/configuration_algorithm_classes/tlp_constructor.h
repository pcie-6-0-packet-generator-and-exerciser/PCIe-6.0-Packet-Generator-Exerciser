#pragma once

#include "completion_construction_algorithms.h"

class TLPConstructor
{
    private:
        shared_ptr<CompletionConstructionAlgorithms> completion;

    public:
        void setData(boost::dynamic_bitset<> dataToBeReadBits);

        void setRegisterLength(int registerLength);

        void setAlgorithm(shared_ptr<CompletionConstructionAlgorithms> completion);

        TLP performAlgorithm();
};