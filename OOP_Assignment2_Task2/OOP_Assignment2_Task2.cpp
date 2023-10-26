// OOP_Assignment2_Task2.cpp : Defines the entry point for the application.
//

#include <iostream>
#include "BCDDigit.cpp"

using namespace std;

int main()
{
	BCDDigit t = 3;
	cout << (t + t.Get10Compliment());
}
