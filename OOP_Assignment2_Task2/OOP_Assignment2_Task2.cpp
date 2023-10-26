// OOP_Assignment2_Task2.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "BCDDigit.cpp"
#include "PackedBCD.cpp"

using namespace std;

int main()
{	
	PackedBCD p = 10;
	cout << p << endl << p.get9Compliment();
}
