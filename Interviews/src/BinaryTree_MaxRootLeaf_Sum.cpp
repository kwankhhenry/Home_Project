#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>
#include <climits>

using namespace std;

/* Write a function, maxPathSum, that takes in the root of a binary tree that contains number values. 
The function should return the maximum sum of any root to leaf path within the tree.

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

int maxPathSum_DFS_recursive(Node* root)
{
	if(!root) return 0;

	int sum_left = maxPathSum_DFS_recursive(root->left);
	int sum_right = maxPathSum_DFS_recursive(root->right);
	int max_child = std::max(sum_left, sum_right);

	return root->data + max_child;
}

int maxPathSum_DFS_iterative(Node* root)
{
	if(!root) return 0;

	std::stack<std::pair<Node*, int>> myStack;
	myStack.push({root, root->data});

	int max_value = INT_MIN;
	while(!myStack.empty())
	{
		std::pair<Node*, int> current = myStack.top();
		myStack.pop();
		max_value = std::max(max_value, current.second);

		if(current.first->right)
			myStack.push({current.first->right, current.first->right->data + current.second});

		if(current.first->left)
			myStack.push({current.first->left, current.first->left->data + current.second});
	}
	return max_value;
}

int main() 
{
	Node* root = NULL;
	root = new Node(3);
	root->left = new Node(11);
	root->right = new Node(4);
	root->left->left = new Node(4);
	root->left->right = new Node(-2);
	root->right->right = new Node(1);

	root->printPreOrder(root);
	cout << endl;
	root->printDFSOrder(root);
	cout << endl;
	
	root->printBFSOrder(root);

	cout << "\n" << maxPathSum_DFS_recursive(root);
	cout << "\n" << maxPathSum_DFS_iterative(root);

	cout << endl;
	
	delete root;
	return 0;
}