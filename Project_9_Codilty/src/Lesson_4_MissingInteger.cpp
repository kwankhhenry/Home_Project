#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution(vector<int> &A)
{
    std::sort(A.begin(), A.end());

    int smallest = 1;
    for(vector<int>::iterator it = A.begin(); it < A.end(); ++it)
    {
        if(*it == smallest )
            smallest++;
    }
    return smallest;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int arr[] = {1,3,6,4,1,2};
    vector<int> v(arr, arr+sizeof(arr)/sizeof(int));
    int result = solution(v);

    cout << "Result is: " << result << endl;

    /*************************************************************************/
    printf("\n\nTime taken: %.8fs", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}