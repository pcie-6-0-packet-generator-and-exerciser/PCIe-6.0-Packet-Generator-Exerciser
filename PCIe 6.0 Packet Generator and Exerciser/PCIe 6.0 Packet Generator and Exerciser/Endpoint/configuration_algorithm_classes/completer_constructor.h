#pragma once

#include "completion_construction_algorithms.h"

class CompleterConstructor
{
    private:
        shared_ptr<CompletionConstructionAlgorithms> completion;

    public:
        void setData(boost::dynamic_bitset<> dataToBeReadBits);

        void setRegisterLength(int registerLength);

        void setTLP(TLP* tlp);

        void setDeviceID(unsigned int deviceID);

        void setAlgorithm(shared_ptr<CompletionConstructionAlgorithms> completion);

        TLP performAlgorithm();
};