#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//implement a linked list
struct Node
{
    string data;
    Node *next;
};

//function prototypes
void addNode(Node *&, string);
void deleteNode(Node *&, string);
void displayList(Node *);
void searchList(Node *, string);
void sortList(Node *);

int main()
{
    //declare variables
    Node *head = NULL;
    string name;
    int choice;

    return 0;
}

