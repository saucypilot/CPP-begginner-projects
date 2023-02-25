#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <sstream>

using namespace std;

map<string, vector<pair<string, int>>> parseCompounds(string compounds)
{
    map<string, vector<pair<string, int>>> compoundMap;
    int i = 0;
    int j = 0;
    int len = compounds.length();
    string currentElement = "";
    string currentCompound = "";
    int currentCompoundCoeff = 1;
    while (i < len)
    {
        if (compounds[i] == '+')
        {
            compoundMap[currentCompound].push_back(make_pair(currentElement, currentCompoundCoeff));
            currentElement = "";
            currentCompoundCoeff = 1;
            i++;
            continue;
        }
        else if (compounds[i] == '=')
        {
            compoundMap[currentCompound].push_back(make_pair(currentElement, currentCompoundCoeff));
            currentElement = "";
            currentCompoundCoeff = 1;
            currentCompound = "";
            i++;
            continue;
        }
        else if (compounds[i] == '(')
        {
            if (currentElement != "")
            {
                compoundMap[currentCompound].push_back(make_pair(currentElement, currentCompoundCoeff));
            }
            currentElement = "";
            i++;
            int k = i;
            int openParens = 1;
            while (openParens > 0)
            {
                if (compounds[k] == '(')
                {
                    openParens++;
                }
                else if (compounds[k] == ')')
                {
                    openParens--;
                }
                k++;
            }
            map<string, vector<pair<string, int>>> subCompoundMap = parseCompounds(compounds.substr(i, k - i - 1));
            i = k;
            if (k < len && isdigit(compounds[k]))
            {
                currentCompoundCoeff = compounds[k] - '0';
                k++;
                while (k < len && isdigit(compounds[k]))
                {
                    currentCompoundCoeff = currentCompoundCoeff * 10 + (compounds[k] - '0');
                    k++;
                }
                i = k;
            }
            for (auto subCompound : subCompoundMap)
            {
                string subCompoundName = subCompound.first;
                for (auto element : subCompound.second)
                {
                    compoundMap[currentCompound].push_back(make_pair(element.first, element.second * currentCompoundCoeff));
                }
            }
            continue;
        }
        else if (compounds[i] == ')')
        {
            if (currentElement != "")
            {
                compoundMap[currentCompound].push_back(make_pair(currentElement, currentCompoundCoeff));
            }
            break;
        }
        else if (isupper(compounds[i]))
        {
            if (currentElement != "")
            {
                compoundMap[currentCompound].push_back(make_pair(currentElement, currentCompoundCoeff));
            }
            currentElement = compounds.substr(i, 1);
            i++;
            if (i < len && islower(compounds[i]))
            {
                currentElement += compounds.substr(i, 1);
                i++;
            }
            if (i < len && isdigit(compounds[i]))
            {
                currentCompoundCoeff = compounds[i] - '0';
                i++;
                while (i < len && isdigit(compounds[i]))
                {
                    currentCompoundCoeff = currentCompoundCoeff * 10 + (compounds[i] - '0');
                    i++;
                }
            }
        }
        else if (isdigit(compounds[i]))
        {
            currentCompoundCoeff = compounds[i] - '0';
            i++;
            while (i < len && isdigit(compounds[i]))
            {
                currentCompoundCoeff = currentCompoundCoeff * 10 + (compounds[i] - '0');
                i++;
            }
        }
    }
    if (currentElement != "")
    {
        compoundMap[currentCompound].push_back(make_pair(currentElement, currentCompoundCoeff));
    }
    return compoundMap;
}

int main()
{
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;
    ifstream file(fileName);
    int numEquations;
    file >> numEquations;
    file.ignore();
    for (int i = 0; i < numEquations; i++)
    {
        string equation;
        getline(file, equation);
        map<string, vector<pair<string, int>>> compoundMap = parseCompounds(equation);
        map<string, int> elementMap;
        for (auto compound : compoundMap)
        {
            for (auto element : compound.second)
            {
                elementMap[element.first] += element.second;
            }
        }
        int gcd = 1;
        for (auto element : elementMap)
        {
            gcd = __gcd(gcd, element.second);
        }
        if (gcd == 0)
        {
            cout << "E" << i + 1 << ": Cannot Balance" << endl;
        }
        else
        {
            cout << "E" << i + 1 << ": ";
            int j = 0;
            for (auto compound : compoundMap)
            {
                if (j > 0)
                {
                    cout << " + ";
                }
                if (compound.first == "")
                {
                    cout << " = ";
                }
                else
                {
                    if (compound.second[0].second > 1)
                    {
                        cout << compound.second[0].second / gcd << compound.first;
                    }
                    else
                    {
                        cout << compound.first;
                    }
                    for (int k = 1; k < compound.second.size(); k++)
                    {
                        if (compound.second[k].second > 1)
                        {
                            cout << compound.second[k].second / gcd << compound.second[k].first;
                        }
                        else
                        {
                            cout << compound.second[k].first;
                        }
                    }
                }
                j++;
            }
            cout << endl;
        }
    }
    return 0;
}