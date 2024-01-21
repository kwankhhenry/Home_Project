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
	Node* left;
	Node* right;

	Node(): data(0), left(NULL), right(NULL){};
	Node(int value): data(value), left(NULL), right(NULL){};

	void printPreOrder(Node* root)
	{
		if(root == NULL) return;

		cout << root->data << " ";
		printPreOrder(root->left);
		printPreOrder(root->right);
	}

	void printDFSOrder(Node* root)
	{
		if(root == NULL) return;

		stack<Node*> myStack;
		myStack.push(root);

		while(!myStack.empty())
		{
			Node* current = myStack.top();
			myStack.pop();
			cout << current->data << " ";

			// **Handle right first because they get pushed to stack first and will be executed last
			if(current->right != NULL)
				myStack.push(current->right);

			if(current->left != NULL)
				myStack.push(current->left);
		}
	}

	void printBFSOrder(Node* root)
	{
		if(root == NULL) return;

		queue<Node*> myQueue;
		myQueue.push(root);

		while(!myQueue.empty())
		{
			Node* current = myQueue.front();
			myQueue.pop();
			cout << current->data << " ";

			if(current->left != NULL)
				myQueue.push(current->left);
			
			if(current->right != NULL)
				myQueue.push(current->right);
		}
	}

	~Node() // Destructor will call its child's destructor recursively, execute child level first
	{
		delete left;
		delete right;
		//cout << "Deleting: " << this->data << endl;
	}
};

int treeMinValue_DFS(Node* root)
{
	if(!root) return INT_MAX;

	int min_children = std::min(treeMinValue_DFS(root->left), treeMinValue_DFS(root->right));

	return std::min(root->data, min_children);
}

int treeMinValue_BFS(Node* root)
{
	if(!root) return 0;

	std::queue<Node*> myQueue;
	myQueue.push(root);

	int min_value = INT_MAX;
	while(!myQueue.empty())
	{
		Node* current = myQueue.front();
		myQueue.pop();
		min_value = min(min_value, current->data);

		if(current->left)
			myQueue.push(current->left);

		if(current->right)
			myQueue.push(current->right);
	}
	return min_value;
}

int main() 
{
	Node* root = NULL;
	root = new Node(5);
	root->left = new Node(11);
	root->right = new Node(3);
	root->left->left = new Node(4);
	root->left->right = new Node(15);
	root->right->right = new Node(12);

	root->printPreOrder(root);
	cout << endl;
	root->printDFSOrder(root);
	cout << endl;
	
	root->printBFSOrder(root);

	cout << "\n" << treeMinValue_DFS(root);
	cout << "\n" << treeMinValue_BFS(root);

	cout << endl;
	
	delete root;
	return 0;
}