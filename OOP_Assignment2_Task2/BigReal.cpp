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
 //TODO: fix the - logic
 BigReal BigReal::operator-(BigReal other)
{
   BigReal Value;
	if (SignValue == other.SignValue)
	{
		Value.BigRealValue=  BigRealValue-other.BigRealValue;
      if(Value.BigRealValue!=0)Value.SetSignValue(SignValue);
	}
	else
	{
		Value.BigRealValue = BigRealValue+other.BigRealValue;
       
         if(BigRealValue>other.BigRealValue)
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
//TODO: fix the + logic
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
		Value.BigRealValue = BigRealValue-other.BigRealValue;
       
         if(BigRealValue>other.BigRealValue)
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
bool BigReal::operator>=(BigReal anotherReal)
{
   if(SignValue==false&&anotherReal.SignValue==true)
   {
      return true;
   }
   else if(SignValue==true&&anotherReal.SignValue==false)
   {
      return false;
   }
   else
   {
      int c= BigRealValue.comparePublic(BigRealValue,anotherReal.BigRealValue);
      return c >= 0;
   }
	
}
bool BigReal::operator<=(BigReal anotherReal)
{
	if(SignValue==false&&anotherReal.SignValue==true)
   {
      return false;
   }
   else if(SignValue==true&&anotherReal.SignValue==false)
   {
      return true;
   }
   else
   {
      int c= BigRealValue.comparePublic(BigRealValue,anotherReal.BigRealValue);
      return c <= 0;
   }
}
bool BigReal::operator>(BigReal anotherReal)
{
	if(SignValue==false&&anotherReal.SignValue==true)
   {
      return true;
   }
   else if(SignValue==true&&anotherReal.SignValue==false)
   {
      return false;
   }
   else
   {
      return BigRealValue.comparePublic(BigRealValue,anotherReal.BigRealValue)==1;
      
   }
}
bool BigReal::operator<(BigReal anotherReal)
{
	if(SignValue==false&&anotherReal.SignValue==true)
   {
      return false;
   }
   else if(SignValue==true&&anotherReal.SignValue==false)
   {
      return true;
   }
   else
   {
      return BigRealValue.comparePublic(BigRealValue,anotherReal.BigRealValue)==-1;
      
   }
}
bool BigReal::operator!=(BigReal anotherReal)
{
	if(SignValue==anotherReal.SignValue)
   {
      return BigRealValue.comparePublic(BigRealValue,anotherReal.BigRealValue)!=0;
   }
   else
   {
      return true;
   }
}
bool BigReal::operator==(BigReal anotherReal)
{
	if(SignValue==anotherReal.SignValue)
   {
      return BigRealValue.comparePublic(BigRealValue,anotherReal.BigRealValue)==0;
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
	if(num.SignValue&&num.BigRealValue!=0)
   {
      out<<'-';
   }
   out<<num.BigRealValue;
	return out;
}

#endif //BigReal