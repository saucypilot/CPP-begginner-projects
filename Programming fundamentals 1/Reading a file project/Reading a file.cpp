#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
using namespace std;

int main()
{
    ifstream inputFile;
    double nums;

    inputFile.open("Week10a.dat",ios::in);
    double sum = 0;

    while (inputFile>>nums) 
    {   
        sum += nums;
    }
    inputFile.close();
    
    cout<<setprecision(2)<<fixed<<"The current balance is "<<sum<<".";

	return 0;
}