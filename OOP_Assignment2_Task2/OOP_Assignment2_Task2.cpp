// OOP_Assignment2_Task2.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "BCDDigit.cpp"
#include "PackedBCD.cpp"
#include "UnsignedBigReal.cpp"
#include <random>

using namespace std;

int main()
{	
	UnsignedBigReal x = "28753492650324563405630.1435781430671";
	for (int i = 0; i < 235283405; i++)
	{
		UnsignedBigReal y = "1321436342626263464214.432543126136";
		x = x + y + x + y;
		y = y + x;
		cout << x << endl;
	}
}
