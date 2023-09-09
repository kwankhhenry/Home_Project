#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A)
{
    if(A.empty()) return -1;

    map<int,int> myMap;
    for(auto& ele: A)
    {
        myMap[ele]++;
    }

    map<int,int>::iterator it = std::max_element(myMap.begin(), myMap.end(), 
        [](const pair<int,int> &x, const pair<int,int> &y){ return x.second < y.second; });
    //cout << "Leader key is: " << it->first << ", counted occurrence is: " << it->second << endl;
    
    // Condition: if leader is less than 1/2 of array size then return -1
    if((size_t)it->second <= A.size()/2) return 0;

    int leader = it->first;
    int leader_total = it->second;
    int equiLeader = 0;
    int left_leader = 0, right_leader = 0;
    int left_sequence = 0, right_sequence = 0;
    for(size_t i = 0; i < A.size(); i++)
    {
        left_sequence = (int) i+1;
        right_sequence = (int) A.size() - (i+1);
        if(A[i] == leader)
        {
            left_leader++;
            right_leader = leader_total - left_leader;
        }

        if(left_leader > (int) left_sequence/2 && right_leader > (int) right_sequence/2)
            equiLeader++;
    }
    return equiLeader;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {4,3,4,4,4,2};
    //int array_A[] = {2,1,1,3};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_naive(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
