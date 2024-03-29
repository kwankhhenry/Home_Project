#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution(vector<int> &A)
{
    set<int> tempSet(A.begin(), A.end());

    int smallest = 1;
    for(set<int>::iterator it = tempSet.begin(); it != tempSet.end(); ++it)
    {
        //cout << "*it is: " << *it << endl;
        if(*it > 0)
        {
            if(*it == smallest )
            {
                smallest++;
                cout << "smallest is: " << smallest << endl;
            }
            else
                return smallest;
        }
    }
    return smallest;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int arr[] = {-1,3,1,3,2,6,4,1,2};
    vector<int> v(arr, arr+sizeof(arr)/sizeof(int));
    int result = solution(v);

    cout << "Result is: " << result << endl;

    /*************************************************************************/
    printf("\n\nTime taken: %.8fs", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}