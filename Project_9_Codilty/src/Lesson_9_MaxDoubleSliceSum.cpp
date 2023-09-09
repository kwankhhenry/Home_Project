#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <numeric>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A)
{
    int N = A.size();

    if(N <= 3) return 0;

    int leftSum=0, rightSum=0, maxSum=0;
    vector<int> LVec;
    vector<int> RVec;
    int VecSize{};

    for(int i = 0; i < N-1; i++)
    {
        if(i == 0)
            leftSum = 0;
        else
            leftSum = max(A[i], A[i]+leftSum);

        if(leftSum < 0)
            leftSum = 0;
        LVec.push_back(leftSum);

        if(i == 0)
            rightSum = 0;
        else
            rightSum = max(A[N-1-i], A[N-1-i]+rightSum);

        if(rightSum < 0)
            rightSum = 0;

        RVec.push_back(rightSum);
        //cout << "A[i]=" << A[i] << ", leftSum=" << leftSum << endl;
        //cout << "A[N-1-i]=" << A[N-1-i] << ", rightSum=" << rightSum << endl;

        VecSize++;
    }
    
    int leftGap=0, rightGap=0;
    //cout << "VecSize: " << VecSize << endl;
    for(int j = 0; j < VecSize-1; j++)
    {
        leftGap = LVec[j];
        rightGap = RVec[VecSize-2-j];

        maxSum = max(leftGap+rightGap, maxSum);
        //cout << "leftGap: " << leftGap << ", rightGap: " << rightGap << ", maxSum is: " << maxSum << endl;
    }
    return maxSum;

    /*cout << "LVec\n";
    for(auto& ele: LVec)
        cout << ele << ", ";
    cout << "\n";

    cout << "RVec\n";
    for(auto& ele: RVec)
        cout << ele << ", ";
    cout << "\n";*/
}

int solution_efficient(vector<int> &A)
{
 
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {3,2,6,-1,4,5,-1,2};
    //int array_A[] = {0,10,-5,-2,0};
    //int array_A[] = {5,17,0,3};
    //int array_A[] = {-2,-2};
    //int array_A[] = {2,-1,6};
    //int array_A[] = {-2,3};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_naive(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
