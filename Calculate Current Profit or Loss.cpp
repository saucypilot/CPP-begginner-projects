/* Given: A 40 bottle case of wine was purchased for $2000.
       A cold storage fee is $15 per day for the case. 
       These bottles will are to be sold at a single future event and will be in cold storage until the event.  
       Any unsold bottles are considered spoilage. */

#include <iostream>
using namespace std;

int main(){
    int numSold; //number of bottles sold
    float sellingPrice; //selling price of the bottles
    int days; //number of days in storage
    int profit; //the profit or loss.
    
    //Prompting
    cout<<"What is the selling price of a bottle: ";
    cin>>sellingPrice;

    cout<<"What is the number of bottles sold (0-40): ";
    cin>>numSold;

    cout<<"How many number of days in storage: "; 
    cin>>days;

    //Calculation
    profit= numSold * sellingPrice - (days * 15) - 2000;

    //Output
    cout<<"The price of a current bottle is "<<sellingPrice<<endl;
    cout<<"The number of bottles sold is "<<numSold<<endl;
    cout<<"The current profit or loss is calculated to be "<<profit;
}