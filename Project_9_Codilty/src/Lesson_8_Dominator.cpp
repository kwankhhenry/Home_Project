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
    //cout << "Dominator key is: " << it->first << ", counted value is: " << it->second << endl;
    
    // Condition: if dominator less than 1/2 of array size then return -1
    if((size_t)it->second <= A.size()/2) return -1;

    // Condition: if multiple value has equal dominant occurrence then return -1
    int count = count_if(myMap.begin(), myMap.end(),
        [it](const pair<int,int> &x){ return x.second >= it->second; });
    //cout << "Number of dominator occurring: " << count << endl;
    if (count > 1) return -1;

    int index = 0;
    for(size_t i = 0; i < A.size(); i++)
    {
        //cout << "Index: " << i << ", value is: " << A[i] << endl;
        if(A[i] == it->first)
        {
            index = i;
            return index;
        }
    }
    return index;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    //int array_A[] = {0,4,3,2,3,-1,3,3};
    //int array_A[] = {0,0,1,1,1};
    int array_A[] = {2,1,1,3};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_naive(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
