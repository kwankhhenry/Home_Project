#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A)
{
    int maxSum = INT_MIN;
    int tempSum = 0;
    
    if(A.size() == 0) return 0;

    for(size_t i = 0; i < A.size(); i++)
    {
        if(i == 0)
            tempSum = A[0];
        else
        {
            if(tempSum + A[i] > 0)
            {
                if(A[i] > tempSum + A[i])
                    tempSum = A[i];
                else
                    tempSum = A[i] + tempSum;
            }
            else
            {
                tempSum = A[i];
            }
        }

        if(tempSum > maxSum)
            maxSum = tempSum;

        cout << "MaxSum=" << maxSum << ", tempSum=" << tempSum << ", at: " << i << endl;
    }
    return maxSum;
}

int solution_efficient(vector<int> &A)
{
    int maxSum;
    int tempSum = 0;
    
    if(A.size() == 0) 
        return 0;
    else
        maxSum = tempSum = A[0];

    for(size_t i = 1; i < A.size(); i++)
    {
        tempSum = max(A[i], tempSum + A[i]);

        if(tempSum > maxSum)
            maxSum = tempSum;
        cout << "MaxSum=" << maxSum << ", tempSum=" << tempSum << ", at: " << i << endl;
    }
    return maxSum;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {3,2,-6,4,0};
    //int array_A[] = {-10};
    //int array_A[] = {-2,1};
    //int array_A[] = {-2,-2};
    //int array_A[] = {2,-1,6};
    //int array_A[] = {-2,3};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_efficient(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
