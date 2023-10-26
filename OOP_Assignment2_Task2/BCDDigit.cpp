#ifndef _BCDDigit
#define _BCDDigit

#include <iostream>

using namespace std;

class BCDDigit
{
public:
	static bool isValidBCD(unsigned int digit);
	BCDDigit(unsigned int digit = 0);
	static BCDDigit add(BCDDigit r, BCDDigit l, BCDDigit& carryOut, BCDDigit carryIn = 0);
	unsigned int getDigit();
	BCDDigit get9Compliment();
	BCDDigit get10Compliment();
	BCDDigit operator+ (BCDDigit other);
	bool operator == (BCDDigit other);
	bool operator != (BCDDigit other);
	bool operator > (BCDDigit other);
	bool operator < (BCDDigit other);
	bool operator <= (BCDDigit other);
	bool operator >= (BCDDigit other);
	friend ostream& operator << (ostream& out, BCDDigit num);
	friend istream& operator >> (istream& in, BCDDigit &num);

private:
	unsigned char digit;
};
BCDDigit::BCDDigit(unsigned int digit)
{
	if (!isValidBCD(digit))
	{
		throw new std::invalid_argument("Invalid BCD");
	}
	this->digit = digit;
}
BCDDigit BCDDigit::add(BCDDigit r, BCDDigit l, BCDDigit& carryOut, BCDDigit carryIn)
{
	unsigned char result = r.digit + l.digit + carryIn.digit;
	if (result > 9)
	{
		result += 6;
		result &= 0b1111;
		carryOut = 1;
	}
	else
	{
		carryOut = 0;
	}
	return BCDDigit(result);
}
BCDDigit BCDDigit::operator+(BCDDigit other)
{
	BCDDigit c;
	return add(*this, other, c);
}
bool BCDDigit::operator==(BCDDigit other)
{
	return digit == other.digit;
}
bool BCDDigit::operator!=(BCDDigit other)
{
	return digit != other.digit;
}
bool BCDDigit::operator>(BCDDigit other)
{
	return digit > other.digit;
}
bool BCDDigit::operator<(BCDDigit other)
{
	return digit < other.digit;
}
bool BCDDigit::operator<=(BCDDigit other)
{
	return digit <= other.digit;
}
bool BCDDigit::operator>=(BCDDigit other)
{
	return digit >= other.digit;
}
bool BCDDigit::isValidBCD(unsigned int digit)
{
	return digit < 10;
}
unsigned int BCDDigit::getDigit()
{
	return (unsigned int)digit;
}
BCDDigit BCDDigit::get9Compliment()
{
	return BCDDigit(9 - digit);
}
BCDDigit BCDDigit::get10Compliment()
{
	return BCDDigit((10 - digit) % 10);
}

ostream& operator<<(ostream& out, BCDDigit num)
{
	out << num.getDigit();
	return out;
}

istream& operator>>(istream& in, BCDDigit& num)
{
	unsigned int digit;
	in >> digit;
	if (!BCDDigit::isValidBCD(digit))
	{
		throw new std::invalid_argument("Invalid BCD");
	}
	num.digit = digit;
	return in;
}
#endif // !_BCDDigit