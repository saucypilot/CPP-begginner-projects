#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

struct Palindrome
{
    string longest;
};

bool isPalindrome(const string &str)
{
    return str == string(str.rbegin(), str.rend());
}

Palindrome findLongestPalindrome(const string &str)
{
    Palindrome palindrome;
    palindrome.longest = "";

    int n = str.length();

    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            string substring = str.substr(i, j - i + 1);
            if (isPalindrome(substring) && substring.length() > palindrome.longest.length())
            {
                palindrome.longest = substring;
            }
        }
    }

    return palindrome;
}

int main()
{
    char choice;
    do
    {
        string input;
        cout << "Enter a string: ";
        cin >> input;

        Palindrome result = findLongestPalindrome(input);

        cout << "Longest palindrome: " << result.longest << endl;

        cout << "Run again (Y/N): ";
        cin >> choice;
    } while (tolower(choice) == 'y');

    return 0;
}