#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>
#include <sstream>

using namespace std;

// Define the structure for the binary tree node
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int x) : val(x), left(NULL), right(NULL) {}
};

// Function to insert a node in the binary search tree
TreeNode *insert(TreeNode *root, int value)
{
    if (root == NULL)
    {
        root = new TreeNode(value);
    }
    else if (value <= root->val)
    {
        root->left = insert(root->left, value);
    }
    else
    {
        root->right = insert(root->right, value);
    }
    return root;
}

// Function to print the binary tree in a vector of vector of strings
vector<vector<string>> printTree(TreeNode *root)
{
    // Calculate the height of the tree
    int h = height(root);
    // Calculate the width of the tree
    int width = pow(2, h) - 1;
    // Create a vector of vector of strings to store the tree
    vector<vector<string>> ans(h, vector<string>(width, "    "));

    // Fill the tree in the vector of vector of strings
    fillTree(ans, root, 0, 0, width);
    return ans;
}

// Function to recursively fill the vector of vector of strings with the binary tree
void fillTree(vector<vector<string>> &ans, TreeNode *node, int h, int l, int r)
{
    if (!node)
        return;
    int mid = (l + r) / 2;
    ans[h][mid] = to_string(node->val);
    fillTree(ans, node->left, h + 1, l, mid - 1);
    fillTree(ans, node->right, h + 1, mid + 1, r);
}

// Function to calculate the height of the binary tree
int height(TreeNode *root)
{
    if (!root)
        return 0;
    return 1 + max(height(root->left), height(root->right));
}

int main()
{
    char choice;
    do
    {
        // Initialize the root of the binary search tree
        TreeNode *root = NULL;
        int value;
        // Prompt the user to enter integers
        cout << "Enter integers: ";
        string line;
        // Get the input from the user
        getline(cin, line);
        istringstream iss(line);
        // Insert the integers in the binary search tree
        while (iss >> value)
        {
            root = insert(root, value);
        }

        // Print the binary tree
        vector<vector<string>> tree = printTree(root);
        for (int i = 0; i < tree.size(); ++i)
        {
            for (int j = 0; j < tree[i].size(); ++j)
            {
                if (i % 2 == 0)
                {
                    // Print the even levels with a larger width
                    cout << setw(4) << tree[i][j];
                }
                else
                {
                    // Print the odd levels with a smaller width
                    if (tree[i][j] != "    ")
                    {
                        cout << setw(2) << tree[i][j];
                    }
                    else
                    {
                        cout << tree[i][j];
                    }
                }
            }
            cout << endl;
        }

        // Ask the user if they want to run the program again
        cout << "Run Again (Y/N): ";
        cin >> choice;
        cin.ignore();
        cout << endl;
    } while (toupper(choice) == 'Y');

    return 0;
}