#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>

using namespace std;

/* Write a function, shortestPath, that takes in an array of edges for an undirected graph and two nodes (nodeA, nodeB). 
The function should return the length of the shortest path between A and B. 
Consider the length as the number of edges in the path, not the number of nodes. 
If there is no path between A and B, then return -1. */

std::unordered_map<char, vector<char>> buildGraph(vector<std::pair<char, char>>& graph)
{
	std::unordered_map<char, vector<char>> myGraph;

	for(std::pair<char, char> element: graph)
	{
		if(myGraph.find(element.first) == myGraph.end())
			myGraph.insert({element.first, {}});
		
		if(myGraph.find(element.second) == myGraph.end())
			myGraph.insert({element.second, {}});
		
		myGraph[element.first].push_back(element.second);
		myGraph[element.second].push_back(element.first);
	}

	// View adjacency list
	/*for(auto& ele: myGraph)
	{
		cout << ele.first << ": [";
		for(auto& neighbour: ele.second)
		{
			cout << neighbour << ", ";
		}
		cout << "]" << endl;
	}*/
	return myGraph;
}

int BFS_iteration(std::unordered_map<char, vector<char>>& adjacency_list, char src, char dest, std::unordered_map<char, bool>& visited)
{
	std::queue<std::pair<char, int>> myQueue;
	myQueue.push({src, 0});

	while(!myQueue.empty())
	{
		std::pair<char, int> current = myQueue.front();
		visited[current.first] = true;
		myQueue.pop();

		if(current.first == dest)
			return current.second;
		
		for(char& neighbour: adjacency_list.at(current.first))
		{
			if(visited[neighbour] != true)
			{
				cout << "Visited: " << neighbour << ", distance: " << current.second+1 << endl;
				visited[neighbour] = true;
				myQueue.push({neighbour, current.second+1});
			}
		}
	}
	return -1;
}

int shortestPath(vector<std::pair<char, char>>& graph, char src, char dest)
{
	std::unordered_map<char, vector<char>> adjacency_list = buildGraph(graph);
	std::unordered_map<char, bool> visited;

	return BFS_iteration(adjacency_list, src, dest, visited);
}

int main() 
{
	vector<std::pair<char, char>> graph = {
		{'w', 'x'},
		{'w', 'y'},
		{'z', 'y'},
		{'z', 'v'},
		{'w', 'v'}
	};

	cout << shortestPath(graph, 'w', 'z') << endl;
	return 0;
}