#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    double nums, sum;
    ifstream inputFile;

    inputFile.open("Week10a.dat", ios::in);
    while (inputFile >> nums)
    {
        sum = sum + nums;
    }
    inputFile.close();
    cout<<sum;
    cout<<setprecision(2)<<fixed<<"The current balance is "<<sum<<".";

	return 0;
}