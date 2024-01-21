#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>
#include <climits>

using namespace std;

/* Write a function, minimumIsland, that takes in a grid containing Ws and Ls. 
W represents water and L represents land. 
The function should return the size of the smallest island. 
An island is a vertically or horizontally connected region of land.

You may assume that the grid contains at least one island. */

int explore(char grid[][5], const int& row, const int& col, int r, int c, std::set<std::string>& visited)
{
	bool rowInbounds = (r >= 0 && r < row);
	bool colInbounds = (c >= 0 && c < col);

	if(!rowInbounds || !colInbounds) return 0;
	if(grid[r][c] == 'W') return 0;

	std::string id = std::to_string(r) + ',' + std::to_string(c);
	if(visited.find(id) != visited.end()) 
		return 0;
	else
		visited.emplace(id);

	int island_size = 1;
	island_size += explore(grid, row, col, r-1, c, visited);
	island_size += explore(grid, row, col, r, c-1, visited);
	island_size += explore(grid, row, col, r+1, c, visited);
	island_size += explore(grid, row, col, r, c+1, visited);
	return island_size;
}

int minimumIsland(char grid[][5], int row, int col)
{
	int minimum_island = INT_MAX;
	std::set<std::string> visited;
	for(int r = 0; r < row; r++)
	{
		for(int c = 0; c < col; c++)
		{
			int island_size = explore(grid, row, col, r, c, visited);

			if(island_size > 0)
			{
				cout << "Island has size: " << island_size << endl;
				minimum_island = min(minimum_island, island_size);
			}
		}
	}
	return minimum_island;
}

int main() 
{
	char grid[6][5] = {
		{'W', 'L', 'W', 'W', 'W'},
		{'W', 'L', 'W', 'W', 'W'},
		{'W', 'W', 'W', 'L', 'W'},
		{'W', 'W', 'L', 'L', 'W'},
		{'L', 'W', 'W', 'L', 'L'},
		{'L', 'L', 'W', 'W', 'W'}
	};

	cout << minimumIsland(grid, 6, 5) << endl;
	return 0;
}