#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    const string FILE_NAME = "StudentData.txt";
    string myData;

    ofstream outputFile;
    
    outputFile.open(FILE_NAME, ios::out);

    FILE_NAME << "What is your full name? ";
    cin >> myData;
    FILE_NAME << endl;

    FILE_NAME << "What is the street you're in? ";
    cin >> myData;
    FILE_NAME << endl;

    FILE_NAME << "What is the second street you're in? ";
    cin >> myData;
    FILE_NAME << endl;

    FILE_NAME << "What city are you in? ";
    cin >> myData;
    FILE_NAME << endl;

    FILE_NAME << "What state are you in? ";
    cin >> myData;
    FILE_NAME << endl;

    FILE_NAME << "What is your zip code? ";
    cin >> myData;
    FILE_NAME << endl;

    outputFile.close();
    return 0;
}