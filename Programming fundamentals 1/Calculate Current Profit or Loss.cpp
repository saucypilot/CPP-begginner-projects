#include <iostream>
using namespace std;

int main(){
    int numSold; //number of bottles sold
    float sellingPrice; //selling price of the bottles
    int days; //number of days in storage
    float profit; //the profit or loss.

    const int PER_DAY_FEE = 15;
    const int CASE_COST = 2000;
    
    //Prompting
    cout<<"What is the selling price of a bottle: ";
    cin>>sellingPrice;

    cout<<"What is the number of bottles sold (0-40): ";
    cin>>numSold;

    cout<<"How many number of days in storage: "; 
    cin>>days;

    //Calculation
    profit= numSold * sellingPrice - (days * perDayFee) - caseCost;

    //Output
    cout<<"The price of a current bottle is "<<setperciscion(2)<<sellingPrice<<endl;
    cout<<"The number of bottles sold is "<<numSold<<endl;
    cout<<"The current profit or loss is calculated to be "<<setperciscion(2)<<profit;
}