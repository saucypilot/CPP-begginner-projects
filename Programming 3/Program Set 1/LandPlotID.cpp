#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

int main()
{
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;
    cout << endl;
    ifstream inFile;
    inFile.open(fileName);
    if (!inFile)
    {
        cout << "Unable to open file";
        exit(1);
    }
    int numSurveys;
    inFile >> numSurveys;
    inFile.ignore();
    for (int i = 0; i < numSurveys; i++)
    {
        vector<int> plotCounts;
        for (int row = 0; row < 8; row++)
        {
            int unclaimedPlotsInRow = 0;
            for (int col = 0; col < 16; col++)
            {
                char c = inFile.get();
                if (c == '*')
                {
                    unclaimedPlotsInRow++;
                }
            }
            inFile.ignore(); // ignore newline character
            plotCounts.push_back(unclaimedPlotsInRow);
        }
        sort(plotCounts.rbegin(), plotCounts.rend());
        cout << "Survey " << i + 1 << ": ";
        for (int j = 0; j < plotCounts.size(); j++)
        {
            cout << plotCounts[j] * 5 << " ";
        }
        cout << endl;
        inFile.ignore(); // ignore blank line
    }
    inFile.close();
    return 0;
}