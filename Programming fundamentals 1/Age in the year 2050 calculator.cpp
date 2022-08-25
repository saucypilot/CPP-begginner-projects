#include <iostream>
using namespace std;

//This is a program that will estimate my age in the year 2050.

int main() {
	const string name = "Irian";
	const int YEAR_FUTURE = 2050;
	int currentYear = 2022;
	int myAge = 20;
	int ageInFuture = myAge + (YEAR_FUTURE - currentYear);
	cout << "My Name is " << name << " and I will be " << ageInFuture << " in the year " << YEAR_FUTURE << ".";
}
