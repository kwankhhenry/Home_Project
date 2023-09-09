#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A, vector<int> &B)
{
    // Implement your solution here
    int N = A.size();
    int alive = 0;
    stack<int> fish;
    for(int i = 0; i < N; i++)
    {
        if(B[i] == 0)
        {
            alive++;

            while(!fish.empty() && A[i] > fish.top())
            {
                fish.pop();
                alive--;
            }

            if(!fish.empty() && A[i] < fish.top())
                alive--;
        }
        else
        {
            fish.push(A[i]);
            alive++;
        }
        //cout << "Alive fish: " << alive << ", Fish stack: " << fish.size() << endl;
    }
    return alive;
}

int solution_efficient(vector<int> &A, vector<int> &B)
{
    // Implement your solution here
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {4,3,2,1,5,4,3,5,3,6};
    int array_B[] = {0,1,0,0,0,0,0,1,1,0};

    vector<int> vec_A = {array_A, array_A + sizeof(array_A)/sizeof(array_A[0])};
    vector<int> vec_B(array_B, array_B + sizeof(array_B)/sizeof(array_B[0]));

    int result = solution_naive(vec_A, vec_B);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
