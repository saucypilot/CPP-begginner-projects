// Assignment:
// Use the cout Stream Manipulators to produce the expect results for the numeric data
#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
//float values with variables
float mondayMaxTemp = 98.1;
float tuesdayMaxTemp = 94.9;
float wednesdayMaxTemp = 90.555;
float thursdayMaxTemp = 88.88;
float fridayMaxTemp = 87.9;

//Calculates the average tempenture
float computedAverageTemp = (mondayMaxTemp + tuesdayMaxTemp + wednesdayMaxTemp + thursdayMaxTemp + fridayMaxTemp)/5;

//Shows 2 decimal values using `fixed`
cout<<fixed<<setprecision(2);
//Outputs the temps
cout << "*********  Max Temperature for this Week  *******************" << endl;
cout << "   Monday  Tuesday   Wednesday   Thursday   Friday    Average" << endl;

cout << setw(9) << mondayMaxTemp << setw(9) << tuesdayMaxTemp << setw(12) << wednesdayMaxTemp << setw(11) << thursdayMaxTemp << setw(9) << fridayMaxTemp << setw(11) << computedAverageTemp << endl;

cout<<string(32, '-');

return (0);
}
