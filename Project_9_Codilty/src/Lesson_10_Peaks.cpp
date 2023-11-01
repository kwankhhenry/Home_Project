#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
#include <map>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A)
{
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

    for(int k = peakFlags; k >=1; k--)
    {
        //cout << "Peak Num: " << k << endl;
        int distance = N/k;
        //cout << "Distance per peaks: " << distance << endl;

        vector<int> sliceVec(k);
        if(N%k == 0)
        {
            int ss = 0;
            for(int i = 0; i < (int)peakVec.size(); i++)
            {
                //sliceVec[peakVec[i]/distance]++;
                //cout << "k=" << k << ", peakVec[" << i << "] having index at: " << peakVec[i] << ", hash to :" << peakVec[i]/distance << endl;

                if(sliceVec[peakVec[i]/distance] == 0)
                {
                    sliceVec[peakVec[i]/distance]++;
                    ss++;
                }
            }

            /*for(size_t i = 0; i < sliceVec.size(); i++)
            {
                cout << "i = " << i << ", sliceVec[" << i << "] is: " << sliceVec[i] << endl;
            }*/

            if(ss == k)
                return k;
        }
    }
    return 0;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    //int array_A[] = {1,2,3,4,3,4,1,2,3,4,6,2};
    //int array_A[] = {1,2,3,4,3,3,1,2,5,4,6,2};
    //int array_A[] = {1,2,3,4,3,4,1,2,3,4,4,4};
    int array_A[] = {0,0,0,0,0,0,0,0,0,1,0,1,0,1};
    //int array_A[] = {3,2,1};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_efficient(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
