#include <iostream>
using namespace std;

struct Node{
    int Value;
    Node* Next;
    Node* Prev;
};

void insertAfterNode(Node** targetNode, int value)
{
    // 1. Create new node
    Node* node = new Node();
    node->Value = value;
    node->Next = NULL;
    node->Prev = NULL;

    // 2. Check if list is empty
    if(*targetNode == NULL)
    {
        cout << "List cannot be empty." << endl;
        return;
    }

    // 3. Insert after targetNode
    Node* target = *targetNode;
    node->Next = target->Next;
    target->Next = node;
    node->Prev = target;

    // 4. Adjust the prev next node
    if(node->Next != NULL)
        node->Next->Prev = node;
}

void printForward(Node* head){
    Node* traverser = head;

    while(traverser != NULL)
    {
        cout << traverser->Value << endl;
        traverser = traverser->Next;
    }
}

void printBackward(Node* tail){
    Node* traverser = tail;

    while(traverser != NULL)
    {
        cout << traverser->Value << endl;
        traverser = traverser->Prev;
    }
}

int main() {
    Node* head =NULL;
    Node* tail =NULL;

    // Add first node
    Node* node = new Node();
    node->Value = 4;
    node->Next = NULL;
    node->Prev = NULL;
    head = node;
    tail = node;

    // Add 2nd node;
    node = new Node();
    node->Value = 5;
    node->Next = nullptr;
    node->Prev = tail;
    tail->Next = node;
    tail = node;

    // Add 3rd node;
    node = new Node();
    node->Value = 6;
    node->Next = nullptr;
    node->Prev = tail;
    tail->Next = node;
    tail = node;

    insertAfterNode(&head, 7);
    insertAfterNode(&head, 8);
    printForward(head);
    //printBackward(tail);

    return 0;
}