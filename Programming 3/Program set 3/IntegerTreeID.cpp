#include <iostream>
#include <vector>
#include <iomanip> // for std::setw()
#include <queue>   // for std::queue
#include <string>  // for std::string
#include <limits>  // for std::numeric_limits

using namespace std;

struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) : val(v), left(nullptr), right(nullptr) {}
};

// Inserts a node with the given value into the BST rooted at root.
void insertNode(TreeNode *&root, int val)
{
    if (!root)
    { // If root is null, create a new node with val.
        root = new TreeNode(val);
        return;
    }
    // Otherwise, recurse down the left or right subtree based on the value of val.
    if (val <= root->val)
    {
        insertNode(root->left, val);
    }
    else
    {
        insertNode(root->right, val);
    }
}

// Generates a 2D vector of strings representing the binary search tree rooted at root.
vector<vector<string>> generateTree(TreeNode *root)
{
    if (!root)
    {
        return {};
    }

    // Get the left and right subtrees of the root node.
    vector<vector<string>> leftTree = generateTree(root->left);
    vector<vector<string>> rightTree = generateTree(root->right);

    // Get the maximum height of the left and right subtrees.
    int leftHeight = leftTree.size();
    int rightHeight = rightTree.size();
    int maxHeight = max(leftHeight, rightHeight);

    // Add padding to the left and right subtrees so that they have the same height.
    if (leftHeight < maxHeight)
    {
        int numCols = leftTree[0].size();
        for (int i = 0; i < maxHeight - leftHeight; i++)
        {
            leftTree.push_back(vector<string>(numCols, "    "));
        }
    }
    if (rightHeight < maxHeight)
    {
        int numCols = rightTree[0].size();
        for (int i = 0; i < maxHeight - rightHeight; i++)
        {
            rightTree.push_back(vector<string>(numCols, "    "));
        }
    }

    // Add the root node to the middle of the 2D vector representation of the tree.
    int numCols = leftTree[0].size() + rightTree[0].size() + 1;
    vector<string> row(numCols, "    ");
    row[leftTree[0].size()] = to_string(root->val);
    vector<vector<string>> result = {row};

    // Merge the left and right subtrees together.
    for (int i = 0; i < maxHeight; i++)
    {
        vector<string> newRow = leftTree[i];
        newRow.insert(newRow.end(), {"    "});
        newRow.insert(newRow.end(), rightTree[i].begin(), rightTree[i].end());
        result.push_back(newRow);
    }

    return result;
}

// Generates and prints the binary search tree in a vertical tree-like form.
void printTree(TreeNode *root)
{
    if (!root)
    {
        return;
    }

    // Generate the 2D vector representation of the tree.
    vector<vector<string>> tree = generateTree(root);

    // Print the tree vertically.
    for (const auto &row : tree)
    {
        for (const auto &col : row)
        {
            cout << col;
        }
        cout << endl;
    }
}


int main()
{
    char runAgain = 'Y';
    while (runAgain == 'Y' || runAgain == 'y')
    {
        TreeNode *root = nullptr;
        cout << "Enter up to 20 integers: ";
        for (int i = 0, num; i < 20 && cin >> num; ++i)
        {
            insertNode(root, num); // Insert each input integer into the BST.
        }

        printTree(root); // Generate and print the tree representation.

        cout << "Run Again (Y/N): ";
        cin >> runAgain;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }

    return 0;
}
