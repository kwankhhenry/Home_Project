#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/* Write a function, undirectedPath, that takes in an array of edges for an undirected graph and two nodes (nodeA, nodeB).
The function should return a boolean indicating whether or not there exists a path between nodeA and nodeB */

std::unordered_map<char, vector<char>> buildGraph(const vector<std::pair<char, char>> edges)
{
	std::unordered_map<char, vector<char>> myMap;
	std::vector<char> myNeighbours;

	for(auto edge: edges)
	{
		//cout << "Visisted pair: (" << edge.first << ", " << edge.second << ")" << endl;
		if(myMap.find(edge.first) == myMap.end())
			myMap.insert(std::make_pair(edge.first, myNeighbours));

		if(myMap.find(edge.second) == myMap.end())
			myMap.insert(std::make_pair(edge.second, myNeighbours));

		myMap[edge.first].push_back(edge.second);
		myMap[edge.second].push_back(edge.first);
	}

	// View adjacency list
	/*for(auto& ele: myMap)
	{
		cout << ele.first << ": [";
		for(auto& neighbour: ele.second)
		{
			cout << neighbour << ", ";
		}
		cout << "]" << endl;
	}*/
	return myMap;
}

bool DFS_iterative(std::unordered_map<char, vector<char>>& graph, char nodeA, char nodeB)
{
	std::unordered_map<char, bool> visited;

	for(std::unordered_map<char, vector<char>>::iterator it = graph.begin(); it != graph.end(); it++)
	{
		visited[it->first] = false;
	}

	std::stack<char> myStack;
	myStack.push(nodeA);
	
	while(!myStack.empty())
	{
		char curr = myStack.top();
		myStack.pop();
		visited[curr] = true;
		cout << "Current Node: " << curr << endl;

		if(curr == nodeB) return true;

		// Find current node's neighbor
		for(char& neighbour: graph.at(curr))
		{
			if(visited[neighbour] != true)
			{
				visited[neighbour] = true;
				myStack.push(neighbour);
			}
		}
	}
	return false;
}

bool DFS_recursive(std::unordered_map<char, vector<char>>& graph, char nodeA, char nodeB, std::unordered_map<char, bool>& visited)
{
	char curr = nodeA;

	if(curr == nodeB) return true;
	if(visited[curr] == true) return false;

	visited[curr] = true;
	cout << "Current Node: " << curr << endl;

	for(char& neighbour: graph.at(curr))
	{
		if(DFS_recursive(graph, neighbour, nodeB, visited) == true)
			return true;
	}
	return false;
}

bool undirectedPath(const vector<std::pair<char, char>> edges, char nodeA, char nodeB)
{
	std::unordered_map<char, vector<char>> myGraph = buildGraph(edges);
	//return DFS_iterative(myGraph, nodeA, nodeB);

	// For recursive
	std::unordered_map<char, bool> visited;
	for(std::unordered_map<char, vector<char>>::iterator it = myGraph.begin(); it != myGraph.end(); it++)
	{
		visited[it->first] = false;
	}
	return DFS_recursive(myGraph, nodeA, nodeB, visited);
}

int main() 
{
	vector<std::pair<char, char>> edges = {
		{'i', 'j'},
		{'k', 'i'},
		{'m', 'k'},
		{'k', 'l'},
		{'o', 'n'}
	};

	cout << std::boolalpha << undirectedPath(edges, 'j', 'm') << endl;
	return 0;
}