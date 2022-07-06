#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    const string outputFile = "StudentData.txt";
    string myData;

    ofstream outputFile;
    
    outputFile.open(outputFile, ios::out);

    outputFile << "What is your full name? ";
    cin >> myData;
    outputFile << endl;

    outputFile << "What is the street you're in? ";
    cin >> myData;
    outputFile << endl;

    outputFile << "What is the second street you're in? ";
    cin >> myData;
    outputFile << endl;

    outputFile << "What city are you in? ";
    cin >> myData;
    outputFile << endl;

    outputFile << "What state are you in? ";
    cin >> myData;
    outputFile << endl;

    outputFile << "What is your zip code? ";
    cin >> myData;
    outputFile << endl;

    outputFile.close();
    return 0;
}