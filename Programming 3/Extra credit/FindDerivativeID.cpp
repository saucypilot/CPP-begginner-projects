#include <iostream>
#include <string>
#include <sstream>
#include <list>
#include <cctype>
#include <limits>

struct Term
{
    int coefficient;
    int exponent;
};

std::list<Term> parsePolynomial(const std::string &input);
std::string derivativeToString(const std::list<Term> &derivative);

int main()
{
    std::string input;
    char runAgain;
    do
    {
        std::cout << "Enter polynomial: ";
        std::getline(std::cin, input);

        std::list<Term> polynomial = parsePolynomial(input);
        std::list<Term> firstDerivative;
        std::list<Term> secondDerivative;

        for (const Term &term : polynomial)
        {
            if (term.exponent > 0)
            {
                Term firstDerivativeTerm{term.coefficient * term.exponent, term.exponent - 1};
                firstDerivative.push_back(firstDerivativeTerm);

                if (firstDerivativeTerm.exponent > 0)
                {
                    Term secondDerivativeTerm{firstDerivativeTerm.coefficient * firstDerivativeTerm.exponent, firstDerivativeTerm.exponent - 1};
                    secondDerivative.push_back(secondDerivativeTerm);
                }
            }
        }

        std::cout << "First and second derivative: " << derivativeToString(firstDerivative) << " : " << derivativeToString(secondDerivative) << std::endl;

        std::cout << "Run Again (Y/N): ";
        std::cin >> runAgain;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    } while (std::toupper(runAgain) == 'Y');

    return 0;
}

std::list<Term> parsePolynomial(const std::string &input)
{
    std::list<Term> polynomial;
    std::istringstream iss(input);
    char op;
    int coefficient, exponent;

    while (!iss.eof())
    {
        if (polynomial.empty())
        {
            op = '+';
        }
        else
        {
            iss >> op;
        }

        iss >> coefficient;

        if (op == '-')
        {
            coefficient = -coefficient;
        }
        if (std::toupper(iss.peek()) == 'X')
        {
            iss.ignore();
            if (iss.peek() == '^')
            {
                iss.ignore();
                iss >> exponent;
            }
            else
            {
                exponent = 1;
            }
        }
        else
        {
            exponent = 0;
        }
        polynomial.push_back(Term{coefficient, exponent});
    }
    return polynomial;
}

std::string derivativeToString(const std::list<Term> &derivative)
{
    if (derivative.empty())
    {
        return "0";
    }

    std::ostringstream oss;
    bool firstTerm = true;

    for (const Term &term : derivative)
    {
        if (!firstTerm)
        {
            oss << (term.coefficient > 0 ? " + " : " - ");
        }
        else
        {
            firstTerm = false;
            if (term.coefficient < 0)
            {
                oss << "-";
            }
        }

        int absCoefficient = std::abs(term.coefficient);
        if (absCoefficient != 1 || term.exponent == 0)
        {
            oss << absCoefficient;
        }
        if (term.exponent > 0)
        {
            oss << "X";
            if (term.exponent > 1)
            {
                oss << "^" << term.exponent;
            }
        }
    }

    return oss.str();
}
