#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/* Write a function, zipperLists, that takes in the head of two linked lists as arguments. 
The function should zipper the two lists together into single linked list by alternating nodes. 
If one of the linked lists is longer than the other, the resulting list should terminate with the remaining nodes. 
The function should return the head of the zippered linked list.

Do this in-place, by mutating the original Nodes.

You may assume that both input lists are non-empty. */

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

Node* zipperLists_iterative(Node* A, Node* B)
{
	Node* head = NULL;
	if(A != NULL)
		head = A;
	else
		head = B;

	Node* A_curr = A;
	Node* B_curr = B;
	Node* A_next = NULL;
	Node* B_next = NULL;
	while(A_curr != NULL && B_curr != NULL)
	{
		if(A_curr != NULL && B_curr != NULL)
		{
			A_next = A_curr->next;
			A_curr->next = B_curr;
			A_curr = A_next; // A_curr is changed after this
		}

		if(B_curr != NULL && A_curr != NULL) // Affect whether this gets executed or not
		{
			B_next = B_curr->next;
			B_curr->next = A_curr;
			B_curr = B_next;
		}
	}
	return head;
}

Node* zipperLists_recursive(Node* A, Node* B)
{
	if(A == NULL && B == NULL) return NULL;
	if(A == NULL) return B;
	if(B == NULL) return A;

	Node* A_next = A->next;
	Node* B_next = B->next;

	A->next = B;
	B->next = zipperLists_recursive(A_next, B_next);
	return A;
}

int main() 
{
	Node* A = NULL;
	A = new Node('a');
	A->next = new Node('b');
	A->next->next = new Node('c');
	A->next->next->next = new Node('d');
	A->next->next->next->next = new Node('e');
	A->next->next->next->next->next = new Node('f');

	Node* B = NULL;
	B = new Node('q');
	B->next = new Node('r');
	B->next->next = new Node('s');

	A->printList_recursive(A);
	cout << endl;
	B->printList_iterative(B);
	cout << endl;

	/*Node* combined = NULL;
	combined = zipperLists_iterative(A, B);
	combined->printList_iterative(combined);
	cout << endl;*/

	Node* combined2 = NULL;
	combined2 = zipperLists_recursive(A, B);
	combined2->printList_recursive(combined2);
	cout << endl;

	//delete combined;
	delete combined2;
	return 0;
}