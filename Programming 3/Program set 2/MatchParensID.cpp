#include <iostream>
#include <stack>
#include <string>
#include <vector>

using namespace std;

void printOutput(const string &input, const vector<vector<int>> &connections)
{
    // Print the input string
    cout << input << endl;

    // Iterate through the connections vector
    for (const auto &row : connections)
    {
        // Iterate through the characters in the input string
        for (int i = 0; i < input.size(); i++)
        {
            // Check if the current character is connected to the previous
            // character in the input string
            if (row[i])
            {
                // Print the appropriate character
                cout << (row[i] == 1 ? '|' : '_');
            }
            else
            {
                // Print a space if the current character is not connected
                // to the previous character
                cout << ' ';
            }
        }
        // Print a new line
        cout << endl;
    }
}

bool findMatchingParentheses(const string &input, vector<vector<int>> &connections)
{
    stack<pair<int, int>> s;

    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '(')
        {
            // push the current index and the current
            // number of rows into the stack
            s.push(make_pair(i, connections.size()));
            // add a new row to the connections matrix
            connections.push_back(vector<int>(input.size(), 0));
        }
        else if (input[i] == ')')
        {
            // if the stack is empty, then there is a
            // missing open parenthesis
            if (s.empty())
            {
                return false;
            }
            // get the top element
            auto top = s.top();
            // pop the top element
            s.pop();
            // set the top row to have a vertical line
            // at the current index
            connections[top.second][top.first] = 1;
            // set the top row to have a horizontal line
            // from the open parenthesis to the closing
            // parenthesis
            for (int j = top.first + 1; j < i; j++)
            {
                connections[top.second][j] = 2;
            }
            // set the top row to have a vertical line
            // at the current index
            connections[top.second][i] = 1;
        }
    }
    // if the stack is not empty, then there is a
    // missing closing parenthesis
    return s.empty();
}

int main()
{
    char choice;
    do
    {
        string input;
        cout << "Enter a string up to 30 characters long: ";
        getline(cin, input); //Get the input from the user

        vector<vector<int>> connections;
        if (findMatchingParentheses(input, connections)) //Check if the parentheses match
        {
            printOutput(input, connections);
        }
        else
        {
            cout << "Parentheses do not match!" << endl;
        }

        cout << "Run again (Y/N): ";
        cin >> choice;
        cin.ignore();
    } while (tolower(choice) == 'y');

    return 0;
}