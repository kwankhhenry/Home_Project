#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A)
{
    // Implement your solution here
    int intersect = 0;
    int N = A.size();

    if(N == 1) return 0;

    for(int i = 0; i < N; i++)
    {
        for(int j = i+1; j < N; j++)
        {
            //cout << "i: " <<  i << ", j: " << j << endl;
            //cout << "i Radius at: " << i + A[i] << ", j Radius at: " << j - A[j] << endl;
            if( i + A[i] >= j - A[j])
            {
                //cout << "Circle[" << i << "] intersects with Circle[" << j << "].\n";
                intersect++;
            }
        }
    }
    if(intersect > 10000000)
        return -1;

    return intersect;
}

int solution_efficient(vector<int> &A)
{
    // Implement your solution here
    int intersect = 0;
    int N = A.size();

    if(N <= 1) return 0;

    vector<long> startVec;
    vector<long> endVec;
    for(int i = 0; i < N; i++)
    {
        // Obtain two vectors storing the left and right endpoints of each Disc
        startVec.push_back(i-(long)A[i]);
        endVec.push_back(i+(long)A[i]);
    }
    
    sort(startVec.begin(), startVec.end());
    sort(endVec.begin(), endVec.end());

    // Iterate each endpoint to find how many start points intersect with it (except for itself)
    for(int j = 0; j < N; j++)
    {
        long cmp = endVec[j];
        int match = 0;

        // Instead of going thru all elements in startVec, since we sorted the vector, we break when we see not fit.
        
        // Attempt 1
        /*int match = count_if(startVec.begin(), startVec.end(), [&cmp](const long &x){ 
            //cout << "startVec: " << x << ", cmp: " << cmp << ", return: " << (x <= cmp) << "\n";
            return x <= cmp; });*/

        // Attempt 2
        /*for(int k = 0; k < N; k++)
        {
            if(startVec[k] <= cmp)
                match++;
            else
                break;
        }*/

        // Attempt 3 - GOOD
        vector<long>::iterator posValLessThan = upper_bound(startVec.begin(), startVec.end(), cmp);
        match = posValLessThan - startVec.begin();

        intersect += match-1-j;
        if(intersect > 10000000)
            return -1;
    }
    return intersect;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    //int array_A[] = {1, 5, 2, 1, 4, 0};
    int array_A[] = {1, 2147483647, 0};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_efficient(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
