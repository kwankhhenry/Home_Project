#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
#include <map>

#include <stdio.h>
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

    for(int i = prime_init; i <= (int) sqrt(N); i++)
    {
        //cout << "Prime is: " << i << endl;
        if(numVec[i] == 0)
        {
            // For each prime, set all multipliers to True (1 = Not Prime)
            sequence = i*i;
            while(sequence <= N)
            {
                //cout << "i is: " << i << ", prime_j is: " << sequence << endl;
                numVec[sequence] = 1;
                sequence += i;
            }
        }
    }

    // Prime number checks
    /*for(int j = 0; j <= N; j++)
    {
        if(numVec[j] == 0)
            cout << j << " ";
    }*/

    // Find common divisor
    int M = A.size();
    int count = 0, tempCount = 0;
    for(int k = 0; k < M; k++)
    {
        tempCount = 0;
        //cout << "Set #" << k << endl;

        if(A[k] == 1 && B[k] == 1)
            tempCount++;

        for(int j = 1; j <= N; j++)
        {
            if(numVec[j] == 0)
            {
                //cout << "Prime " << j;
                if(A[k]%j == 0 && B[k]%j == 0)
                {
                    tempCount++;
                    //cout << ". Count++.";
                }

                if((A[k]%j == 1 && B[k]%j == 0) || (A[k]%j == 0 && B[k]%j == 1))
                {
                    //cout << ". Break." << endl;
                    tempCount = 0;
                    break;
                }                
                cout << endl;
            }
        }

        if(tempCount > 0)
            count++;
    }
    return count;
}

int solution_efficient(vector<int> &A, vector<int> &B)
{

}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    //int array_A[] = {15,10,3};
    int array_A[] = {1};
    //int array_A[] = {2,1,2};
    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));

    //int array_B[] = {75,30,5};
    int array_B[] = {1};
    //int array_B[] = {1,2,2};
    vector<int> vec_B(array_B, array_B + sizeof(array_B)/sizeof(int));

    int result = solution_naive(vec_A, vec_B);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
