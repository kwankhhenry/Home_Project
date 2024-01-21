#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/* Write a function, getNodeValue, that takes in the head of a linked list and an index. 
The function should return the value of the linked list at the specified index.

If there is no node at the given index, then return null. */

class Node
{
public:
	char data;
	Node* next;

	Node(): data(0), next(NULL){};
	Node(char value): data(value), next(NULL){};

	void printList_recursive(Node* head)
	{
		if(head == NULL) return;

		cout << head->data << " ";
		printList_recursive(head->next);
	}

	void printList_iterative(Node* head)
	{
		Node* current = head;

		while(current != NULL)
		{
			cout << current->data << " ";
			current = current->next;
		}
	}

	~Node() // Destructor will call its child's destructor recursively, execute child level first
	{
		//cout << "Destructor called." << endl;
		delete next;
		//cout << "Deleting: " << this->data << endl;
	}
};

char getNodeValue_iterative(Node* head, int index)
{
	Node* current = head;
	int current_index = 0;
	while(current != NULL)
	{
		if(current_index == index) return current->data;
		current = current->next;
		current_index++;
	}
	return 0;
}

char getNodeValue_recursive(Node* head, int index)
{
	if(head == NULL) return 0;
	if(index == 0) return head->data;
	return getNodeValue_recursive(head->next, index-1);
}

int main() 
{
	Node* head = NULL;
	head = new Node('a');
	head->next = new Node('b');
	head->next->next = new Node('c');
	head->next->next->next = new Node('d');

	head->printList_recursive(head);
	cout << endl;
	head->printList_iterative(head);
	cout << endl;

	cout << getNodeValue_iterative(head, 5);
	cout << endl;
	cout << getNodeValue_recursive(head, 5);
	cout << endl;
	
	delete head;
	return 0;
}