#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

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
        vector<int> v;
        string line;
        for (int j = 0; j < 8; j++)
        {
            getline(inFile, line);
            int count = 0;
            for (int k = 0; k < 16; k++)
            {
                if (line[k] == '*')
                {
                    count++;
                }
                else
                {
                    if (count > 0)
                    {
                        v.push_back(count);
                        count = 0;
                    }
                }
            }
            if (count > 0)
            {
                v.push_back(count);
            }
        }
        sort(v.begin(), v.end(), greater<int>());
        cout << "Survey " << i + 1 << ": ";
        for (int j = 0; j < v.size(); j++)
        {
            cout << v[j] * 5 << " ";
        }
        cout << endl;
        getline(inFile, line);
    }
    inFile.close();
    return 0;
}