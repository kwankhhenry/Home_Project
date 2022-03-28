#include <iostream>
using namespace std;

struct Node{
    int Value;
    Node* Next;
};

void printNode(Node* head)
{
    //cout << "Picking up: " << head << endl;
    while(head != NULL)
    {
        cout << head->Value << endl;
        head = head->Next;
    }
}

void insertFrontNode(Node** head, int value)
{
    //cout << "Picking up: " << head << endl;
    // 1.) Create a new node
    Node* newNode = new Node();
    newNode->Value = value;
    //cout << "NewNode points to:" << newNode << endl;

    // 2.) Assign new node to head
    newNode->Next = *head;
    *head = newNode;
    //cout << "Assign new head points to: " << *head << endl;
}

void insertEndNode(Node** head, int value)
{
    // 1.) Create new Node
    Node* newNode = new Node();
    newNode->Value = value;
    newNode->Next = NULL;
    // 2.) Check if head is empty
    if(*head == NULL)
    {
        *head = newNode;
        return;
    }
    // 3.) Find the end node
    Node* curr = *head;
    while(curr->Next != NULL)
    {
        curr = curr->Next;
    }

    // 4.) Assign end node to new node
    curr->Next = newNode;
}

void insertAfterNode(Node** previous, int value)
{
    // 1.) Create a new node2.) Assign previous next to newNode next
    Node* newNode = new Node;
    newNode->Value = value;

    // 1.) Check if previous node is NULL
    if(*previous == NULL)
    {
        *previous = newNode;
        return;
    }

    // 3.) Assign newNode next to previous
    Node* curr = *previous;
    newNode->Next = curr->Next;
    curr->Next = newNode;
}

int main() {
    Node* head = new Node();
    Node* second = new Node();
    Node* third = new Node();

    head->Value = 1;
    head->Next = second;
    second->Value = 2;
    second->Next = third;
    third->Value = 3;
    third->Next = NULL;
    //insertFrontNode(&head, 4);
    //insertEndNode(&head, 5);
    insertAfterNode(&head, 6);
    printNode(head);
    
    return 0;
}