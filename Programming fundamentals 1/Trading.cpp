#include <iostream>
using namespace std;

int main()
{
    char menuChoice;

//Outputs the choices
    cout<<" ********************************************************************************"<<endl;
    cout<<"     A. Buy Bonds                B. Sell Bonds"<<endl<<endl;
    cout<<"     C. Buy Stocks               D. Sell Stocks       E. Short Stock Sale"<<endl<<endl;
    cout<<"     X. Exit"<<endl<<endl;

//Prompt the user for a choice
    cout<<"From the menu above, choose how you want to interact with the trade by entering the letter of your corressponding choice."<<endl;
    cout<<"(Make sure it's capitalize)"<<endl<<endl;
    cout<<"Enter here: ";
    cin>>menuChoice;
    cout<<endl;

//Displays what the user selected
    switch(menuChoice){
        case 'A':
            cout<<"A. User selected Buy Bonds";
            break;
        case 'B':
            cout<<"B. User selected Sell Bonds";
            break;
        case 'C':
            cout<<"C. User selected Buy Stocks";
            break;
        case 'D':
            cout<<"D. User selected Sell Stocks";
            break;
        case 'E':
            cout<<"E. User selected Short Stock Sale";
            break;
        case 'X':
            cout<<"X. User selected Exit";
            break;

        default:
            cout<<"Invalid choice";
            return 5;
    }

    cout<<endl<<"Done!";
    return 0;
}