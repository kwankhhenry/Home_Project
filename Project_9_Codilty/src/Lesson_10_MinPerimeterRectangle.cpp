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
}

int solution_efficient(int &N)
{
    int minPerimeter = INT_MAX;
    int Perimeter = 0;

    for(unsigned int i = 1; i*i <= (unsigned)N; i++)
    {
        if(N%i == 0)
        {
            Perimeter = 2 * (i + N/i);
            //cout << "N is: " << N << ", i is: " << i << ", Calculated perimeter is: " << Perimeter << endl;
        }

        if(Perimeter < minPerimeter)
            minPerimeter = Perimeter;
    }
    //cout << "minPerimeter is: " << minPerimeter << endl;
    return minPerimeter;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    int N = 30;
    //int N = 65536;
    //int N = 2147483647;
    int result = solution_efficient(N);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
