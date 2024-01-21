#include <iostream>
#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

/* Write a function, connectedComponentsCount, that takes in the adjacency list of an undirected graph. 
The function should return the number of connected components within the graph. */

bool DFS_iterative(std::unordered_map<int, vector<int>>& lists)
{
	return false;
}

bool explore(std::unordered_map<int, vector<int>>& graph, std::unordered_map<int, bool>& visited, int src)
{
	if(visited[src] == true)
		return false;
	
	visited[src] = true;
	//cout << "visited=" << src << endl;

	for(int& neighbour: graph.at(src))
	{
		explore(graph, visited, neighbour);
	}
	return true;
}

int DFS_recursive(std::unordered_map<int, vector<int>>& graph)
{
	// For recursive
	std::unordered_map<int, bool> visited;
	for(std::unordered_map<int, vector<int>>::iterator it = graph.begin(); it != graph.end(); it++)
	{
		visited[it->first] = false;
	}

	int count = 0;
	for(const std::pair<int, vector<int>>& list: graph)
	{
		//cout << "Testing node: " << list.first << endl;
		if(explore(graph, visited, list.first) == true)
			count++;
		//cout << "Count is: " << count << endl;
	}
	return count;
}

int connectedComponentsCount(std::unordered_map<int, vector<int>>& graph)
{
	return DFS_recursive(graph);
}

int main() 
{
	std::unordered_map<int, vector<int>> adjacncy_lists = {
		{0, {8, 1, 5}},
		{1, {0}},
		{5, {0, 8}},
		{8, {0, 5}},
		{2, {3, 4}},
		{3, {2, 4}},
		{4, {3, 2}}
	};

	std::unordered_map<int, vector<int>> adjacncy_lists2 = {
		{1, {2}},
		{2, {1,8}},
		{6, {7}},
		{9, {8}},
		{7, {6, 8}},
		{8, {9, 7, 2}}
	};

	cout << connectedComponentsCount(adjacncy_lists2) << endl;
	return 0;
}