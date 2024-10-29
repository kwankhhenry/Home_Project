#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
#include <map>
#include <set>

//#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A, vector<int> &B)
{
    // Get the max element within A & B
    int N = max(*max_element(A.begin(), A.end()), *max_element(B.begin(), B.end()));
    //cout << "Max element is: " << N << endl;

    // Get range of prime numbers range starting from 2
    vector<int> numVec(N+1);
    int prime_init = 2, sequence = 0;

    numVec[0] = 1;
    numVec[1] = 1;

    // Build prime number table
    for(int i = prime_init; i <= (int) sqrt(N); i++)
    {
        //cout << "Prime is: " << i << endl;
        if(numVec[i] == 0)
        {
            // For each prime, set all multipliers to True (1 = Not Prime)
            sequence = i*i; // 4, 9, 16, 25, 36, 49, 64
            while(sequence <= N)
            {
                //cout << "i is: " << i << ", prime_j is: " << sequence << endl;
                numVec[sequence] = 1;
                sequence += i;
            }
        }
    }

    // Prime number checks
    set<int> mySet;
    for(int j = 0; j <= N; j++)
    {
        if(numVec[j] == 0)
        {
            mySet.insert(j);
            //cout << j << " ";
        }
    }
    //cout << endl;

    // Find common divisor
    int M = A.size();
    int count = 0, tempCount = 0;
    for(int k = 0; k < M; k++)
    {
        tempCount = 0;
        //cout << "Set #" << k << endl;
        vector<int> A_bucket;
        vector<int> B_bucket;

        if(A[k] == 1 && B[k] == 1)
            tempCount++;

        for(set<int>::iterator it = mySet.begin(); it != mySet.end(); it++)
        {
            //cout << "Prime " << j;
            if(A[k]% (*it) == 0 && B[k]% (*it) == 0)
            {
                tempCount++;
            }

            if((A[k]% (*it) != 0 && B[k]% (*it) == 0) || (A[k]% (*it) == 0 && B[k]% (*it) != 0))
            {
                tempCount = 0;
                break;
            }
        }

        if(tempCount > 0)
            count++;
    }
    return count;
}

int GCD(int a, int b)
{
    if(a == 0)
        return b;
    return GCD(b%a, a);
}

bool hasSamePrimeDivisor(int a, int b)
{
    int gcdValue = GCD(a,b);
    int gcdA;
    int gcdB;
    while(a!=1) {
        gcdA = GCD(a,gcdValue);
        if(gcdA==1)
            break;
        a = a/gcdA;
    }
    if(a!=1)  {
        return false;
    }

    while(b!=1) {
        gcdB = GCD(b,gcdValue);
        if(gcdB==1)
            break;
        b = b/gcdB;
    }
    return b==1;
}

int solution_efficient(vector<int> &A, vector<int> &B)
{
    int M = A.size();
    int count = 0;

    for(int k = 0; k < M; k++)
    {
        if(hasSamePrimeDivisor(A[k], B[k]))
            count++;
    }
    return count;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    //int array_A[] = {15,10,3};
    int array_A[] = {10};
    //int array_A[] = {2,1,2};
    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));

    //int array_B[] = {75,30,5};
    int array_B[] = {30};
    //int array_B[] = {1,2,2};
    vector<int> vec_B(array_B, array_B + sizeof(array_B)/sizeof(int));

    int result = solution_efficient(vec_A, vec_B);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
