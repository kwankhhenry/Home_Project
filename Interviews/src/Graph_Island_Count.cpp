#include <iostream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

/* Write a function, islandCount, that takes in a grid containing Ws and Ls. W represents water and L represents land. 
The function should return the number of islands on the grid. 
An island is a vertically or horizontally connected region of land. */

bool explore(char grid[][5], const int& row, const int& col, int r, int c, std::set<std::string>& visited)
{
	bool rowInbounds = (r >= 0 && r < row);
	bool colInbounds = (c >= 0 && c < col);

	if(!rowInbounds || !colInbounds) return false;
	if(grid[r][c] == 'W') return false;

	std::string id = std::to_string(r) + ',' + std::to_string(c);
	if(visited.find(id) != visited.end()) 
		return false;
	else
		visited.emplace(id);

	explore(grid, row, col, r-1, c, visited);
	explore(grid, row, col, r, c-1, visited);
	explore(grid, row, col, r+1, c, visited);
	explore(grid, row, col, r, c+1, visited);
	return true;
}

int islandCount(char grid[][5], int row, int col)
{
	int count = 0;
	std::set<std::string> visited;
	for(int r = 0; r < row; r++)
	{
		for(int c = 0; c < col; c++)
		{
			if(explore(grid, row, col, r, c, visited) == true)
				count++;
		}
	}
	return count;
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

	cout << islandCount(grid, 6, 5) << endl;
	return 0;
}