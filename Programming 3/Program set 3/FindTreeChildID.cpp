#include <iostream>
#include <vector>
#include <queue>
#include <sstream>

class TreeNode
{
public:
    int id;
    std::vector<TreeNode *> children;

    TreeNode(int _id) : id(_id) {}
};

class Tree
{
public:
    TreeNode *root;

    Tree(int rootId)
    {
        root = new TreeNode(rootId);
    }

    void addChildren(int node, const std::vector<int> &children)
    {
        TreeNode *parentNode = findNode(node);
        if (parentNode)
        {
            for (int child : children)
            {
                parentNode->children.push_back(new TreeNode(child));
            }
        }
    }

    TreeNode *findNode(int id)
    {
        std::queue<TreeNode *> q;
        q.push(root);

        while (!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();

            if (current->id == id)
            {
                return current;
            }

            for (TreeNode *child : current->children)
            {
                q.push(child);
            }
        }

        return nullptr;
    }

    std::vector<int> getChildren(int id)
    {
        TreeNode *node = findNode(id);
        std::vector<int> result;

        if (node)
        {
            for (TreeNode *child : node->children)
            {
                result.push_back(child->id);
            }
        }

        return result;
    }
};

int main()
{
    std::string line;
    char runAgain;

    do
    {
        std::cout << "Enter number of children at each tree level: ";
        std::getline(std::cin, line);
        std::stringstream ss(line);

        std::vector<int> levels;
        int val;

        while (ss >> val)
        {
            levels.push_back(val);
        }

        int nodeId;
        std::cout << "\nEnter node to find: ";
        std::cin >> nodeId;

        int currId = 0;
        Tree tree(currId++);

        for (int children : levels)
        {
            std::queue<TreeNode *> q;
            q.push(tree.root);

            while (!q.empty())
            {
                TreeNode *current = q.front();
                q.pop();

                if (current->children.empty())
                {
                    for (int i = 0; i < children; i++)
                    {
                        current->children.push_back(new TreeNode(currId++));
                    }
                }
                else
                {
                    for (TreeNode *child : current->children)
                    {
                        q.push(child);
                    }
                }
            }
        }

        std::vector<int> children = tree.getChildren(nodeId);

        if (children.empty())
        {
            if (tree.findNode(nodeId))
            {
                std::cout << "\nChildren: NO CHILDREN" << std::endl;
            }
            else
            {
                std::cout << "\nChildren: NOT IN TREE" << std::endl;
            }
        }
        else
        {
            std::cout << "\nChildren:";
            for (int child : children)
            {
                std::cout << " " << child;
            }
            std::cout << std::endl;
        }

        std::cout << "\nRun again (Y/N): ";
        std::cin >> runAgain;
        std::cin.ignore();
    } while (std::tolower(runAgain) == 'y');

    return 0;
}
