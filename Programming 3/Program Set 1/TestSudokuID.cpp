/*
Write a program to balance chemical equations. An equation is comprised of a list of compounds and elements, 
separated by plus-signs, on both sides of an equal sign. An element will be represented by either one or two letters; 
the first is always capitalized, and if the element has a second character, it will be lowercase. Compounds are composed of 
several elements added together that may have parenthesis around them and with a number following each element. 
This number represents the number of atoms of the element in front of the number in the compound. If there is only one 
atom of an element in the compound, no number will appear after the element. The result is m the lowest number of integer 
coefficients for each compound needed so the equation is balanced. An equation is balanced when the number of atoms of each 
element on the left side is equal to that of the right side. Coefficients are applied to the complete compound; so, a 
coefficient of two for FeCl represents two atoms of Fe and two atoms of Cl. Input is from a text file, where the first 
line contains an integer N between $[1,30]$. The following N lines define equations according to the rules described above. 
For each labeled equation, output to the screen the balanced equation with the lowest integer number coefficients. If an 
equation cannot be balanced correctly or uniquely, output the words "Cannot Balance".
Let the user enter the file namefrom the keyboard. Refer to the sample output below.
 */
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <sstream>
#include <iomanip>
using namespace std;

int main()
{
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
    int n;
    inFile >> n;
    inFile.ignore();
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(inFile, line);
        int pos = line.find("=");
        string left = line.substr(0, pos);
        string right = line.substr(pos + 1);
        map<string, int> m;
        istringstream iss(left);
        string s;
        while (getline(iss, s, '+'))
        {
            int pos = s.find("(");
            if (pos != string::npos)
            {
                int pos2 = s.find(")");
                string s2 = s.substr(pos + 1, pos2 - pos - 1);
                int num = stoi(s.substr(pos2 + 1));
                istringstream iss2(s2);
                string s3;
                while (getline(iss2, s3, '+'))
                {
                    int pos3 = s3.find_first_of("0123456789");
                    if (pos3 != string::npos)
                    {
                        int num2 = stoi(s3.substr(pos3));
                        string s4 = s3.substr(0, pos3);
                        m[s4] += num * num2;
                    }
                    else
                    {
                        m[s3] += num;
                    }
                }
            }
            else
            {
                int pos2 = s.find_first_of("0123456789");
                if (pos2 != string::npos)
                {
                    int num2 = stoi(s.substr(pos2));
                    string s4 = s.substr(0, pos2);
                    m[s4] += num2;
                }
                else
                {
                    m[s] += 1;
                }
            }
        }
        istringstream iss2(right);
        while (getline(iss2, s, '+'))
        {
            int pos = s.find("(");
            if (pos != string::npos)
            {
                int pos2 = s.find(")");
                string s2 = s.substr(pos + 1, pos2 - pos - 1);
                int num = stoi(s.substr(pos2 + 1));
                istringstream iss2(s2);
                string s3;
                while (getline(iss2, s3, '+'))
                {
                    int pos3 = s3.find_first_of("0123456789");
                    if (pos3 != string::npos)
                    {
                        int num2 = stoi(s3.substr(pos3));
                        string s4 = s3.substr(0, pos3);
                        m[s4] -= num * num2;
                    }
                    else
                    {
                        m[s3] -= num;
                    }
                }
            }
            else
            {
                int pos2 = s.find_first_of("0123456789");
                if (pos2 != string::npos)
                {
                    int num2 = stoi(s.substr(pos2));
                    string s4 = s.substr(0, pos2);
                    m[s4] -= num2;
                }
                else
                {
                    m[s] -= 1;
                }
            }
        }
        bool flag = true;
        for (auto it = m.begin(); it != m.end(); it++)
        {
            if (it->second != 0)
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            cout << "Equation #" << i + 1 << ": " << line << endl;
        }
        else
        {
            cout << "Equation #" << i + 1 << ": Cannot Balance" << endl;
        }
    }
    return 0;
}