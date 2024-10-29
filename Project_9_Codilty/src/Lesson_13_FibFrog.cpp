#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <math.h>
#include <map>
#include <set>
#include <time.h>

using namespace std;

int FibA(int n)
{ 
    if (n <= 1) return n; 
    int curr = 0; 
    int prev1 = 1; 
    int prev2 = 0; 
    for (int i = 2; i <= n; i++)
    { 
        curr = prev1 + prev2;
        prev2 = prev1;
        prev1 = curr;
    } 
    return curr; 
} 

int FibB(int n){ 
    if (n <= 1) return n; 

    vector<int> dp(n + 1);
    dp[0] = 0; dp[1] = 1;
    for (int i = 2; i <= n; ++i)
    { 
        dp[i] = dp[i - 1] + dp[i - 2]; 
    } 
    return dp[n]; 
}

int solution_naive(vector<int> &A)
{
    // Compute Fib Table with F(K) up to size of vector A
    // F(0) = 0
    // F(1) = 1
    // F(2) = 1
    // F(3) = 2
    // F(4) = 3
    // F(5) = 5
    // F(6) = 8
    // F(M) = F(M - 1) + F(M - 2) if M >= 2
    cout << FibB(6) << endl;
    return 0;
}

int solution_efficient(vector<int> &A)
{

}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/
    int array_A[] = {0,0,0,1,1,0,1,0,0,0,0};
    //int array_A[] = {10};
    //int array_A[] = {2,1,2};
    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));

    int result = solution_naive(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
