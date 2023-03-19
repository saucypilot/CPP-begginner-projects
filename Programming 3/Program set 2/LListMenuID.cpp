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
void remove(Node *&head, int key);
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
    Node *newNode = new Node(key);

    newNode->next = head;
    head = newNode;
}

void remove(Node *&head, int key)
{
    Node *prev = NULL;
    Node *curr = head;

    while (curr != NULL)
    {
        if (curr->key == key)
        {
            if (prev == NULL)
            {
                head = curr->next;
            }
            else
            {
                prev->next = curr->next;
            }
            delete curr;
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void search(Node *head, int key)
{
    Node *curr = head;

    while (curr != NULL)
    {
        if (curr->key == key)
        {
            cout << "Found " << key << endl;
            return;
        }
        curr = curr->next;
    }
    cout << "Not found " << key << endl;
}

void print(Node *head)
{
    Node *curr = head;

    while (curr != NULL)
    {
        cout << curr->key << " ";
        curr = curr->next;
    }
    cout << endl;
}

void sort(Node *&head)
{
    Node *curr = head;
    Node *next = NULL;
    int temp;

    if (head == NULL)
    {
        return;
    }
    else
    {
        while (curr != NULL)
        {
            next = curr->next;

            while (next != NULL)
            {
                if (curr->key > next->key)
                {
                    temp = curr->key;
                    curr->key = next->key;
                    next->key = temp;
                }
                next = next->next;
            }
            curr = curr->next;
        }
    }
}

void reverse(Node *&head)
{
    Node *prev = NULL;
    Node *curr = head;
    Node *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
    }
    head = prev;
}

void rotate(Node *&head, int k)
{
    Node *curr = head;
    Node *prev = NULL;
    Node *next = NULL;
    int count = 0;

    while (curr != NULL && count < k)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    head = prev;
    while (curr != NULL)
    {
        curr = curr->next;
    }
    curr->next = next;
}

void iShift(Node *&head, int k)
{
    Node *curr = head;
    Node *prev = NULL;
    Node *next = NULL;
    int count = 0;

    while (curr != NULL && count < k)
    {
        next = curr->next;
        curr->next = prev;
        prev = curr;
        curr = next;
        count++;
    }
    head = prev;
    while (curr != NULL)
    {
        curr = curr->next;
    }
    curr->next = next;
}

void clear(Node *&head)
{
    Node *curr = head;
    Node *next = NULL;

    while (curr != NULL)
    {
        next = curr->next;
        delete curr;
        curr = next;
    }
    head = NULL;
}

