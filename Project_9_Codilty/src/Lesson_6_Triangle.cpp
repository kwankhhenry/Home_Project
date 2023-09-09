#include <iostream>
#include <vector>
#include <algorithm>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution(vector<int> &A)
{
    // Implement your solution here
    int N = A.size();
    sort(A.begin(), A.end());

    if(N < 3) return 0;

    for(int i = 0; i < N-2; i++)
    {
        if(A[i] > A[i+2] - A[i+1])
            return true;
    }
    return false;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {10, 2, 5, 1, 8, 20};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
