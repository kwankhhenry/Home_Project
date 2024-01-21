#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/* Write a function, hasPath, that takes in an object representing the adjacency list of a directed acyclic graph 
and two nodes (src, dst). The function should return a boolean indicating whether or not there exists a directed path between
the source and destination nodes. */

bool DFS_iterative(const std::unordered_map<char, std::vector<char>>& graph, char src, char dest)
{
	std::stack<char> myStack;
	myStack.push(src);
	
	while(myStack.size() > 0)
	{
		char curr = myStack.top();
		myStack.pop();
		cout << "Char is: " << curr << endl;
		
		if(curr == dest)
			return true;

		// Find current's neighbour node
		for(char neighbour: graph.at(curr))
		{
			myStack.push(neighbour);
		}
	}
	return false;
}

bool DFS_recursive(const std::unordered_map<char, std::vector<char>>& graph, char src, char dest)
{
	cout << "Char is: " << src << endl;
	// Base case - end of recursive loop
	if(src == dest) return true;

	// Find current's neighbour node
	for(char neighbour: graph.at(src))
	{
		if(DFS_recursive(graph, neighbour, dest) == true)
			return true;
	}
	return false;
}

bool hasPath(const std::unordered_map<char, std::vector<char>>& graph, char src, char dest)
{
	return DFS_iterative(graph, src, dest);
}

int main() 
{
	std::unordered_map<char, std::vector<char>> graph_00 = {
		{'f',{'g','i'}},
		{'g',{'h'}},
		{'h',{}},
		{'i',{'g','k'}},
		{'j',{'i'}},
		{'k',{}}
	};

	cout << std::boolalpha << hasPath(graph_00, 'f', 'k') << endl;
	return 0;
}