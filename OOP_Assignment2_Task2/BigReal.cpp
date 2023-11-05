#ifndef _BigReal
#define _BigReal

#include <iostream>
#include <string>
#include <string.h>
#include <deque>
#include "BCDDigit.cpp"
#include "UnsignedBigReal.cpp"
using namespace std;
 
 class BigReal{
    bool isNegative;
    UnsignedBigReal BigRealValue;
        void SetSignValue(bool Sign)
    {
        isNegative = Sign;
    }
    void SetBigRealValue(const UnsignedBigReal& value) {
        BigRealValue = value;
    }
    public:
    BigReal() : isNegative(false){};  

    BigReal(UnsignedBigReal BigRealValue);
    
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
	if (isNegative == other.isNegative)
	{
      if(BigRealValue>other.BigRealValue)
         {
            Value.BigRealValue=  BigRealValue-other.BigRealValue;
         }
         else
         {
            Value.BigRealValue= other.BigRealValue-BigRealValue;
         }
      Value.SetSignValue(isNegative);
	}
	else
	{
		Value.BigRealValue = BigRealValue+other.BigRealValue;
       
         if(BigRealValue>other.BigRealValue)
         {
            Value.SetSignValue(isNegative);
         }
         else
         {
            Value.SetSignValue(!isNegative);
         }
	}
	return Value;
}

BigReal BigReal::operator+(BigReal other)
{
   BigReal Value;
   if (isNegative == other.isNegative)
	{
		Value.BigRealValue=  BigRealValue+other.BigRealValue;
      Value.SetSignValue(isNegative);
	}
	else
	{
      if(BigRealValue>other.BigRealValue)
         {
            Value.SetSignValue(isNegative);
            Value.BigRealValue = BigRealValue-other.BigRealValue;
         }
         else
         {
            Value.SetSignValue(!isNegative);
            Value.BigRealValue = other.BigRealValue-BigRealValue;
         }
	}
	return Value;
   
}
bool BigReal::operator>=(BigReal anotherReal)
{
    if (!isNegative && anotherReal.isNegative)
    {
        return true;
    }
    if (isNegative && anotherReal.isNegative)
    {
        return false;
    }
    int c = BigRealValue.compare(BigRealValue, anotherReal.BigRealValue);
    return c >= 0;

}
bool BigReal::operator<=(BigReal anotherReal)
{
    if (!isNegative && anotherReal.isNegative)
    {
        return false;
    }
    if (isNegative && !anotherReal.isNegative)
    {
        return true;
    }
    int c = BigRealValue.compare(BigRealValue, anotherReal.BigRealValue);
    return c <= 0;
}
bool BigReal::operator>(BigReal anotherReal)
{
    if (!isNegative && anotherReal.isNegative)
    {
        return true;
    }
    if (isNegative && !anotherReal.isNegative)
    {
        return false;
    }
    return BigRealValue.compare(BigRealValue, anotherReal.BigRealValue) == 1;
}
bool BigReal::operator<(BigReal anotherReal)
{
    if (!isNegative && anotherReal.isNegative)
    {
        return false;
    }
    if (isNegative && !anotherReal.isNegative)
    {
        return true;
    }
    return BigRealValue.compare(BigRealValue, anotherReal.BigRealValue) == -1;
}
bool BigReal::operator!=(BigReal anotherReal)
{
    if (isNegative == anotherReal.isNegative)
    {
        return BigRealValue.compare(BigRealValue, anotherReal.BigRealValue) != 0;
    }
    return true;
}
bool BigReal::operator==(BigReal anotherReal)
{
    if (isNegative == anotherReal.isNegative)
    {
        return BigRealValue.compare(BigRealValue, anotherReal.BigRealValue) == 0;
    }
    else
    {
        return false;
    }
}
istream& operator>>(istream& in, BigReal& num)
{
	string s;
	in >> s;
   if(s[0]=='-')
   {
      num.SetSignValue(s[0]);
      num.SetBigRealValue(s.substr(1,s.size()-1));
   }
   else
   {
      num.SetBigRealValue(s);
   }
	return in;
}

ostream& operator<<(ostream& out, BigReal num)
{
    if (num.isNegative && num.BigRealValue != 0)
    {
        out << '-';
    }
    out << num.BigRealValue;
    return out;
}

#endif //BigReal