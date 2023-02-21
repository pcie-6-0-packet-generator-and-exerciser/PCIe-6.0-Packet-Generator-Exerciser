#pragma once
#include <bitset>
#include <array>
enum class CreditType { initFC1 = 1, initFC2 = 3, updateFC = 2 };
enum class Type { P = 0, NP = 1, Cpl = 2 };

class Dllp {
public:
    int HdrScale;
    bool shared;
    int VC;
    int HdrFC;
    int DataScale;
    int DataFC;
    CreditType creditType; //  CreditType enum
    Type type; // Type enum

    Dllp(int HdrScale, bool shared, int VC, int HdrFC, int DataScale, int DataFC, CreditType credittype, Type type);
    ~Dllp(); // Destructor declaration

    std::array<bool, 32> getBitRep() const;
}; 