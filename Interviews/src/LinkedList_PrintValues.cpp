#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/* Write a function, treeMinValue, that takes in the root of a binary tree that contains number values. 
The function should return the minimum value within the tree.

You may assume that the input tree is non-empty. */

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

int treeMinValue_DFS(Node* head)
{

}

int main() 
{
	Node* head = NULL;
	head = new Node(1);
	head->next = new Node(2);
	head->next->next = new Node(3);
	head->next->next->next = new Node(4);

	head->printList_recursive(head);
	cout << endl;
	head->printList_iterative(head);
	cout << endl;

	//cout << "\n" << treeMinValue_DFS(head);

	cout << endl;
	
	delete head;
	return 0;
}