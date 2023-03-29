#include <iostream>
#include <string>
#include <algorithm>
#include <limits>
#include <iomanip>

using namespace std;

// implement the linked list stuct
struct Node
{
    int key;
    Node *next;

    Node(int k) : key(k), next(nullptr) {}
};

// function prototypes for the linked list operations
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

int main()
{
    // declare the head of the linked list
    Node *head = nullptr;

    int choice; // declare the menu choice variable
    int key;
    int size;
    int *arr;
    bool inserted, deleted, found;

    // display the menu
    std::cout << "Welcome to the Linked List Operations Program!" << std::endl;
    std::cout << "Please enter the number corresponding to your desired operation:" << std::endl;

    while (true)
    {
        std::cout << "1. Insert a key" << std::endl;
        std::cout << "2. Delete a key" << std::endl;
        std::cout << "3. Search for a key" << std::endl;
        std::cout << "4. Print the list" << std::endl;
        std::cout << "5. List size" << std::endl;
        std::cout << "6. Sort the list" << std::endl;
        std::cout << "7. Reverse the lis" << std::endl;
        std::cout << "8. Rotate the list" << std::endl;
        std::cout << "9. Shift the list" << std::endl;
        std::cout << "10. Clear the list" << std::endl;
        std::cout << "11. Exit" << std::endl << std::endl;

        std::cout << "Enter your choice: ";
        std::cin >> choice;
        std::cout << std::endl;

        switch (choice)
        {
        case 1:
            std::cout << "Enter the key to insert: ";
            std::cin >> key;
            inserted = insertKey(head, key);
            if (inserted)
            {
                std::cout << "Key " << key << " inserted successfully" << std::endl;
            }
            else
            {
                std::cout << "Key " << key << " already exists" << std::endl;
            }
            break;
        case 2:
            std::cout << "Enter the key to delete: ";
            std::cin >> key;
            deleted = deleteKey(head, key);
            if (deleted)
            {
                std::cout << "Key " << key << " deleted successfully" << std::endl;
            }
            else
            {
                std::cout << "Key " << key << " not found" << std::endl;
            }
            break;
        case 3:
            std::cout << "Enter the key to search: ";
            std::cin >> key;
            found = searchKey(head, key);
            if (found)
            {
                std::cout << "Key " << key << " found" << std::endl;
            }
            else
            {
                std::cout << "Key " << key << " not found" << std::endl;
            }
            break;
        case 4:
            std::cout << "Printing the list:" << std::endl;
            printList(head);
            break;
        case 5:
            size = listSize(head);
            std::cout << "List size: " << size << std::endl;
            break;
        case 6:
            std::cout << "Sorting the list..." << std::endl;
            sortList(head);
            std::cout << "List sorted successfully" << std::endl;
            break;
        case 7:
            std::cout << "Reversing the list..." << std::endl;
            reverseList(head);
            std::cout << "List reversed successfully" << std::endl;
            break;
        case 8:
            std::cout << "Rotating the list..." << std::endl;
            rotateList(head);
            std::cout << "List rotated successfully" << std::endl;
            break;
        case 9:
            std::cout << "Shifting the list..." << std::endl;
            shiftList(head);
            std::cout << "List shifted successfully" << std::endl;
            break;
        case 10:
            std::cout << "Clearing the list..." << std::endl;
            clearList(head);
            std::cout << "List cleared successfully" << std::endl;
            break;
        case 11:
            std::cout << "Exiting program..." << std::endl;
            return 0;
        default:
            std::cout << "Invalid choice. Please enter a number from 1 to 11." << std::endl;
        }
    }
    return 0;
}

/*
----------------------
Linked list operations
----------------------
*/
bool insertKey(Node *&head, int key)
{
    // create a new node
    Node *newNode = new Node(key);

    // check if the list is empty
    if (head == NULL)
    {
        head = newNode;
        return true;
    }

    // check if the key is already in the list
    if (searchKey(head, key))
    {
        return false;
    }

    // insert the key at the beginning of the list
    newNode->next = head;
    head = newNode;
    return true;
}

bool deleteKey(Node *&head, int key)
{
    // check if the list is empty
    if (head == NULL)
    {
        return false;
    }

    // check if the key is in the list
    if (!searchKey(head, key))
    {
        return false;
    }

    // delete the key from the beginning of the list
    if (head->key == key)
    {
        Node *temp = head;
        head = head->next;
        delete temp;
        return true;
    }

    // delete the key from the middle of the list
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
    // check if the list is empty
    if (head == NULL)
    {
        return false;
    }

    // search for the key in the list
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
    Node *current = head;
    cout << "Printing the list:" << endl;
    while (current != NULL)
    {
        cout << "----------     ";
        current = current->next;
    }
    cout << endl;
    current = head;
    while (current != NULL)
    {
        cout << "| " << setw(2) << current->key << " |";
        current = current->next;
        if (current != NULL)
        {
            cout << "--->";
        }
    }
    cout << "  " << endl;
    current = head;
    while (current != NULL)
    {
        cout << "----------     ";
        current = current->next;
    }
    cout << endl;
}

int listSize(Node *head)
{
    // check if the list is empty
    if (head == NULL)
    {
        return 0;
    }

    // count the number of nodes in the list
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
    // check if the list is empty
    if (head == NULL)
    {
        return;
    }

    // sort the list
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
    // check if the list is empty
    if (head == NULL)
    {
        return;
    }

    // reverse the list
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
    // check if the list is empty
    if (head == NULL)
    {
        return;
    }

    // rotate the list
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
    // check if the list is empty
    if (head == NULL)
    {
        return;
    }

    // shift the list
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
    // check if the list is empty
    if (head == NULL)
    {
        return;
    }

    // clear the list
    Node *current = head;
    while (current != NULL)
    {
        Node *temp = current;
        current = current->next;
        delete temp;
    }
    head = NULL;
}