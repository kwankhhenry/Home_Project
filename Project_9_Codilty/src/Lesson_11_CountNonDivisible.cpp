#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
#include <map>

#include <stdio.h>
#include <time.h>

using namespace std;

vector<int> solution_naive(vector<int> &A)
{
    int N = A.size();
    int count = 0;
    vector<int> result;
    for(int i = 0; i < N; i++)
    {
        count = 0;
        for(int j = 0; j < N; j++)
        {
            if(A[i]%A[j] != 0)
            {
                count++;
            }
        }
        result.push_back(count);
    }
    return result;
}

vector<int> solution_efficient(vector<int> &A)
{
    int N = A.size();
    vector<int> result;

    vector<int> myVec(*max_element(A.begin(), A.end())+1,0);
    for(int i = 0; i < N; i++)
    {
        myVec[A[i]]++;

        // Edge case
        if(myVec[A[i]] == N)
        {
            result.resize(N);
            fill_n(result.begin(), N, 0);
            return result;
        }
    }

    for(int j = 0; j < N; j++)
    {
        int non_divisors_count = 0;
        int divisors_count = 0;
        //cout << "sqrt(" << A[j] << ") is: " << (int) sqrt(A[j]) << endl;
        for(int k = 1; k <= (int) sqrt(A[j]); k++)
        {
            //cout << A[j] << " % " << k << " is: " << A[j]%k << endl;
            int sub_divisors_count = 0;
            if(A[j]%k == 0)
            {
                // Increment count of divisor
                sub_divisors_count += myVec[k];
                //cout << "Divisor " << myVec[k] << " has a count of " << sub_divisors_count << endl;

                // Increment count of pair divisor
                if(A[j]/k != k)
                {
                    //cout << "Divisor " << A[j]/k << " has a count of " << myVec[A[j]/k] << endl;
                    sub_divisors_count += myVec[A[j]/k];
                }
            }
            //cout << "Up to here sub_divisors_count is: " << sub_divisors_count << endl;
            divisors_count += sub_divisors_count;
        }
        non_divisors_count = N - divisors_count;
        //cout << "Element A[" << j << "]=" << A[j] << " has count of " << non_divisors_count << endl;
        //cout << endl;
        result.push_back(non_divisors_count);
    }
    return result;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    //int array_A[] = {3,1,2,3,6};
    int array_A[] = {2};
    //int array_A[] = {15,15,15,15,15};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    vector<int> result = solution_efficient(vec_A);

    cout << "Result is: [";
    for(auto ele: result)
        cout << ele << ",";
    cout << "]" << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
