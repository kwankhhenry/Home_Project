#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/* Write a function, linkedListFind, that takes in the head of a linked list and a target value. 
The function should return a boolean indicating whether or not the linked list contains the target. */

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

bool linkedListFind_iterative(Node* head, int target)
{
	Node* current = head;

	while(current != NULL)
	{
		if(current->data == target) return true;
		current = current->next;
	}
	return false;
}

bool linkedListFind_recursive(Node* head, int target)
{
	if(head == NULL) return false;
	if(head->data == target) return true;

	if(linkedListFind_recursive(head->next, target)) return true;
	return false;
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

	cout << std::boolalpha << linkedListFind_iterative(head, 'c');
	cout << endl;
	cout << std::boolalpha << linkedListFind_recursive(head, 'c');
	cout << endl;
	
	delete head;
	return 0;
}