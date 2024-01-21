#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>
#include <queue>

using namespace std;

/*  */

class Node
{
private:
	int data;
	Node* left;
	Node* right;
public:
	Node(): data(0), left(NULL), right(NULL){};
	Node(int value): data(value), left(NULL), right(NULL){};

	Node* insert_recursive(Node* parent, int val)
	{
		if(parent == NULL)
			return new Node(val);

		if(val < parent->data)
		{
			parent->left = insert_recursive(parent->left, val);
		}
		else
		{
			parent->right = insert_recursive(parent->right, val);
		}
		return parent;
	}

	Node* insert_iterative(Node* parent, int val)
	{
		stack<Node*> myStack;
		myStack.push(parent);

		if(parent == NULL) return new Node(val);

		while(!myStack.empty())
		{
			Node* current = myStack.top();
			myStack.pop();

			if(val < current->data)
			{
				if(current->left == NULL)
					current->left = new Node(val);
				else
					myStack.push(current->left);
			}
			else if(val > current->data)
			{
				if(current->right == NULL)
					current->right = new Node(val);
				else
					myStack.push(current->right);
			}
		}
		return parent;
	}

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

int main() 
{
	Node* root = NULL;
	root = root->insert_iterative(root, 10);
	root->insert_iterative(root, 13);
	root->insert_iterative(root, 2);
	root->insert_iterative(root, 6);
	root->insert_iterative(root, 15);
	root->insert_iterative(root, 1);
	root->insert_iterative(root, 11);

	root->printPreOrder(root);
	cout << endl;
	root->printDFSOrder(root);
	cout << endl;
	
	root->printBFSOrder(root);
	
	cout << endl;
	
	delete root;
	return 0;
}