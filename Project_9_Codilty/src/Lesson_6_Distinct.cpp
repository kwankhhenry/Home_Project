#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution(vector<int> &A)
{
    if(A.size() == 0) return 0;
    
    set<int> mySet;
    for(unsigned int i = 0; i < A.size(); i++)
    {
        mySet.insert(A[i]);
    }
    return mySet.size();
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {2, 1, 1, 2, 3, 1};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\n\nTime taken: %.8fs", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}