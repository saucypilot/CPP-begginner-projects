#include <iostream>
using namespace std;

int main(){
    int amount;
    int numOFmonths;
    int currentMonths = 0;
    int balance = 0;

///prompting the user
    cout << "Enter amount to save each month:";
    cin >> amount;
    cout << "Enter the number of months to save:";
    cin >> numOFmonths;
    cout << endl;

//Outputting
    do
    {   balance += amount;
        currentMonths += 1;
        cout << "For month " << currentMonths << ", the balance is " << balance << endl;
    } while (currentMonths < numOFmonths);
    
    cout << endl << "End of Program";

    return 0;
}