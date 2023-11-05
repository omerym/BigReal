#ifndef _UnsignedBigReal
#define _UnsignedBigReal

#include <iostream>
#include <string>
#include <deque>
#include "BCDDigit.cpp"
using namespace std;

class UnsignedBigReal
{
public:
	// 1 if > , 0 if == , -1 if <
	static int compare(UnsignedBigReal& r, UnsignedBigReal& l);
	static bool isValidUnsignedReal(string realNumber);
	UnsignedBigReal(string realNumber);
	UnsignedBigReal(const char* realNumber) : UnsignedBigReal(string(realNumber)) {}
	UnsignedBigReal(double realNumber = 0.0) :UnsignedBigReal(to_string(realNumber)) {};
	UnsignedBigReal(unsigned int realNumber) :UnsignedBigReal(to_string(realNumber)) {};
	UnsignedBigReal(int realNumber) :UnsignedBigReal(to_string(realNumber)) {};
	UnsignedBigReal(const UnsignedBigReal& other);
	void setNum(string realNumber);
	int digitCount();
	int size();
	UnsignedBigReal operator- (UnsignedBigReal other);
	UnsignedBigReal operator+(UnsignedBigReal other);
	bool operator>= (UnsignedBigReal anotherReal);
	bool operator<= (UnsignedBigReal anotherReal);
	bool operator> (UnsignedBigReal anotherReal);
	bool operator< (UnsignedBigReal anotherReal);
	bool operator!= (UnsignedBigReal anotherReal);
	bool operator== (UnsignedBigReal anotherReal);
	friend istream& operator >> (istream& in, UnsignedBigReal &num);
	friend ostream& operator << (ostream& out, UnsignedBigReal num);
	UnsignedBigReal getCompliment();
	BCDDigit GetSignValue(){
		return integer[0];
	}
private:
	deque<BCDDigit> integer;
	deque<BCDDigit> fraction;
	BCDDigit* at(int pos);
	UnsignedBigReal getZeros();
	UnsignedBigReal add(UnsignedBigReal other, bool ignoreCarry = false);
	// Removes extra zeros
	void clean();
	// add zeros to the right or to the left until both numbers have similar size
	static void normalize(UnsignedBigReal& r, UnsignedBigReal& l);
};
UnsignedBigReal::UnsignedBigReal(string realNumber)
{
	setNum(realNumber);
}
UnsignedBigReal::UnsignedBigReal(const UnsignedBigReal& other)
{
	integer = deque<BCDDigit>(other.integer);
	fraction = deque<BCDDigit>(other.fraction);
}
void UnsignedBigReal::setNum(string realNumber)
{
	integer.clear();
	fraction.clear();
	if (!isValidUnsignedReal(realNumber))
	{
		throw invalid_argument("invalid real number");
	}
	unsigned int dotPos = realNumber.find('.');
	string integerNumber = dotPos == 0 ? "" : realNumber.substr(0, dotPos);
	string fractionNumber = dotPos < realNumber.length() - 1 ? realNumber.substr(dotPos + 1) : "";
	for (int i = integerNumber.length() - 1; i >= 0; i--)
	{
		BCDDigit p = BCDDigit(integerNumber[i] - '0');
		integer.push_front(p);
	}
	for (int i = 0; i < fractionNumber.length(); i++)
	{
		BCDDigit p = BCDDigit(fractionNumber[i] - '0');
		fraction.push_back(p);

	}
	clean();
}
int UnsignedBigReal::digitCount()
{
	return integer.size() + fraction.size();
}
int UnsignedBigReal::size()
{
	return digitCount();
}
UnsignedBigReal UnsignedBigReal::operator-(UnsignedBigReal other)
{
	normalize(*this, other);
	UnsignedBigReal compliment = other.getCompliment();
	int compare = UnsignedBigReal::compare(*this, other);
	if (compare == -1)
	{
		throw underflow_error("Unsigned subtraction cannot have negative result.");
	}
	if (compare == 0)
	{
		return 0;
	}
	return add(compliment, true);
}
UnsignedBigReal UnsignedBigReal::operator+(UnsignedBigReal other)
{
	return add(other);
}
bool UnsignedBigReal::operator>=(UnsignedBigReal anotherReal)
{
	int c = compare(*this, anotherReal);
	return c >= 0;
}
bool UnsignedBigReal::operator<=(UnsignedBigReal anotherReal)
{
	int c = compare(*this, anotherReal);
	return c <= 0;
}
bool UnsignedBigReal::operator>(UnsignedBigReal anotherReal)
{
	return compare(*this, anotherReal) == 1;
}
bool UnsignedBigReal::operator<(UnsignedBigReal anotherReal)
{
	return compare(*this, anotherReal) == -1;
}
bool UnsignedBigReal::operator!=(UnsignedBigReal anotherReal)
{
	return compare(*this, anotherReal) != 0;
}
bool UnsignedBigReal::operator==(UnsignedBigReal anotherReal)
{
	return compare(*this, anotherReal) == 0;
}
UnsignedBigReal UnsignedBigReal::getCompliment()
{
	UnsignedBigReal x = *this, correction = getZeros();
	*correction.at(correction.digitCount() - 1) = 1;
	int start = digitCount() - 1;
	for (int i = start; i >= 0; i--)
	{
		*x.at(i) = x.at(i)->get9Compliment();
	}
	return x.add(correction,true);
}
bool UnsignedBigReal::isValidUnsignedReal(string realNumber)
{
	bool dotFound = false;
	for (int i = 0; i < realNumber.length(); i++)
	{
		if (realNumber[i] == '.')
		{
			if (dotFound)
			{
				return false;
			}
			dotFound = true;
		}
		else if (realNumber[i] > '9' || realNumber[i] < '0')
		{
			return false;
		}
	}
	return true;
}

BCDDigit* UnsignedBigReal::at(int pos)
{
	if (pos < integer.size())
	{
		return &integer[pos];
	}
	pos -= integer.size();
	if (pos < fraction.size())
	{
		return &fraction[pos];
	}
	throw out_of_range(to_string(pos));
}

UnsignedBigReal UnsignedBigReal::getZeros()
{
	UnsignedBigReal zeros;
	normalize(*this, zeros);
	return zeros;
}

UnsignedBigReal UnsignedBigReal::add(UnsignedBigReal other, bool ignoreCarry)
{
	normalize(*this, other);
	BCDDigit carry;
	int start = digitCount() - 1;
	for (int i = start; i >= 0; i--)
	{
		*other.at(i) = BCDDigit::add(*this->at(i), *other.at(i), carry, carry);
	}
	if (!ignoreCarry)
	{
		other.integer.push_front(carry);
	}
	clean();
	other.clean();
	return other;
}

void UnsignedBigReal::clean()
{
	for (int i = 0; i < integer.size(); i++)
	{
		if (integer[i] == 0)
		{
			integer.pop_front();
			i--;
		}
		else
		{
			break;
		}
	}
	for (int i = fraction.size() - 1; i >= 0; i--)
	{
		if (fraction[i] == 0)
		{
			fraction.pop_back();
		}
		else
		{
			break;
		}
	}
}

int UnsignedBigReal::compare(UnsignedBigReal &r, UnsignedBigReal &l)
{
	if (r.integer.size() > l.integer.size())
	{
		return 1;
	}
	if (r.integer.size() < l.integer.size())
	{
		return -1;
	}
	for (int i = 0; i < r.integer.size(); i++)
	{
		if (r.integer[i] > l.integer[i])
		{
			return 1;
		}
		if (r.integer[i] < l.integer[i])
		{
			return -1;
		}
	}
	int rFractionSize = r.fraction.size(), lFractionSize = l.fraction.size();
	int size = rFractionSize < lFractionSize ? rFractionSize : lFractionSize;
	for (int i = 0; i < size; i++)
	{
		if (r.fraction[i] > l.fraction[i])
		{
			return 1;
		}
		if (r.fraction[i] < l.fraction[i])
		{
			return -1;
		}
	}
	if (rFractionSize > lFractionSize)
	{
		return 1;
	}
	if (rFractionSize < lFractionSize)
	{
		return -1;
	}
	return 0;
}

void UnsignedBigReal::normalize(UnsignedBigReal& r, UnsignedBigReal& l)
{
	UnsignedBigReal& minInt = r.integer.size() < l.integer.size() ? r : l;
	UnsignedBigReal& maxInt = r.integer.size() >= l.integer.size() ? r : l;
	while (minInt.integer.size() < maxInt.integer.size())
	{
		minInt.integer.push_front(0);
	}
	UnsignedBigReal& minFrac = r.fraction.size() < l.fraction.size() ? r : l;
	UnsignedBigReal& maxFrac = r.fraction.size() >= l.fraction.size() ? r : l;
	while (minFrac.fraction.size() < maxFrac.fraction.size())
	{
		minFrac.fraction.push_back(0);
	}
}

istream& operator>>(istream& in, UnsignedBigReal& num)
{
	string s;
	in >> s;
	num.setNum(s);
	return in;
}

ostream& operator<<(ostream& out, UnsignedBigReal num)
{
	int integerDigitCount = num.integer.size();
	int fractionDigitCount = num.fraction.size();
	if (integerDigitCount == 0)
	{
		out << 0;
	}
	else
	{
		for (int i = 0; i < num.integer.size(); i++)
		{
			out << num.integer[i];
		}
	}
	out << '.';
	if (fractionDigitCount == 0)
	{
		out << 0;
	}
	else
	{
		for (int i = 0; i < num.fraction.size(); i++)
		{
			out << num.fraction[i];
		}

	}
	return out;
}

#endif // !_UnsignedBigReal
