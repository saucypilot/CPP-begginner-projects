#include <iostream>
#include <string>
#include <algorithm>
#include <limits>

using namespace std;

//implement the linked list stuct
struct Node
{
    int key;
    Node *next;

    Node(int k) : key(k), next(nullptr) {}
};

//function prototypes for the linked list operations
bool insertKey(Node *&head, int key);
bool deleteKey(Node *&head, int key);
bool searchKey(Node *head, int key);
void printList(Node *head);
int listSize(Node *head);
void sortList(Node *&head);
void reverseList(Node *&head);
void rotateList(Node *&head);
void shiftList(Node *&head);
void clearList(Node *&head);

//function prototypes for the menu
void menu();
void menuInsert(Node *&head);
void menuDelete(Node *&head);
void menuSearch(Node *head);
void menuPrint(Node *head);
void menuSize(Node *head);
void menuSort(Node *&head);
void menuReverse(Node *&head);
void menuRotate(Node *&head);
void menuShift(Node *&head);
void menuClear(Node *&head);

int main()
{
    Node *head = nullptr;
    int choice;

    while (true)
    {
        menu();
        cin >> choice;

        // Ensure valid input
        while (cin.fail() || choice < 1 || choice > 11)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice. Please try again: ";
            cin >> choice;
        }

        if (choice == 11)
        {
            break; // Quit the program
        }

        switch (choice)
        {
        case 1:
            menuInsert(head);
            break;
        case 2:
            menuDelete(head);
            break;
        case 3:
            menuSearch(head);
            break;
        case 4:
            menuPrint(head);
            break;
        case 5:
            menuSize(head);
            break;
        case 6:
            menuSort(head);
            break;
        case 7:
            menuReverse(head);
            break;
        case 8:
            menuRotate(head);
            break;
        case 9:
            menuShift(head);
            break;
        case 10:
            menuClear(head);
            break;
        }

        cout << endl; // Add a newline for better readability
    }

    // Clear the list before exiting
    clearList(head);

    return 0;
}

/*
----------------------
Linked list operations
----------------------
*/
bool insertKey(Node *&head, int key)
{
    //create a new node
    Node *newNode = new Node(key);

    //check if the list is empty
    if (head == NULL)
    {
        head = newNode;
        return true;
    }

    //check if the key is already in the list
    if (searchKey(head, key))
    {
        return false;
    }

    //insert the key at the beginning of the list
    newNode->next = head;
    head = newNode;
    return true;
}

bool deleteKey(Node *&head, int key)
{
    //check if the list is empty
    if (head == NULL)
    {
        return false;
    }

    //check if the key is in the list
    if (!searchKey(head, key))
    {
        return false;
    }

    //delete the key from the beginning of the list
    if (head->key == key)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    //delete the key from the middle of the list
    Node *current = head;
    while (current->next->key != key)
    {
        current = current->next;
    }
    Node *temp = current->next;
    current->next = current->next->next;
    delete temp;
    return true;
}

bool searchKey(Node *head, int key)
{
    //check if the list is empty
    if (head == NULL)
    {
        return false;
    }

    //search for the key in the list
    Node *current = head;
    while (current != NULL)
    {
        if (current->key == key)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void printList(Node *head)
{
    // Check if the list is empty
    if (head == nullptr)
    {
        cout << "Nothing to print" << endl;
        return;
    }

    // Print the keys and pointers in the list
    Node *current = head;
    while (current != nullptr)
    {
        cout << "-----------    ";
        current = current->next;
    }
    cout << endl;

    current = head;
    while (current != nullptr)
    {
        cout << "| " << current->key << " |";
        if (current->next != nullptr)
            cout << "---->";
        else
            cout << "  |";
        current = current->next;
    }
    cout << endl;

    current = head;
    while (current != nullptr)
    {
        cout << "-----------    ";
        current = current->next;
    }
    cout << endl;
}

int listSize(Node *head)
{
    //check if the list is empty
    if (head == NULL)
    {
        return 0;
    }

    //count the number of nodes in the list
    int count = 0;
    Node *current = head;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    return count;
}

void sortList(Node *&head)
{
    //check if the list is empty
    if (head == NULL)
    {
        return;
    }

    //sort the list
    int size = listSize(head);
    int *arr = new int[size];
    Node *current = head;
    for (int i = 0; i < size; i++)
    {
        arr[i] = current->key;
        current = current->next;
    }
    sort(arr, arr + size);
    clearList(head);
    for (int i = 0; i < size; i++)
    {
        insertKey(head, arr[i]);
    }
    delete[] arr;
}

void reverseList(Node *&head)
{
    //check if the list is empty
    if (head == NULL)
    {
        return;
    }

    //reverse the list
    Node *current = head;
    Node *prev = NULL;
    Node *next = NULL;
    while (current != NULL)
    {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    head = prev;
}

void rotateList(Node *&head)
{
    //check if the list is empty
    if (head == NULL)
    {
        return;
    }

    //rotate the list
    Node *current = head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = head;
    head = head->next;
    current->next->next = NULL;
}

void shiftList(Node *&head)
{
    //check if the list is empty
    if (head == NULL)
    {
        return;
    }

    //shift the list
    Node *current = head;
    while (current->next->next != NULL)
    {
        current = current->next;
    }
    current->next->next = head;
    head = current->next;
    current->next = NULL;
}

void clearList(Node *&head)
{
    //check if the list is empty
    if (head == NULL)
    {
        return;
    }

    //clear the list
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
}

/*
----------------------
Menu functions
----------------------
*/
void menuInsert(Node *&head)
{
    int key;
    cout << "Enter the key to insert: ";
    cin >> key;
    if (insertKey(head, key))
    {
        cout << "Key inserted successfully" << endl;
    }
    else
    {
        cout << "Key already exists" << endl;
    }
}

void menuDelete(Node *&head)
{
    int key;
    cout << "Enter the key to delete: ";
    cin >> key;
    if (deleteKey(head, key))
    {
        cout << "Key deleted successfully" << endl;
    }
    else
    {
        cout << "Key not found" << endl;
    }
}

void menuSearch(Node *head)
{
    int key;
    cout << "Enter the key to search: ";
    cin >> key;
    if (searchKey(head, key))
    {
        cout << "Key found" << endl;
    }
    else
    {
        cout << "Key not found" << endl;
    }
}

void menuPrint(Node *head)
{
    printList(head);
}

void menuSize(Node *head)
{
    cout << "The size of the list is " << listSize(head) << endl;
}

void menuSort(Node *&head)
{
    sortList(head);
    cout << "The list is sorted" << endl;
}

void menuReverse(Node *&head)
{
    reverseList(head);
    cout << "The list is reversed" << endl;
}

void menuRotate(Node *&head)
{
    rotateList(head);
    cout << "The list is rotated" << endl;
}

void menuShift(Node *&head)
{
    shiftList(head);
    cout << "The list is shifted" << endl;
}

void menuClear(Node *&head)
{
    clearList(head);
    cout << "The list is cleared" << endl;
}

void menuExit()
{
    cout << "Goodbye" << endl;
}