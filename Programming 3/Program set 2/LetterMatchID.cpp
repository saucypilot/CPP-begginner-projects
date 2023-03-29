#include <iostream>
#include <stack>
#include <string>

bool is_properly_ordered(const std::string &input)
{
    // Create a stack for the characters.
    std::stack<char> s;

    // Iterate through each character in the string.
    for (const char &c : input)
    {
        // If the stack is empty or the character is not a matching pair
        // with the top of the stack, push the character onto the stack.
        if (s.empty() || abs(c - s.top()) != 25)
        {
            s.push(c);
        }
        // Otherwise, pop the top of the stack.
        else
        {
            s.pop();
        }
    }

    // If the stack is empty, the string is properly ordered.
    return s.empty();
}

int main()
{
    std::string input;
    char run_again;

    do
    {
        std::cout << "Enter the string: ";
        std::cin >> input;

        if (is_properly_ordered(input))
        {
            std::cout << "YES" << std::endl;
        }
        else
        {
            std::cout << "NO" << std::endl;
        }

        std::cout << "Run again (Y/N): ";
        std::cin >> run_again;
    } while (run_again == 'Y' || run_again == 'y');

    return 0;
}