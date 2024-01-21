#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/* Write a function, reverseList, that takes in the head of a linked list as an argument. 
The function should reverse the order of the nodes in the linked list in-place 
and return the new head of the reversed linked list. */

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

Node* reverseList_iterative(Node* head)
{
	Node* current = head;
	Node* reverse = NULL;

	while(current != NULL)
	{
		Node* next = current->next;
		current->next = reverse;
		reverse = current;
		current = next;
	}
	return reverse;
}

Node* reverseList_recursive(Node* head, Node* reverse = NULL)
{
	if(head == NULL) return reverse;

	Node* next = head->next;
	head->next = reverse;

	return reverseList_recursive(next, head);
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

	Node* reverse = NULL;
	/*reverse = reverseList_iterative(head);
	reverse->printList_iterative(reverse);
	cout << endl;*/
	reverse = reverseList_recursive(head);
	reverse->printList_recursive(reverse);
	cout << endl;
	
	delete reverse;
	return 0;
}