// OOP_Assignment2_Task2.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "BCDDigit.cpp"
#include "UnsignedBigReal.cpp"
#include <random>
#include "BigReal.cpp"

using namespace std;

int main()
{
	BigReal x, y;
	cin >> x >> y;
	if (x < y)
	{
		cout << x << " < " << y << endl;
	}
	if (x > y)
	{
		cout << x << " > " << y << endl;
	}
	if (x == y)
	{
		cout << x << " = " << y << endl;
	}
	cout << x << " + " << y << " = " << (x + y) << endl;
	cout << x << " - " << y << " = " << (x - y) << endl;
}
