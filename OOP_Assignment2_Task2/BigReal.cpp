#ifndef _BigReal
#define _BigReal

#include <iostream>
#include <string>
#include <string.h>
#include <deque>
#include "BCDDigit.cpp"
#include "UnsignedBigReal.cpp"
using namespace std;
 
class BigReal {
    bool isNegative;
    UnsignedBigReal value;
public:
    BigReal() : isNegative(false) {};
    BigReal(UnsignedBigReal BigRealValue);
    void setNum(string s);
    static bool isValidBigReal(string s);
    BigReal operator- (BigReal other);
    BigReal operator- ();
    BigReal operator+(BigReal other);
    bool operator>= (BigReal anotherReal);
    bool operator<= (BigReal anotherReal);
    bool operator> (BigReal anotherReal);
    bool operator< (BigReal anotherReal);
    bool operator!= (BigReal anotherReal);
    bool operator== (BigReal anotherReal);
    friend ostream& operator << (ostream& out, BigReal num);


};

void BigReal::setNum(string s)
{
    if (!isValidBigReal(s))
    {
        throw invalid_argument("invalid real number");
    }
    if (s[0] == '+' || s[0] == '-')
    {
        isNegative = s[0] == '-';
        value.setNum(s.substr(1));
    }
    else
    {
        isNegative = false;
        value.setNum(s);
    }
}

bool BigReal::isValidBigReal(string s)
{
    if (s[0] == '+' || s[0] == '-')
    {
        return UnsignedBigReal::isValidUnsignedReal(s.substr(1));
    }
    return UnsignedBigReal::isValidUnsignedReal(s);
}

BigReal BigReal::operator-(BigReal other)
{
    return *this + -other;
}

BigReal BigReal::operator-()
{
    BigReal negative = *this;
    negative.isNegative = !isNegative;
    return negative;
}

BigReal BigReal::operator+(BigReal other)
{
   BigReal Value;
   if (isNegative == other.isNegative)
	{
		Value.value=  value+other.value;
      Value.isNegative = isNegative;
	}
	else
	{
      if(value>other.value)
         {
            Value.isNegative = isNegative;
            Value.value = value-other.value;
         }
         else
         {
            Value.isNegative = !isNegative;
            Value.value = other.value-value;
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
    int c = value.compare(value, anotherReal.value);
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
    int c = value.compare(value, anotherReal.value);
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
    return value.compare(value, anotherReal.value) == 1;
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
    return value.compare(value, anotherReal.value) == -1;
}
bool BigReal::operator!=(BigReal anotherReal)
{
    if (isNegative == anotherReal.isNegative)
    {
        return value.compare(value, anotherReal.value) != 0;
    }
    return true;
}
bool BigReal::operator==(BigReal anotherReal)
{
    if (isNegative == anotherReal.isNegative)
    {
        return value.compare(value, anotherReal.value) == 0;
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
    num.setNum(s);
	return in;
}

ostream& operator<<(ostream& out, BigReal num)
{
    if (num.isNegative && num.value != 0)
    {
        out << '-';
    }
    out << num.value;
    return out;
}

#endif //BigReal