#include<iostream>
#include<string>
#include<fstream>
using namespace std;

const string FILE_NAME="StudentData.txt";
int main()
{

    string myData;
    ofstream outputFile;
    outputFile.open(FILE_NAME);

    cout<<"Enter Full Name :";
    getline(cin,myData);
    outputFile<<myData<<endl;
    cout<<"Enter Street 1 :";
    getline(cin,myData);
    outputFile<<myData<<endl;
    cout<<"Enter Street 2 :";
    getline(cin,myData);
    outputFile<<myData<<endl;
    cout<<"Enter City :";
    getline(cin,myData);
    outputFile<<myData<<endl;
    cout<<"Enter State Code :";
    getline(cin,myData);
    outputFile<<myData<<endl;
    cout<<"Enter Zip Code :";
    getline(cin,myData);
    outputFile<<myData<<endl;
    outputFile.close();

    cout<<endl<<endl;
    ifstream readFile;
    readFile.open(FILE_NAME);
    while(getline(readFile, myData))
    {
        cout << myData << endl;
    }
    readFile.close();
    return 0;
}