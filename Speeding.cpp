#include <iostream>
using namespace std;

int main(){
    int speedLimit;
    int currentSpeed;
    bool petrol;

    //Prompting the user
    cout<<"What is the speed limit(between 50 and 75mph)? ";
    cin>>speedLimit;

    cout<<endl<<"What is your current speed? ";
    cin>>currentSpeed;

    cout<<endl<<"Is the car a petrol car? (Enter 1 for true and 0 for false) ";
    cin>>petrol;
    cout<<endl;

    //Conditional if statements
    if(petrol==1){
        cout<<"Car is authorized at any speed";
    }
    else if(currentSpeed>speedLimit){
        cout<<"Car is currently speeding.";
        if(currentSpeed>=10+speedLimit){
            cout<<endl<<"Car may get a speeding ticket.";
        }
    }
    else if(currentSpeed<=35){
        cout<<"Car may be too slow for safe travel.";
    }
    return 0;
}