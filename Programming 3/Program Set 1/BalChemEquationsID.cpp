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

// Function to balance a chemical equation
string balanceEquation(string equation)
{
    // Split the equation into left and right sides
    vector<string> sides = splitEquation(equation);

    // Parse the compounds on both sides
    map<string, int> leftCompounds = parseCompounds(sides[0]);
    map<string, int> rightCompounds = parseCompounds(sides[1]);

    // Get the list of all elements in the equation
    set<string> elements;
    for (auto const &compound : leftCompounds)
    {
        for (auto const &element : parseElements(compound.first))
        {
            elements.insert(element);
        }
    }
    for (auto const &compound : rightCompounds)
    {
        for (auto const &element : parseElements(compound.first))
        {
            elements.insert(element);
        }
    }

    // Create the matrix of coefficients for each element in each compound
    int nElements = elements.size();
    int nCompounds = leftCompounds.size() + rightCompounds.size();
    Matrix matrix(nElements, nCompounds);
    int col = 0;
    for (auto const &compound : leftCompounds)
    {
        for (auto const &element : parseElements(compound.first))
        {
            matrix.setElement(getElementIndex(elements, element), col, parseCount(compound.first, element));
        }
        col++;
    }
    for (auto const &compound : rightCompounds)
    {
        for (auto const &element : parseElements(compound.first))
        {
            matrix.setElement(getElementIndex(elements, element), col, -parseCount(compound.first, element));
        }
        col++;
    }

    // Solve the system of linear equations
    vector<int> coefficients = matrix.solve();

    // Check if the system has no solution or more than one solution
    if (coefficients.empty())
    {
        return "Cannot Balance";
    }
    else if (coefficients.size() != nCompounds)
    {
        return "Multiple Solutions";
    }

    // Construct the balanced equation using the coefficients
    string balancedEquation;
    col = 0;
    for (auto const &compound : leftCompounds)
    {
        if (col > 0)
        {
            balancedEquation += " + ";
        }
        balancedEquation += toCoeffString(coefficients[col]) + compound.first;
        col++;
    }
    balancedEquation += " = ";
    for (auto const &compound : rightCompounds)
    {
        if (col > 0)
        {
            balancedEquation += " + ";
        }
        balancedEquation += toCoeffString(coefficients[col]) + compound.first;
        col++;
    }

    // Combine the two maps into a single map of all compounds
    Map<String, Integer> compounds = new HashMap<>(leftCompounds);
    rightCompounds.forEach((k, v)->compounds.merge(k, v, Integer::sum));

    // Build the matrix of coefficients
    int[][] matrix = new int[compounds.size()][compounds.size() + 1];

    // Fill in the coefficients for each compound on the left side
    int col = 0;
    for (String compound : leftCompounds.keySet())
    {
        fillInCoefficients(matrix, col, parseCompound(compound), compounds);
        col++;
    }

    // Fill in the coefficients for each compound on the right side
    for (String compound : rightCompounds.keySet())
    {
        fillInCoefficients(matrix, col, parseCompound(compound), compounds);
        col++;
    }

    // Solve the matrix to get the coefficients
    int[] coefficients = solveMatrix(matrix);

    // Check if the equation could be balanced
    if (coefficients == null)
    {
        return "Cannot Balance";
    }

    // Build the balanced equation
    StringBuilder balancedEquation = new StringBuilder();
    col = 0;
    for (String compound : leftCompounds.keySet())
    {
        int coefficient = coefficients[col];
        if (coefficient > 1)
        {
            balancedEquation.append(coefficient);
        }
        balancedEquation.append(compound);
        balancedEquation.append(" + ");
        col++;
    }
    for (String compound : rightCompounds.keySet())
    {
        int coefficient = coefficients[col];
        if (coefficient > 1)
        {
            balancedEquation.append(coefficient);
        }
        balancedEquation.append(compound);
        balancedEquation.append(" + ");
        col++;
    }
    balancedEquation.delete(balancedEquation.length() - 3, balancedEquation.length());

    return balancedEquation.toString();
}

/**
 * Parses a compound into a map of elements and their counts.
 *
 * @param compound the compound to parse
 * @return a map of elements and their counts
 */
private
static Map<String, Integer> parseCompound(String compound)
{
    Map<String, Integer> elements = new HashMap<>();
    Matcher matcher = ELEMENT_PATTERN.matcher(compound);
    while (matcher.find())
    {
        String element = matcher.group(1);
        String count = matcher.group(2);
        int coefficient = count != null ? Integer.parseInt(count) : 1;
        elements.merge(element, coefficient, Integer::sum);
    }
    return elements;
}

/**
 * Fills in the coefficients for a compound in the matrix.
 *
 * @param matrix    the matrix to fill in
 * @param col       the column to fill in
 * @param compound  the compound to fill in
 * @param compounds the map of all compounds and their elements
 */
private
static void fillInCoefficients(int[][] matrix, int col, Map<String, Integer> compound,
                               Map<String, Integer> compounds)
{
    for (Map.Entry<String, Integer> entry : compound.entrySet())
    {
        String element = entry.getKey();
        int row = getRowForElement(element, compounds);
        int count = entry.getValue();
        matrix[row][col] = count;
    }
    matrix[matrix.length - 1][col] = -1;
}
/**
     * Solves the matrix to get the coefficients for each compound.
     *
     * @param matrix the matrix to solve
     * @return an array of coefficients
     * @throws IllegalArgumentException if the matrix cannot be solved
     */
