// Abstract class OHC
#include <bitset>

class OHC {
public:
    virtual void someFunction() = 0;  // pure virtual function
    // Public attribute size of type int, set to 4
    int size = 4;
};


// Concrete class OHCA1 that inherits from OHC
class OHCA1 : public OHC {
public:
    // Public attributes firstDWBE and lastDWBE, both as bitsets with a size of 4
    std::bitset<4> firstDWBE;
    std::bitset<4> lastDWBE;

    // Constructor that takes firstDWBE and lastDWBE attributes as input and sets them
    OHCA1(std::bitset<4> firstDWBEsetter, std::bitset<4> lastDWBEsetter) {
        for (int i = 0; i < 4; i++) {
            firstDWBE[i] = firstDWBEsetter[i];
            lastDWBE[i] = lastDWBEsetter[i];
        }
    }

};

// Concrete class OHCA3 that inherits from OHC
class OHCA3 : public OHC {
public:
    // Public attributes firstDWBE and lastDWBE, both as bitsets with a size of 4
    std::bitset<4> firstDWBE;
    std::bitset<4> lastDWBE;
    int destinationSegment;

    // Constructor that takes firstDWBE and lastDWBE attributes as input and sets them
    OHCA3(std::bitset<4> firstDWBEsetter, std::bitset<4> lastDWBEsetter, int destinationSeg) {
        for (int i = 0; i < 4; i++) {
            firstDWBE[i] = firstDWBEsetter[i];
            lastDWBE[i] = lastDWBEsetter[i];
        }
        destinationSegment = destinationSeg;
    }

};


// Concrete class OHCA4 that inherits from OHC
class OHCA4 : public OHC {
public:
    // Public attributes destinationSegment
    int destinationSegment;

    // Constructor that takes destinationSegment attributes as input and sets it
    OHCA4(int destinationSeg) {
        destinationSegment = destinationSeg;

    }
};

// Concrete class OHCA5 that inherits from OHC
class OHCA5 : public OHC {
public:
    int destinationSegment;
    int completerSegment;
    std::bitset<2> lowerAddress;
    enum class CPLStatus {
        True = 1,
        False = 0
    };
    CPLStatus CPLStatusEnum;
    // Constructor that takes destinationSegment and completerSegment and lowerAddress and CPLStatus as input and set them
    OHCA5(int destinationSeg, int completerSeg, std::bitset<2> lowerAddresssetter, CPLStatus myEnumsetter) :
        CPLStatusEnum(myEnumsetter)
    {
        for (int i = 0; i < 2; i++) {
            lowerAddress[i] = lowerAddresssetter[i];
        }
        destinationSegment = destinationSeg;
        completerSegment = completerSeg;
    }

};