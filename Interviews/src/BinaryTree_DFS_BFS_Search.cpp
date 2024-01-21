#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/* Write a function, depthFirstValues, that takes in the root of a binary tree. 
The function should return an array containing all values of the tree in depth-first order. 

Write a function, breadthFirstValues, that takes in the root of a binary tree. 
The function should return an array containing all values of the tree in breadth-first order.*/

class Node
{
public:
	char data;
	Node* left;
	Node* right;

	Node(): data('0'), left(NULL), right(NULL){};
	Node(char value): data(value), left(NULL), right(NULL){};

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

bool findNode_DFS(Node* root, char target)
{
	if(root == NULL) return false;

	Node* current = root;
	if(current->data == target) return true;

	if(findNode_DFS(root->left, target) || findNode_DFS(root->right, target)) return true;
	return false;
}

bool findNode_BFS(Node* root, char target)
{
	std::queue<Node*> myQueue;
	myQueue.push(root);

	if(root == NULL) return false;

	while(!myQueue.empty())
	{
		Node* current = myQueue.front();
		myQueue.pop();

		if(current->data == target) return true;

		if(current->left != NULL)
			myQueue.push(current->left);
		
		if(current->right != NULL)
			myQueue.push(current->right);
	}
	return false;
}

int main() 
{
	Node* root = NULL;
	root = new Node('a');
	root->left = new Node('b');
	root->right = new Node('c');
	root->left->left = new Node('d');
	root->left->right = new Node('e');
	root->right->right = new Node('f');

	root->printPreOrder(root);
	cout << endl;
	root->printDFSOrder(root);
	cout << endl;
	
	root->printBFSOrder(root);

	cout << "\n" << std::boolalpha << findNode_DFS(root, 'e');
	cout << "\n" << std::boolalpha << findNode_BFS(root, 'e');

	cout << endl;
	
	delete root;
	return 0;
}