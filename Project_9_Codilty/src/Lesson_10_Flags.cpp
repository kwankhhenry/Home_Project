#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A)
{
    int N = A.size();
    int peakFlags = 0, maxFlags = 0;
    vector<int> peakVec;

    if(N < 3) return 0;

    for(int i = 1; i < N-1; i++)
    {
        int prev, next;

        prev = A[i-1];
        next = A[i+1];

        if(A[i] > prev && A[i] > next)
        {
            peakFlags++;
            peakVec.push_back(i);
            
            cout << "Peak at i=" << i << ", Peak at height: " << A[i] << endl;
        }
    }
}

int solution_efficient(vector<int> &A)
{
    int N = A.size();
    int peakFlags = 0;
    vector<int> peakVec;

    if(N < 3) return 0;

    for(int i = 1; i < N-1; i++)
    {
        if(A[i] > A[i-1] && A[i] > A[i+1])
        {
            peakFlags++;
            peakVec.push_back(i);
            //cout << "Peak at i=" << i << ", Peak at height: " << A[i] << endl;
        }
    }
    if(peakVec.size() == 0) return 0;

    int maxFlags = 0, maxLocalFlags = 0;
    for(int k = min(peakFlags, (int) sqrt(N))+1; k >=1; k--)
    {
        if(k < maxFlags)
            return maxFlags;

        //cout << "Set flags: " << k << endl;
        int previ = 0;
        int countFlags = 1;
        for(int i = 1; i < (int)peakVec.size(); i++)
        {
            if(peakVec[i] - peakVec[previ] >= k)
            {
                //cout << "k=" << k << ", peakVec[" << i << "] - peakVec[" << previ << "] = " 
                //<< peakVec[i] << " - " << peakVec[previ] << " = " << peakVec[i] - peakVec[previ] << endl;
                countFlags++;
                previ = i;
            }
        }
        //cout << "Counted flag is: " << countFlags << endl;

        maxLocalFlags = min(k, countFlags);

        if(maxLocalFlags > maxFlags)
            maxFlags = maxLocalFlags;
        
        //cout << "Max flag is: " << maxFlags << endl;
    }
    return maxFlags;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    //int array_A[] = {1,5,3,4,3,4,1,2,3,4,6,2};
    //int array_A[] = {0,0,0,0,0,1,0,1,0,1};
    int array_A[] = {3,2,1};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_efficient(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
