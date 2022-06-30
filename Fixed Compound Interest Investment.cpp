#include <iostream>
#include <iomanip>
using namespace std;

int main(){
    double balance;
    int years;
    int perYear;
    double apr;

    cout<<"Enter Balance: ";
    cin>>balance;
    cout<<"Enter Interest Rate: ";
    cin>>apr;
    cout<<"Enter years: ";
    cin>>years;
    cout<<endl;

    cout<<"Year   Balance";
    for(perYear=0; perYear<=years; perYear++){
        cout << fixed << setprecision(2)<< perYear << "        "<< balance << endl;
        balance = balance * ( 1 + apr) ; 
    }
    cout<<endl<<"Done!";
    return 0;
}