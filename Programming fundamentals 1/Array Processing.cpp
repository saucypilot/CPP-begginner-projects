#include <iostream>
#include <string>
using namespace std;

const short MAX_MONTHS = 12;
const string MONTHS[MAX_MONTHS] = { "January", "February","March","April","May","June","July","August","September","October","November","December" };

void showMonths()
{
	int i;
	for (i = 0; i < MAX_MONTHS; i++)
	{
		cout << MONTHS[i] << endl;
	}
}

string getMonth(int month)
{
	month--;
	if (month >= 0 && month <= 11) {
		return MONTHS[month];
	}
	else {
		return "Invalid";
	}
}

int main()
{
	showMonths();
	cout << "Enter a month number 1-12: ";

	int userNumber;
	cin >> userNumber;

	getMonth(userNumber);
	cout << getMonth(userNumber) << endl << "Done!";
	return (0);
}