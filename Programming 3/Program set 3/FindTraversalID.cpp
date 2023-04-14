#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Define a struct for a binary tree node
struct Node
{
    char data;
    Node *left;
    Node *right;
};

// Function to create a new node with the given data and NULL left and right pointers
Node *newNode(char data)
{
    Node *node = new Node();
    node->data = data;
    node->left = node->right = nullptr;
    return node;
}

// Function to search for a character in a string within the given range
int search(string arr, int start, int end, char value)
{
    for (int i = start; i <= end; i++)
    {
        if (arr[i] == value)
        {
            return i;
        }
    }
    return -1;
}

// Function to build a binary tree from the inorder and preorder traversals
Node *buildTree(string in, string pre, int inStart, int inEnd)
{
    static int preIndex = 0;

    // Base case: if the inorder start index is greater than the end index, return NULL
    if (inStart > inEnd)
    {
        return nullptr;
    }

    // Create a new node with the data at the current preIndex position
    char curr = pre[preIndex++];
    Node *node = newNode(curr);

    // Base case: if the inorder start and end indexes are equal, return the node
    if (inStart == inEnd)
    {
        return node;
    }

    // Find the index of the current node's data in the inorder traversal
    int inIndex = search(in, inStart, inEnd, curr);

    // Recursively build the left and right subtrees of the current node
    node->left = buildTree(in, pre, inStart, inIndex - 1);
    node->right = buildTree(in, pre, inIndex + 1, inEnd);

    // Return the current node
    return node;
}

// Function to print the postorder traversal of a binary tree
void printPostorder(Node *node)
{
    if (node == nullptr)
    {
        return;
    }

    printPostorder(node->left);
    printPostorder(node->right);
    cout << node->data;
}

// Main function
int main()
{
    string in, pre;
    char runAgain;

    do
    {
        // Read in the inorder and preorder traversals from the user
        cout << "Enter inorder traversal: ";
        cin >> in;
        cout << "Enter preorder traversal: ";
        cin >> pre;

        // Check that the input traversals have the same length
        if (in.size() != pre.size())
        {
            cout << "Invalid Tree" << endl;
        }
        else
        {
            // Build the binary tree from the input traversals and print the postorder traversal
            Node *root = buildTree(in, pre, 0, in.size() - 1);
            cout << "Postorder traversal: ";
            printPostorder(root);
            cout << endl;
        }

        // Prompt the user to run the program again
        cout << "Run again (Y/N): ";
        cin >> runAgain;
        runAgain = toupper(runAgain);
    } while (runAgain == 'Y');

    return 0;
}