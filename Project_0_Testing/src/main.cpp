#include <iostream>
#include <vector>
#include <stack>
#include <set>

using namespace std;

bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
	int N = static_cast<int>(prerequisites.size());

	vector<vector<int>> adj_list(numCourses, vector<int>(0));        
	for(int i = 0; i < N; i++)
	{
		adj_list[prerequisites[i][0]].push_back(prerequisites[i][1]);
	}

	vector<bool> visited(numCourses, false);
    set<int> mySet;
	stack<int> myStack;

	for(int a = 0; a < numCourses; a++)
	{
		cout << a << ": [";
		for(int b = 0; b < (int) adj_list[a].size(); b++)
		{
			cout << adj_list[a][b] << " ";
		}
		cout << "]\n";
	}   

	for(int j = 0; j < (int) adj_list.size(); j++)
	{
		if(visited[j] == false)
			myStack.push(j);
		else
			return false;
		
		visited[j] = true;

		while(!myStack.empty())
		{
			int curr = myStack.top();
			myStack.pop();
			mySet.emplace(curr);
			
			for(int& ele: adj_list[curr])
			{
				if(visited[ele] == true && mySet.contains(ele)) 
					return false;
				else
				{
					myStack.push(ele);
				}
			}
			mySet.erase(curr);
		}
	}
	return true;
}

int main() 
{
	int numCourses = 2;
	vector<vector<int>> prerequisites{{1,0},{0,1}};
	bool result = 0;

	result = canFinish(numCourses, prerequisites);
	cout << "Result is: " << result << endl;
	return 0;
}