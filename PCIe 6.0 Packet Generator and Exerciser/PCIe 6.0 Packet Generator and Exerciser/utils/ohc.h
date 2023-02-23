// Abstract class OHC
class OHC {
public:
    // Public attribute size of type int, set to 4
    int size = 4;
};


// Concrete class OHCA1 that inherits from OHC
class OHCA1 : public OHC {
public:
    // Public attributes firstDWBE and lastDWBE, both arrays of integers with a length of 4
    int firstDWBE[4];
    int lastDWBE[4];

    // Constructor that takes firstDWBE and lastDWBE attributes as input and sets them
    OHCA1(int firstDWBE_[], int lastDWBE_[]) {
        for (int i = 0; i < 4; i++) {
            firstDWBE[i] = firstDWBE_[i];
            lastDWBE[i] = lastDWBE_[i];
        }
    }

};

// Concrete class OHCA3 that inherits from OHC
class OHCA3 : public OHC {
public:
    // Public attributes firstDWBE and lastDWBE, both arrays of integers with a length of 4
    int firstDWBE[4];
    int lastDWBE[4];
    int destinationSegment;

    // Constructor that takes firstDWBE and lastDWBE attributes as input and sets them
    OHCA3(int firstDWBE_[], int lastDWBE_[], int destinationSeg) {
        for (int i = 0; i < 4; i++) {
            firstDWBE[i] = firstDWBE_[i];
            lastDWBE[i] = lastDWBE_[i];
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
    int lowerAddress[2];
    enum class CPLStatus {
        True = 1,
        False = 0
    };
    CPLStatus CPLStatus_;
    // Constructor that takes destinationSegment and completerSegment and lowerAddress and CPLStatus as input and set them
    OHCA5(int destinationSeg, int completerSeg, int lowerAddress_[], CPLStatus myEnum_) :
        CPLStatus_(myEnum_)
    {
        for (int i = 0; i < 2; i++) {
            lowerAddress[i] = lowerAddress_[i];
        }
        destinationSegment = destinationSeg;
        completerSegment = completerSeg;
    }

};