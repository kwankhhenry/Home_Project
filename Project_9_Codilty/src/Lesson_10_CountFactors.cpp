#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(int &N)
{
    int count = 0;
    for(int i = 1; i <= N; i++)
    {
        if(N%i == 0)
        {
            count++;
            //cout << "Counting: " << i << endl;
        }
    }
    return count;
}

int solution_efficient(int &N)
{
    int count = 0;

    for(unsigned int i = 1; i*i <= (unsigned)N; i++)
    {
        if(N%i == 0)
        {
            count++;
            //cout << "Counting: " << i << endl;
        }
    }

    //cout << "sqrt of N is: " << (unsigned) sqrt(N) * (unsigned) sqrt(N) << endl;
    if((unsigned) sqrt(N) * (unsigned) sqrt(N) == (unsigned) N)
        return count*2 - 1;
    else
        return count*2;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    //int N = 1;
    //int N = 9;
    //int N = 24;
    //int N = 41;
    //int N = 93;
    //int N = 65536;
    int N = 2147483647;
    int result = solution_efficient(N);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
