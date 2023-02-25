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