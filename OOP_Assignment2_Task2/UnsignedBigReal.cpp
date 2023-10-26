#ifndef _UnsignedBigReal
#define _UnsignedBigReal

#include <iostream>
#include <string>
#include <deque>
#include "BCDDigit.cpp"
#include "PackedBCD.cpp"
using namespace std;

class UnsignedBigReal
{
public:
	UnsignedBigReal(string realNumber);
	UnsignedBigReal(const char* realNumber) : UnsignedBigReal(string(realNumber)) {}
	UnsignedBigReal(double realNumber = 0.0) :UnsignedBigReal(to_string(realNumber)) {};
	UnsignedBigReal(const UnsignedBigReal& other);
	void setNum(string realNumber);
	int size();
	/*
	UnsignedBigReal operator- (UnsignedBigReal& other);
	*/
	UnsignedBigReal operator+(UnsignedBigReal& other);
	bool operator>= (UnsignedBigReal anotherReal);
	bool operator<= (UnsignedBigReal anotherReal);
	bool operator> (UnsignedBigReal anotherReal);
	bool operator< (UnsignedBigReal anotherReal);
	bool operator!= (UnsignedBigReal anotherReal);
	bool operator== (UnsignedBigReal anotherReal);
	friend istream& operator >> (istream& in, UnsignedBigReal &num);
	friend ostream& operator << (ostream& out, UnsignedBigReal num);

private:
	deque<PackedBCD> integer;
	deque<PackedBCD> fraction;
	bool isValidUnsignedReal(string realNumber);
	PackedBCD* at(int pos);
	// Removes extra zeros
	void clean();
	// 1 if > , 0 if == , -1 if <
	static int compare(UnsignedBigReal &r, UnsignedBigReal &l);
	// add zeros to the right or to the left until both numbers have similar size
	static void normalize(UnsignedBigReal& r, UnsignedBigReal& l);
};
UnsignedBigReal::UnsignedBigReal(string realNumber)
{
	setNum(realNumber);
}
UnsignedBigReal::UnsignedBigReal(const UnsignedBigReal& other)
{
	integer = deque<PackedBCD>(other.integer);
	fraction = deque<PackedBCD>(other.fraction);
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
		if (i - 1 >= 0)
		{
			PackedBCD p = PackedBCD(integerNumber[i] - '0', integerNumber[i - 1] - '0');
			integer.push_front(p);
			i--;
		}
		else
		{
			PackedBCD p = PackedBCD(integerNumber[i] - '0');
			integer.push_front(p);
		}
	}
	for (int i = 0; i < fractionNumber.length(); i++)
	{
		if (i + 1 < fractionNumber.length())
		{
			PackedBCD p = PackedBCD(fractionNumber[i + 1] - '0', fractionNumber[i] - '0');
			fraction.push_back(p);
			i++;
		}
		else
		{
			PackedBCD p = PackedBCD(0, fractionNumber[i] - '0');
			fraction.push_back(p);
		}
	}
	clean();
}
int UnsignedBigReal::size()
{
	int size =  integer.size() + fraction.size();
	size *= 2;
	if (integer.size() != 0)
	{
		size += integer[0].digitCount() - 2;
	}
	if (fraction.size() != 0)
	{
		PackedBCD lastDigit = fraction[fraction.size() - 1];
		if ((lastDigit.getNumber() % 10) == 0)
		{
			size--;
		}
	}
	return size;
}
UnsignedBigReal UnsignedBigReal::operator+(UnsignedBigReal& other)
{
	normalize(*this, other);
	UnsignedBigReal result;
	BCDDigit carry;
	for (int i = fraction.size() - 1; i >= 0; i--)
	{
		PackedBCD s = PackedBCD::add(fraction[i], other.fraction[i], carry, carry);
		result.fraction.push_front(s);
	}
	for (int i = integer.size() - 1; i >= 0; i--)
	{
		PackedBCD s = PackedBCD::add(integer[i], other.integer[i], carry, carry);
		result.integer.push_front(s);
	}
	result.integer.push_front(carry);
	clean();
	other.clean();
	result.clean();
	return result;
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
	if (integer.size() != anotherReal.integer.size() || fraction.size() != anotherReal.fraction.size())
	{
		return true;
	}
	for (int i = 0; i < integer.size(); i++)
	{
		if (integer[i] != anotherReal.integer[i])
		{
			return true;
		}
	}
	for (int i = 0; i < fraction.size(); i++)
	{
		if (fraction[i] != anotherReal.fraction[i])
		{
			return true;
		}
	}
	return false;
}
bool UnsignedBigReal::operator==(UnsignedBigReal anotherReal)
{
	if (integer.size() != anotherReal.integer.size() || fraction.size() != anotherReal.fraction.size())
	{
		return false;
	}
	for (int i = 0; i < integer.size(); i++)
	{
		if (integer[i] != anotherReal.integer[i])
		{
			return false;
		}
	}
	for (int i = 0; i < fraction.size(); i++)
	{
		if (fraction[i] != anotherReal.fraction[i])
		{
			return false;
		}
	}
	return true;
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

PackedBCD* UnsignedBigReal::at(int pos)
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
		out << num.integer[0].getNumber();
		for (int i = 1; i < num.integer.size(); i++)
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
		for (int i = 0; i < num.fraction.size() - 1; i++)
		{
			out << num.fraction[i];
		}
		PackedBCD lastDigit = num.fraction[num.fraction.size() - 1];
		if ((lastDigit.getNumber() % 10) == 0)
		{
			out << lastDigit.getNumber() / 10;
		}
		else
		{
			out << lastDigit;
		}

	}
	return out;
}


#endif // !_UnsignedBigReal
