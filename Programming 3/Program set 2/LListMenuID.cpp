#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

//implement the linked list stuct
struct Node
{
    int key;
    Node *next;

    Node(int k) : key(k), next(nullptr) {}
};

//function prototypes for the linked list operations
void insert(Node *&head, int key);
void delete(Node *&head, int key);
void search(Node *head, int key);
void print(Node *head);
void sort(Node *&head);
void reverse(Node *&head);
void rotate(Node *&head, int k);
void iShift(Node *&head, int k);
void clear(Node *&head);

//function prototypes for the menu

int main()
{
    //declare variables
    Node *head = NULL;
    string name;
    int choice;

    return 0;
}

/*
----------------------
Linked list operations
----------------------
*/
void insert(Node *&head, int key)
{
    //create a new node
    Node *newNode = new Node(key);

    //insert the new node at the beginning of the list
    newNode->next = head;
    head = newNode;
}