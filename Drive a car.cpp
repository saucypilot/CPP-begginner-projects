#include <iostream>
using namespace std;

void start(){
    cout<<"Start the Car"<<endl;}
void Find(){
    cout<<"Locate your Keys"<<endl;}
void Activate(){
    cout<<"Turn on your GPS"<<endl;}
void Drive(){
    cout<<"Drive to Destination"<<endl;}
void Buckle(){
    cout<<"Buckle up and adjust seat and mirrors"<<endl;}
void GC(){
    cout<<"Get inside the car"<<endl;}
void parked(string s){
    cout<<"My "<<s<<" is now parked";}
int main(){
    start();
    Find();
    Activate();
    Drive();
    Buckle();
    GC();

//string s="Rolls Royce";
    parked("Rolls Royce");
return 0;}