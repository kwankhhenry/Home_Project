#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution(vector<int> &A)
{
    int east = 0;
    unsigned long int intercept = 0;
    for(vector<int>::iterator it = A.begin(); it != A.end(); ++it)
    {
        if(*it == 0)
            east++;
        else if(*it == 1)
            intercept = intercept + east;
    }
    if (intercept > 1000000000) return -1;

    return intercept;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int arr[] = {0, 1, 0, 1, 1};
    vector<int> v(arr, arr+sizeof(arr)/sizeof(int));
    int result = solution(v);

    cout << "Result is: " << result << endl;

    /*************************************************************************/
    printf("\n\nTime taken: %.8fs", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}