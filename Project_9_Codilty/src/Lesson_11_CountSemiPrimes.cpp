#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
#include <map>

#include <stdio.h>
#include <time.h>

using namespace std;

vector<int> solution_naive(int N, vector<int> &P, vector<int> &Q)
{
    // Find prime numbers within range starting from 2
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

    vector<int> primeVec;
    for(int z = 0; z <= N; z++)
    {
        //cout << "Z: " << z << endl;
        if(numVec[z] == 0)
        {
            //cout << z << " ";
            primeVec.push_back(z);
        }
    }
    //cout << endl;

    int M = P.size();
    vector<int> resultVec;
    for(int k = 0; k < M; k++)
    {
        int low = P[k];
        int high = Q[k];
        int count = 0;
        for(int x = low; x <= high; x++)
        {
            for(int y = 0; y < (int) primeVec.size(); y++)
            {
                if(x%primeVec[y] == 0 && x/primeVec[y] != 1)
                {
                    int divisor = 0;
                    divisor = x/primeVec[y];
                    
                    //cout << x << " dividied by " << divisor << ".";
                    if(find(primeVec.begin(), primeVec.end(), divisor) != primeVec.end())
                    {
                        count++;
                        //cout << " Counted." << endl;
                        break;
                    }
                    //cout << endl;
                }
            }
        }
        //cout << "Count is: " << count << endl;
        resultVec.push_back(count);
    }
    return resultVec;
}

vector<int> solution_efficient(int N, vector<int> &P, vector<int> &Q)
{
    // Find prime numbers within range starting from 2
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

    // Build semiPrime Table
    vector<int> semiPrimeVec(N+1);
    for(int j = 0; j <= N; j++)
    {
        for(int k = 0; k <= N; k++)
        {
            if(numVec[j] == 0 && numVec[k] == 0 && j*k <= N)
            {
                semiPrimeVec[j*k] = 1;
            }

            if(j*k > N) break;
        }
    }

    /*cout << "semiPrime is: ";
    for(int l = 0; l <= N; l++)
    {
        if(semiPrimeVec[l] == 1)
            cout << l << ", ";
    }
    cout << endl;*/

    // Build cumulative semiPrime Table
    vector<int> semiPrimeCum(N+1);
    int cumSum = 0;
    for(int x = 0; x <= N; x++)
    {
        cumSum += semiPrimeVec[x];
        semiPrimeCum[x] = cumSum;
        //cout << "At x=" << x << ", cumSum is: " << cumSum << endl;
    }

    // Find difference in counts
    int M = P.size();
    vector<int> resultVec(M);
    for(int y = 0; y < M; y++)
    {
        resultVec[y] = semiPrimeCum[Q[y]] - semiPrimeCum[P[y]-1];
        //cout << "Count is: " << semiPrimeCum[Q[y]] - semiPrimeCum[P[y]] << endl;
    }
    return resultVec;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    int array_P[] = {1,4,16};
    int array_Q[] = {26,10,20};
    int N = 26;

    vector<int> vec_P(array_P, array_P + sizeof(array_P)/sizeof(int));
    vector<int> vec_Q(array_Q, array_Q + sizeof(array_P)/sizeof(int));
    vector<int> result = solution_efficient(N, vec_P, vec_Q);

    cout << "Result is: [";
    for(auto ele: result)
        cout << ele << ",";
    cout << "]" << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
