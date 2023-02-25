/*
Sample File:
5
Fe + Cl2 = FeCl3
KMnO4 + HCl = KCl + MnCl2 + H2O + Cl2
C8H18 + O2 = CO2 + H2O
Fe2(SO4)3 KSCN = K3Fe(SCN)6 K2SO4
CO2 = CO

Sample Run:

Enter the file name: balequation.txt

E1: 2Fe + 3Cl2 = 2FeCl3
E2: 2KMnO4 + 16HCl = 2KCl + 2MnCl2 + 8H2O + 5Cl2
E3: 2C8H18 + 25O2 = 16CO2 + 18H2O
E4: Fe2(SO4)3 + 12KSCN = 2K3Fe(SCN)6 + 3K2SO4
E5: Cannot Balance
 */

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
    // Parse the equation into its two sides
    int i = 0;
    string left = "";
    string right = "";
    while (i < equation.length() && equation[i] != '=')
    {
        left += equation[i];
        i++;
    }
    i++;
    while (i < equation.length())
    {
        right += equation[i];
        i++;
    }

    // Parse the two sides into their elements and coefficients
    unordered_map<string, int> leftElements = parseCompound(left);
    unordered_map<string, int> rightElements = parseCompound(right);

    // Check if the two sides have the same elements
    if (leftElements.size() != rightElements.size())
    {
        return false;
    }
    for (auto it = leftElements.begin(); it != leftElements.end(); it++)
    {
        if (rightElements.find(it->first) == rightElements.end())
        {
            return false;
        }
    }

    // Check if the two sides have the same coefficients for each element
    for (auto it = leftElements.begin(); it != leftElements.end(); it++)
    {
        if (rightElements[it->first] != it->second)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    // Read the input file
    string fileName;
    cout << "Enter the file name: ";
    cin >> fileName;
    ifstream fin(fileName);

    // Read the number of equations
    int n;
    fin >> n;

    // Read the equations and check if they are balanced
    string equation;
    getline(fin, equation);
    for (int i = 0; i < n; i++)
    {
        getline(fin, equation);
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

    return 0;
}