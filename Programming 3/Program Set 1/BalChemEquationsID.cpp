/*
Write a program to balance chemical equations. An equation is comprised of a list of compounds and elements, separated by plus-signs, on both sides of an equal sign. An element will be represented by either one or two letters; the first is always capitalized, and if the element has a second character, it will be lowercase. Compounds are composed of several elements added together that may have parenthesis around them and with a number following each element. This number represents the number of atoms of the element in front of the number in the compound. If there is only one atom of an element in the compound, no number will appear after the element. The result is m the lowest number of integer coefficients for each compound needed so the equation is balanced. An equation is balanced when the number of atoms of each element on the left side is equal to that of the right side. Coefficients are applied to the complete compound; so, a coefficient of two for FeCl represents two atoms of Fe and two atoms of Cl. Input is from a text file, where the first line contains an integer N between $[1,30]$. The following N lines define equations according to the rules described above. For each labeled equation, output to the screen the balanced equation with the lowest integer number coefficients. If an equation cannot be balanced correctly or uniquely, output the words "Cannot Balance". Let the user enter the file namefrom the keyboard. Refer to the sample output below.

Sample File:
```
5
Fe + Cl2 = FeCl3
KMnO4 + HCl = KCl + MnCl2 + H2O + Cl2
C8H18 + O2 = CO2 + H2O
Fe2(SO4)3 KSCN = K3Fe(SCN)6 K2SO4
CO2 = CO
```

Sample Run:
```
Enter the file name: balequation.txt

E1: 2Fe + 3Cl2 = 2FeCl3
E2: 2KMnO4 + 16HCl = 2KCl + 2MnCl2 + 8H2O + 5Cl2
E3: 2C8H18 + 25O2 = 16CO2 + 18H2O
E4: Fe2(SO4)3 + 12KSCN = 2K3Fe(SCN)6 + 3K2SO4
E5: Cannot Balance
```
 */

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>

using namespace std;

// Function to parse a chemical equation string into its constituent parts
void parseEquation(const std::string &equation, std::vector<std::map<std::string, int>> &compounds);

// Function to extract the elements and their counts from a compound string
void parseCompound(const std::string &compound, std::map<std::string, int> &elements);

// Function to balance a chemical equation
bool balanceEquation(std::vector<std::map<std::string, int>> &reactants,
                     std::vector<std::map<std::string, int>> &products,
                     std::vector<int> &coefficients);

// Function to print the balanced equation
void printBalancedEquation(const std::string &equation,
                           const std::vector<std::map<std::string, int>> &reactants,
                           const std::vector<std::map<std::string, int>> &products,
                           const std::vector<int> &coefficients);

// Function to print "Cannot Balance" message for unbalanced equations
void printCannotBalance(const std::string &equation);

int main()
{
    // Open the input file
    std::string filename;
    std::cout << "Enter the file name: ";
    std::cin >> filename;
    std::ifstream infile(filename);
    if (!infile)
    {
        std::cerr << "Error: Cannot open file " << filename << std::endl;
        return 1;
    }

    // Read the number of equations
    int numEquations;
    infile >> numEquations;

    // Read and balance each equation
    std::string equation;
    std::getline(infile, equation); // Skip the newline character
    for (int i = 0; i < numEquations; ++i)
    {
        // Read the equation
        std::getline(infile, equation);

        // Parse the equation into reactants and products
        std::vector<std::map<std::string, int>> reactants;
        std::vector<std::map<std::string, int>> products;
        parseEquation(equation, reactants);
        parseEquation(equation, products);

        // Balance the equation
        std::vector<int> coefficients;
        if (balanceEquation(reactants, products, coefficients))
        {
            // Print the balanced equation
            printBalancedEquation(equation, reactants, products, coefficients);
        }
        else
        {
            // Print "Cannot Balance" message
            printCannotBalance(equation);
        }
    }

    return 0;
}

// Function to parse a chemical equation string into its constituent parts
void parseEquation(const std::string &equation, std::vector<std::map<std::string, int>> &compounds)
{
    // Find the equal sign
    std::string::size_type equalSignPos = equation.find('=');

    // Parse the reactants
    std::string::size_type pos = 0;
    while (pos < equalSignPos)
    {
        // Find the next plus sign
        std::string::size_type plusSignPos = equation.find('+', pos);

        // Parse the compound
        std::map<std::string, int> elements;
        parseCompound(equation.substr(pos, plusSignPos - pos), elements);
        compounds.push_back(elements);

        // Move to the next compound
        pos = plusSignPos + 1;
    }

    // Parse the products
    pos = equalSignPos + 1;
    while (pos < equation.length())
    {
        // Find the next plus sign
        std::string::size_type plusSignPos = equation.find('+', pos);

        // Parse the compound
        std::map<std::string, int> elements;
        parseCompound(equation.substr(pos, plusSignPos - pos), elements);
        compounds.push_back(elements);

        // Move to the next compound
        pos = plusSignPos + 1;
    }
}

// Function to extract the elements and their counts from a compound string
void parseCompound(const std::string &compound, std::map<std::string, int> &elements)
{
    // Find the first parenthesis
    std::string::size_type leftParenPos = compound.find('(');

    // If there is no parenthesis, parse the compound as a single element
    if (leftParenPos == std::string::npos)
    {
        // Find the first digit
        std::string::size_type digitPos = compound.find_first_of("0123456789");

        // If there is no digit, the compound is a single element
        if (digitPos == std::string::npos)
        {
            elements[compound] = 1;
        }
        else
        {
            // Extract the element and its count
            std::string element = compound.substr(0, digitPos);
            int count = std::stoi(compound.substr(digitPos));
            elements[element] = count;
        }
    }
    else
    {
        // Find the matching right parenthesis
        std::string::size_type rightParenPos = compound.find(')', leftParenPos);

        // Parse the compound inside the parenthesis
        std::map<std::string, int> subElements;
        parseCompound(compound.substr(leftParenPos + 1, rightParenPos - leftParenPos - 1), subElements);

        // Find the first digit after the right parenthesis
        std::string::size_type digitPos = compound.find_first_of("0123456789", rightParenPos);

        // If there is no digit, the count is 1
        int count = 1;
        if (digitPos != std::string::npos)
        {
            // Extract the count
            count = std::stoi(compound.substr(digitPos));
        }

        // Add the elements to the compound
        for (auto &subElement : subElements)
        {
            elements[subElement.first] = subElement.second * count;
        }
    }
}

// Function to balance a chemical equation
bool balanceEquation(std::vector<std::map<std::string, int>> &reactants,
                     std::vector<std::map<std::string, int>> &products,
                     std::vector<int> &coefficients)
{
    // Create a map of elements and their counts
    std::map<std::string, int> elements;

    // Add the reactants to the map
    for (auto &reactant : reactants)
    {
        for (auto &element : reactant)
        {
            elements[element.first] += element.second;
        }
    }

    // Subtract the products from the map
    for (auto &product : products)
    {
        for (auto &element : product)
        {
            elements[element.first] -= element.second;
        }
    }

    // Check if the equation is balanced
    for (auto &element : elements)
    {
        if (element.second != 0)
        {
            return false;
        }
    }

    // Create a map of elements and their coefficients
    std::map<std::string, int> elementCoefficients;

    // Add the reactants to the map
    for (auto &reactant : reactants)
    {
        for (auto &element : reactant)
        {
            if (elementCoefficients[element.first] < element.second)
            {
                elementCoefficients[element.first] = element.second;
            }
        }
    }

    // Add the products to the map
    for (auto &product : products)
    {
        for (auto &element : product)
        {
            if (elementCoefficients[element.first] < element.second)
            {
                elementCoefficients[element.first] = element.second;
            }
        }
    }

    // Calculate the coefficients
    for (auto &reactant : reactants)
    {
        int coefficient = 1;
        for (auto &element : reactant)
        {
            int elementCoefficient = elementCoefficients[element.first] / element.second;
            if (coefficient < elementCoefficient)
            {
                coefficient = elementCoefficient;
            }
        }
        coefficients.push_back(coefficient);
    }

    for (auto &product : products)
    {
        int coefficient = 1;
        for (auto &element : product)
        {
            int elementCoefficient = elementCoefficients[element.first] / element.second;
            if (coefficient < elementCoefficient)
            {
                coefficient = elementCoefficient;
            }
        }
        coefficients.push_back(coefficient);
    }

    return true;
}

// Function to print a balanced chemical equation
void printBalancedEquation(const std::string &equation,
                           const std::vector<std::map<std::string, int>> &reactants,
                           const std::vector<std::map<std::string, int>> &products,
                           const std::vector<int> &coefficients)
{
    // Print the reactants
    for (std::size_t i = 0; i < reactants.size(); ++i)
    {
        // Print the coefficient
        std::cout << coefficients[i];

        // Print the compound
        for (auto &element : reactants[i])
        {
            std::cout << element.first;
            if (element.second > 1)
            {
                std::cout << element.second;
            }
        }

        // Print the plus sign
        if (i < reactants.size() - 1)
        {
            std::cout << " + ";
        }
    }

    // Print the equal sign
    std::cout << " = ";

    // Print the products
    for (std::size_t i = 0; i < products.size(); ++i)
    {
        // Print the coefficient
        std::cout << coefficients[i + reactants.size()];

        // Print the compound
        for (auto &element : products[i])
        {
            std::cout << element.first;
            if (element.second > 1)
            {
                std::cout << element.second;
            }
        }

        // Print the plus sign
        if (i < products.size() - 1)
        {
            std::cout << " + ";
        }
    }

    std::cout << std::endl;
}