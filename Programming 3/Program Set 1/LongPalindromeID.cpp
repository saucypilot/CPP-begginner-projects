    #include <iostream>
    #include <string>
    #include <algorithm>

    using namespace std;

    // contains the longest palindrome
    struct Palindrome
    {
        string longest;
    };

    // checks if a given string is a palindrome or not
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

    // prompts the user for input and calls the `findLongestPalindrome` function
    void runProgram()
    {
        string input;
        char choice;

        do
        {
            cout << "Enter a string: ";
            cin >> input;

            Palindrome result = findLongestPalindrome(input);

            cout << "The longest palindrome in the given string is: " << result.longest << endl;

            cout << "Do you want to run the program again? (y/n): ";
            cin >> choice;

        } while (tolower(choice) == 'y');
    }

    int main()
    {
        runProgram();
        return 0;
    }