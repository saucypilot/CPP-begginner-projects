#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <memory>
#include <string>
#include <limits>
#include <sstream>

// Node class for binary search tree
class Node
{
public:
    int data;
    std::shared_ptr<Node> left, right;

    // Constructor to initialize data and pointers
    Node(int data) : data(data), left(nullptr), right(nullptr) {}
};

// Binary search tree class
class BST
{
public:
    std::shared_ptr<Node> root;

    // Insert a new node into the binary search tree
    void insert(int data)
    {
        if (!root)
        {
            root = std::make_shared<Node>(data);
            return;
        }

        std::shared_ptr<Node> curr = root, prev;
        while (curr)
        {
            prev = curr;
            if (data <= curr->data)
            {
                curr = curr->left;
            }
            else
            {
                curr = curr->right;
            }
        }

        if (data <= prev->data)
        {
            prev->left = std::make_shared<Node>(data);
        }
        else
        {
            prev->right = std::make_shared<Node>(data);
        }
    }
};

// Get height of the binary search tree
int getHeight(std::shared_ptr<Node> root)
{
    if (!root)
    {
        return 0;
    }
    return 1 + std::max(getHeight(root->left), getHeight(root->right));
}

// Print a level of the binary search tree
void printLevel(std::shared_ptr<Node> root, int level, int indent)
{
    if (!root)
    {
        return;
    }

    if (level == 1)
    {
        std::cout << std::setw(indent) << root->data;
    }
    else
    {
        printLevel(root->left, level - 1, indent / 2);
        printLevel(root->right, level - 1, indent / 2);
    }
    std::cout << std::setw(indent) << ' ';
}

// Print the binary search tree
void printTree(std::shared_ptr<Node> root, int height)
{
    for (int i = 1; i <= height; ++i)
    {
        printLevel(root, i, 1 << (height - i));
        std::cout << '\n';
        if (i % 2 == 0)
        {
            for (int j = 1; j <= (1 << (height - i)) / 2; ++j)
            {
                std::cout << " / \\";
            }
            std::cout << '\n';
        }
    }
}

// Main function
int main()
{
    char runAgain;
    do
    {
        BST tree;               // Create a binary search tree
        std::vector<int> input; // Create a vector to store user input
        int num;
        std::string line;

        std::cout << "Enter up to 20 integers: ";
        std::getline(std::cin, line); // Get a line of user input
        std::istringstream iss(line);

        int count = 0;
        while (count < 20 && iss >> num) // Read integers from the user input
        {
            input.push_back(num);
            tree.insert(num); // Insert each integer into the binary search tree
            count++;
        }

        int height = getHeight(tree.root); // Get the height of the binary search tree
        printTree(tree.root, height);      // Print the binary search tree
        std::cout << "\nRun Again (Y/N): "; // Ask user if they want to run the program again
        std::cin >> runAgain;              // Get user input
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear the input buffer
    } while (std::tolower(runAgain) == 'y'); // Run the program again if the user enters 'y'
}