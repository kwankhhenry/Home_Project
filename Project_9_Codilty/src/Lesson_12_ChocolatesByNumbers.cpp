#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
#include <map>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(int N, int M)
{
    vector<int> chocolates(N);

    if(N == 1) return 1;

    chocolates[0] = 1;
    //cout << "Chocolate 0 eaten." << endl;

    int next_chocolate = M;
    int count = 1;
    while(chocolates[next_chocolate] == 0)
    {
        chocolates[next_chocolate] = 1;
        //cout << "Chocolate " << next_chocolate << " eaten." << endl;
        next_chocolate = (next_chocolate + M) % N;
        count++;
    }
    return count;
}

int solution_efficient(int N, int M)
{
    // Least Common Multiple (LCM) = N * M / Greatest Common divisor (GCD)
    int remainder = 0;
    int quotient = N, divisor = M;
    do
    {
        remainder = quotient%divisor;
        //cout << "Quotient is: " << quotient << ", divisor is: " << divisor << ", Remainder is: " << remainder << endl;
        if(remainder == 0) 
            return N/divisor;
        else
        {
            quotient = divisor;
            divisor = remainder;
        }
    } while(remainder != 0);
    //cout << "GCD is: " << divisor << endl;
    return N/divisor;
}

int gcd(int a, int b)
{
    //cout << "a: " << a << ", b: " << b << ", a/b: " << a/b << ", a%b: " << a%b << endl;
    if(a%b == 0) return b;
    else return gcd(b, a%b);
}

int solution_optimal(int N, int M)
{
    return N/gcd(N,M);
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    //int N = 10, M = 4;
    //int N = 2, M = 1;
    int N = 12, M = 21;
    //int N = 1000000000, M = 1;

    int result = solution_efficient(N, M);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
