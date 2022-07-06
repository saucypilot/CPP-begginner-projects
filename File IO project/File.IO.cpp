#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    const string FILE_NAME = "StudentData.txt";
    string myData;

    ofstream outputFile;
    
    outputFile.open(FILE_NAME, ios::out);

    cout << "What is your full name? ";
    cin >> myData;
    cout << endl;

    cout << "What is the street you're in? ";
    cin >> myData;
    cout << endl;

    cout << "What is the second street you're in? ";
    cin >> myData;
    cout << endl;

    cout << "What city are you in? ";
    cin >> myData;
    cout << endl;

    cout << "What state are you in? ";
    cin >> myData;
    cout << endl;

    cout << "What is your zip code? ";
    cin >> myData;
    cout << endl;

    outputFile.close();
    return 0;
}