#include <iostream>
#include <string>
#include <cctype>

std::string wordify(int n);
std::string triple_to_words(int n);

int main()
{
    char runAgain;
    int number;

    do
    {
        std::cout << "Enter number [1-999999999]: ";
        std::cin >> number;

        if (number < 1 || number > 999999999)
        {
            std::cerr << "Invalid input. Please enter a number between 1 and 999999999." << std::endl;
            continue;
        }

        std::cout << wordify(number) << std::endl;

        std::cout << "Run Again (Y/N): ";
        std::cin >> runAgain;
    } while (std::toupper(runAgain) == 'Y');

    return 0;
}

std::string wordify(int n)
{
    if (n == 0)
        return "";

    std::string result;

    if (n >= 1000000)
    {
        result += triple_to_words(n / 1000000) + " MILLION";
        n %= 1000000;
        if (n > 0)
            result += ", ";
    }

    if (n >= 1000)
    {
        result += triple_to_words(n / 1000) + " THOUSAND";
        n %= 1000;
        if (n > 0)
            result += ", ";
    }

    if (n > 0)
    {
        result += triple_to_words(n);
    }

    return result;
}

std::string triple_to_words(int n)
{
    std::string ones[] = {"", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE"};
    std::string teens[] = {"TEN", "ELEVEN", "TWELVE", "THIRTEEN", "FOURTEEN", "FIFTEEN", "SIXTEEN", "SEVENTEEN", "EIGHTEEN", "NINETEEN"};
    std::string tens[] = {"", "", "TWENTY", "THIRTY", "FORTY", "FIFTY", "SIXTY", "SEVENTY", "EIGHTY", "NINETY"};

    std::string result;

    if (n >= 100)
    {
        result += ones[n / 100] + " HUNDRED";
        n %= 100;
        if (n > 0)
            result += " ";
    }

    if (n >= 20)
    {
        result += tens[n / 10];
        n %= 10;
        if (n > 0)
            result += "-";
    }
    else if (n >= 10)
    {
        result += teens[n - 10];
        n = 0;
    }

    result += ones[n];

    return result;
}
