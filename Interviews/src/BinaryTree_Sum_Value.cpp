#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/* Write a function, treeSum, that takes in the root of a binary tree that contains number values. 
The function should return the total sum of all values in the tree. */

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

int findNodeSum_DFS(Node* root)
{
	if(root == NULL) return 0;

	int sum = root->data;
	sum += findNodeSum_DFS(root->left);
	sum += findNodeSum_DFS(root->right);
	return sum;
}

int findNodeSum_BFS(Node* root)
{
	if(root == NULL) return 0;

	std::queue<Node*> myQueue;
	myQueue.push(root);

	int sum = 0;
	while(!myQueue.empty())
	{
		Node* current = myQueue.front();
		myQueue.pop();

		sum += current->data;

		if(current->left != NULL)
			myQueue.push(current->left);
		
		if(current->right != NULL)
			myQueue.push(current->right);
	}
	return sum;
}

int main() 
{
	Node* root = NULL;
	root = new Node(3);
	root->left = new Node(11);
	root->right = new Node(4);
	root->left->left = new Node(4);
	root->left->right = new Node(2);
	root->right->right = new Node(1);

	root->printPreOrder(root);
	cout << endl;
	root->printDFSOrder(root);
	cout << endl;
	
	root->printBFSOrder(root);

	cout << "\n" << findNodeSum_DFS(root);
	cout << "\n" << findNodeSum_BFS(root);

	cout << endl;
	
	delete root;
	return 0;
}