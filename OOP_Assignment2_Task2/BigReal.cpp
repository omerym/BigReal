#ifndef _BigReal
#define _BigReal

#include <iostream>
#include <string>
#include <deque>
#include "BCDDigit.cpp"
#include "PackedBCD.cpp"
#include "UnsignedBigReal.cpp"
using namespace std;
 
 class BigReal : UnsignedBigReal{
    bool SignValue;
    UnsignedBigReal BigRealValue;
    public:
    void SetSignValue(bool Sign);
    BigReal() : SignValue(true){};  

    BigReal(bool Sign): SignValue(Sign){};
    void SetSignValue(bool Sign)
    {
    SignValue=Sign;
    }
    

    
 };
#endif //BigReal