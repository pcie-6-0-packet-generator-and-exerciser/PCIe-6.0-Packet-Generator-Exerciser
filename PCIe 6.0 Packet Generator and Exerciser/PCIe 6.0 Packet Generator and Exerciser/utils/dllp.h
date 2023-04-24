#pragma once
#include "boost/dynamic_bitset.hpp"

class Dllp {
public:
	enum class DllpType {
		initFC1 = 1,
		initFC2 = 3,
		updateFC = 2
	};
	enum class CreditType {
		P = 0,
		NP = 1,
		Cpl = 2
	};
	int HdrScale;
	int DataScale;
	int DataFc;
	int HdrFC;
	int VC;
	bool shared;
	DllpType m_type;
	CreditType m_creditType;

	void duck() {
		for (int intCreditType = 0; intCreditType < 3; intCreditType++)
		{
			Foo foo = static_cast<CreditType>(intCreditType);
		}
	}


	Dllp(int hdrScale, int dataScale, int dataFc, int hdrFC, int vc, bool share, DllpType type, CreditType creditType);
	Dllp();
	~Dllp();

	static Dllp DllpObjRep(boost::dynamic_bitset<> dllpBits);
	boost::dynamic_bitset<> getBitRep() const;
};
