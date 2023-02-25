#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <numeric>

using namespace std;

// Function to parse a compound string into its elements and coefficients
unordered_map<string, int> parseCompound(string compound)
{
    unordered_map<string, int> elements;
    string element = "";
    int coeff = 1;

    for (int i = 0; i < compound.length(); i++)
    {
        if (isupper(compound[i]))
        {
            // Start of a new element
            if (element != "")
            {
                // Update the map with the previous element and its coefficient
                elements[element] += coeff;
                element = "";
                coeff = 1;
            }
            element += compound[i];
        }
        else if (islower(compound[i]))
        {
            // Continuation of the previous element
            element += compound[i];
        }
        else if (isdigit(compound[i]))
        {
            // Coefficient of the current element
            coeff = compound[i] - '0';
            while (i + 1 < compound.length() && isdigit(compound[i + 1]))
            {
                // Handle multi-digit coefficients
                coeff = coeff * 10 + (compound[i + 1] - '0');
                i++;
            }
        }
        else if (compound[i] == '(')
        {
            // Start of a compound within parenthesis
            string subCompound = "";
            int j = i + 1;
            int count = 1;
            while (count != 0)
            {
                if (compound[j] == '(')
                {
                    count++;
                }
                else if (compound[j] == ')')
                {
                    count--;
                }
                subCompound += compound[j];
                j++;
            }
            i = j - 1;

            unordered_map<string, int> subElements = parseCompound(subCompound);
            for (auto it = subElements.begin(); it != subElements.end(); it++)
            {
                elements[it->first] += it->second * coeff;
            }
        }
    }

    // Handle the last element
    elements[element] += coeff;

    return elements;
}

// Function to check if a given equation is balanced
bool isBalanced(string equation)
{
    // Split the equation into left and right sides
    int equalSign = equation.find('=');
    string left = equation.substr(0, equalSign);
    string right = equation.substr(equalSign + 1);

    // Parse the left and right sides into their elements and coefficients
    vector<unordered_map<string, int>> leftElements;
    vector<unordered_map<string, int>> rightElements;
    string compound = "";
    for (int i = 0; i < left.length(); i++)
    {
        if (left[i] == '+')
        {
            leftElements.push_back(parseCompound(compound));
            compound = "";
        }
        else
        {
            compound += left[i];
        }
    }
    leftElements.push_back(parseCompound(compound));
    compound = "";
    for (int i = 0; i < right.length(); i++)
    {
        if (right[i] == '+')
        {
            rightElements.push_back(parseCompound(compound));
            compound = "";
        }
        else
        {
            compound += right[i];
        }
    }
    rightElements.push_back(parseCompound(compound));

    // Check if the equation is balanced
    unordered_map<string, int> leftMap;
    unordered_map<string, int> rightMap;
    for (int i = 0; i < leftElements.size(); i++)
    {
        for (auto it = leftElements[i].begin(); it != leftElements[i].end(); it++)
        {
            leftMap[it->first] += it->second;
        }
    }
    for (int i = 0; i < rightElements.size(); i++)
    {
        for (auto it = rightElements[i].begin(); it != rightElements[i].end(); it++)
        {
            rightMap[it->first] += it->second;
        }
    }
    if (leftMap.size() != rightMap.size())
    {
        return false;
    }
    for (auto it = leftMap.begin(); it != leftMap.end(); it++)
    {
        if (rightMap.find(it->first) == rightMap.end() || rightMap[it->first] != it->second)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    // Get the file name from the user
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;

    // Open the file
    ifstream file(fileName);
    if (!file.is_open())
    {
        cout << "Cannot open file " << fileName << endl;
        return 1;
    }

    // Read the number of equations
    int numEquations;
    file >> numEquations;

    // Read each equation and check if it is balanced
    string equation;
    getline(file, equation);
    for (int i = 0; i < numEquations; i++)
    {
        getline(file, equation);
        cout << "E" << i + 1 << ": ";
        if (isBalanced(equation))
        {
            cout << equation << endl;
        }
        else
        {
            cout << "Cannot Balance" << endl;
        }
    }

    file.close();
    return 0;
}