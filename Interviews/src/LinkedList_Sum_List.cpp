#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/* Write a function, sumList, that takes in the head of a linked list containing numbers as an argument. 
The function should return the total sum of all values in the linked list. */

class Node
{
public:
	int data;
	Node* next;

	Node(): data(0), next(NULL){};
	Node(int value): data(value), next(NULL){};

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

int sumList(Node* head)
{
	Node* current = head;
	int sum = 0;
	while(current != NULL)
	{
		sum += current->data;
		current = current->next;
	}
	return sum;
}

int main() 
{
	Node* head = NULL;
	head = new Node(2);
	head->next = new Node(8);
	head->next->next = new Node(3);
	head->next->next->next = new Node(7);

	head->printList_recursive(head);
	cout << endl;
	head->printList_iterative(head);
	cout << endl;

	cout << sumList(head);
	cout << endl;
	
	delete head;
	return 0;
}