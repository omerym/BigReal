#ifndef _BigReal
#define _BigReal

#include <iostream>
#include <string>
#include <string.h>
#include <deque>
#include "BCDDigit.cpp"
#include "PackedBCD.cpp"
#include "UnsignedBigReal.cpp"
using namespace std;
 
 class BigReal{
    bool SignValue;
    UnsignedBigReal BigRealValue;
    public:
    BigReal() : SignValue(false){};  

    BigReal(UnsignedBigReal BigRealValue);
    void SetSignValue(bool Sign)
    {
    SignValue=Sign;
    }
    void SetBigRealValue(const UnsignedBigReal& value) {
        BigRealValue = value;
    }
    
    BigReal operator- (BigReal other);
	 BigReal operator+(BigReal other);
	 bool operator>= (BigReal anotherReal);
	 bool operator<= (BigReal anotherReal);
	 bool operator> (BigReal anotherReal);
	 bool operator< (BigReal anotherReal);
	 bool operator!= (BigReal anotherReal);
	 bool operator== (BigReal anotherReal);
	 friend istream& operator >> (istream& in, BigReal &num);
	 friend ostream& operator << (ostream& out, BigReal num);
    
 };
 BigReal BigReal::operator-(BigReal other)
{
   BigReal Value;
	if (SignValue == other.SignValue)
	{
		Value.BigRealValue=  BigRealValue-other.BigRealValue;
      Value.SetSignValue(SignValue);
	}
	else
	{
		Value.BigRealValue = BigRealValue-other.BigRealValue;
      if(BigRealValue>=other.BigRealValue)
      {
         Value.SetSignValue(SignValue);
      }
      else
      {
         Value.SetSignValue(!SignValue);
      }
	}
	return Value;
}
BigReal BigReal::operator+(BigReal other)
{
   BigReal Value;
   if (SignValue == other.SignValue)
	{
		Value.BigRealValue=  BigRealValue+other.BigRealValue;
      Value.SetSignValue(SignValue);
	}
	else
	{
		Value.BigRealValue = BigRealValue+other.BigRealValue;
      if(BigRealValue>=other.BigRealValue)
      {
         Value.SetSignValue(SignValue);
      }
      else
      {
         Value.SetSignValue(!SignValue);
      }
	}
	return Value;
   
}
istream& operator>>(istream& in, BigReal& num)
{
	string s;
	in >> s;
	num.SetSignValue(s[0]);
   num.SetBigRealValue(s.substr(1,s.size()-1));
	return in;
}

ostream& operator<<(ostream& out, BigReal num)
{
	if(num.SignValue)
   {
      out<<'-';
   }
   out<<num.BigRealValue;
	return out;
}

#endif //BigReal