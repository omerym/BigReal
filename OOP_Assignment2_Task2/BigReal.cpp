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
    UnsignedBigReal value;
    bool sign;
public:
    static int compare(const BigReal& r, const BigReal& l);
    BigReal(string realNumber) { setNum(realNumber); }
    BigReal(const char* realNumber) : BigReal(string(realNumber)) {}
    BigReal(double realNumber = 0.0) :BigReal(to_string(realNumber)) {}
    BigReal(unsigned int realNumber) :BigReal(to_string(realNumber)) {}
    BigReal(int realNumber) :BigReal(to_string(realNumber)) {}
    BigReal(UnsignedBigReal _value, bool _sign = false)
    {
        value = _value;
        sign = _sign;
    }
    void setNum(string s);
    static bool isValidBigReal(string s);
    bool isNegative() const
    {
        return sign && (value != 0);
    }
    BigReal operator- (BigReal other);
    BigReal operator- ();
    BigReal operator+(BigReal other);
    bool operator>= (BigReal anotherReal) const;
    bool operator<= (BigReal anotherReal) const;
    bool operator> (BigReal anotherReal) const;
    bool operator< (BigReal anotherReal) const;
    bool operator!= (BigReal anotherReal) const;
    bool operator== (BigReal anotherReal) const;
    friend ostream& operator << (ostream& out, BigReal num);
};

int BigReal::compare(const BigReal &r,const BigReal& l)
{
    if (r.isNegative() == l.isNegative())
    {
        int f = r.isNegative() ? -1 : 1;
        return UnsignedBigReal::compare(r.value, l.value) * f;
    }
    return r.isNegative() ? -1 : 1;
}

void BigReal::setNum(string s)
{
    if (!isValidBigReal(s))
    {
        throw invalid_argument("invalid real number");
    }
    if (s[0] == '+' || s[0] == '-')
    {
        sign = s[0] == '-';
        value.setNum(s.substr(1));
    }
    else
    {
        sign = false;
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
    if (value == 0)
    {
        return 0;
    }
    BigReal negative = *this;
    negative.sign = !sign;
    return negative;
}

BigReal BigReal::operator+(BigReal other)
{
    bool _sign = value > other.value ? sign : other.sign;
    UnsignedBigReal max = UnsignedBigReal::max(this->value, other.value);
    UnsignedBigReal min = UnsignedBigReal::min(this->value, other.value);
    UnsignedBigReal _value = isNegative() == other.isNegative() ? max + min : max - min;
    return BigReal(_value, _sign);
}
bool BigReal::operator>=(BigReal anotherReal) const
{
    return compare(*this, anotherReal) >= 0;
}
bool BigReal::operator<=(BigReal anotherReal) const
{
    return compare(*this, anotherReal) <= 0;
}
bool BigReal::operator>(BigReal anotherReal) const
{
    return compare(*this, anotherReal) > 0;
}
bool BigReal::operator<(BigReal anotherReal) const
{
    return compare(*this, anotherReal) < 0;
}
bool BigReal::operator!=(BigReal anotherReal) const
{
    return compare(*this, anotherReal) != 0;
}
bool BigReal::operator==(BigReal anotherReal) const
{
    return compare(*this, anotherReal) == 0;
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
    if (num.isNegative())
    {
        out << '-';
    }
    out << num.value;
    return out;
}

#endif //BigReal