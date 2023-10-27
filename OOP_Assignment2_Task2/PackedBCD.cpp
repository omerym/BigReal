#ifndef _PackedBCD
#define _PackedBCD

#include <iostream>
#include "BCDDigit.cpp"

using namespace std;

class PackedBCD
{
public:
	PackedBCD(BCDDigit first = 0, BCDDigit second = 0);
	PackedBCD(unsigned int value);
	static PackedBCD add(PackedBCD r, PackedBCD l, BCDDigit &carryOut, BCDDigit carryIn = 0);
	int digitCount();
	unsigned int getNumber();
	PackedBCD get9Compliment();
	PackedBCD operator+ (PackedBCD other);
	bool operator == (PackedBCD other);
	bool operator != (PackedBCD other);
	bool operator > (PackedBCD other);
	bool operator < (PackedBCD other);
	bool operator <= (PackedBCD other);
	bool operator >= (PackedBCD other);
	friend ostream& operator << (ostream& out, PackedBCD num);
	friend istream& operator >> (istream& in, PackedBCD& num);

private:
	void pack(BCDDigit first, BCDDigit second = 0);
	void unPack(BCDDigit& first, BCDDigit& second);
	unsigned char data;
};

PackedBCD::PackedBCD(BCDDigit first, BCDDigit second)
{
	pack(first, second);
}

PackedBCD::PackedBCD(unsigned int value)
{
	if (value >= 100)
	{
		throw new std::invalid_argument("Invalid BCD");
	}
	pack(value % 10, value / 10);
}

PackedBCD PackedBCD::add(PackedBCD r, PackedBCD l, BCDDigit &carryOut, BCDDigit carryIn)
{
	BCDDigit a1, a2, b1, b2;
	r.unPack(a1, a2);
	l.unPack(b1, b2);
	a1 = BCDDigit::add(a1, b1, carryOut, carryIn);
	a2 = BCDDigit::add(a2, b2, carryOut, carryOut);
	return PackedBCD(a1, a2);
}

int PackedBCD::digitCount()
{
	BCDDigit first, second;
	unPack(first, second);
	if (second == 0)
	{
		return 1;
	}
	return 2;
}

unsigned int PackedBCD::getNumber()
{
	BCDDigit first, second;
	unPack(first, second);
	return first.getDigit() + second.getDigit() * 10;
}

PackedBCD PackedBCD::get9Compliment()
{
	BCDDigit first, second;
	unPack(first, second);
	return PackedBCD(first.get9Compliment(),second.get9Compliment());
} 

PackedBCD PackedBCD::operator+(PackedBCD other)
{
	BCDDigit c;
	return add(*this, other, c);
}

bool PackedBCD::operator==(PackedBCD other)
{
	return data == other.data;
}

bool PackedBCD::operator!=(PackedBCD other)
{
	return data != other.data;
}

bool PackedBCD::operator>(PackedBCD other)
{
	return data > other.data;
}

bool PackedBCD::operator<(PackedBCD other)
{
	return data < other.data;
}

bool PackedBCD::operator<=(PackedBCD other)
{
	return data <= other.data;
}

bool PackedBCD::operator>=(PackedBCD other)
{
	return data >= other.data;
}

void PackedBCD::pack(BCDDigit first, BCDDigit second)
{
	data = first.getDigit() + (second.getDigit() << 4);
}

void PackedBCD::unPack(BCDDigit& first, BCDDigit& second)
{
	first = data & 0b1111;
	second = data >> 4;
}

ostream& operator<<(ostream& out, PackedBCD num)
{
	BCDDigit first, second;
	num.unPack(first, second);
	out << second << first;
	return out;
}

istream& operator>>(istream& in, PackedBCD& num)
{
	unsigned int x;
	in >> x;
	if (x >= 100)
	{
		throw new std::invalid_argument("Invalid BCD");
	}
	num.pack(x % 10, x / 10);
	return in;
}

#endif // !_PackedBCD
