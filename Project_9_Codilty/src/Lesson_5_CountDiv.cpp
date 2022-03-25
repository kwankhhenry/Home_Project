#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution(int A, int B, int K)
{
    /* Brute Force 
    vector<int> myVec;

    if(K > A && K < B)
    {
        if(A == 0) 
            myVec.push_back(A);
        
        A = K;
    }

    for(int i = A; i <= B; i++)
    {  
        if(i % K == 0)
            myVec.push_back(i);
    }
    return myVec.size();*/

    // Efficient Way
    int Div_A = A / K;
    int Div_B = B / K;

    int count = Div_B - Div_A;
    if (A % K == 0)
        count++;

    return count;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int a = 6, b = 15, k = 3;
    int result = solution(a, b, k);

    cout << "Result is: " << result << endl;

    /*************************************************************************/
    printf("\n\nTime taken: %.8fs", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}