#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>
#include <limits.h>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &H)
{
    int N = H.size();
    int block = 0;
    int localMin = INT_MAX;
    vector<int> stoneVec;

    if(N == 0) return 0;
    if(N == 1) return 1;

    int prev = 0;
    for(int i = 0; i < N; i++)
    {
        if(H[i] < localMin)
        {
            localMin = H[i];
            stoneVec.clear();
        }

        if(H[i] > prev)
        {
            stoneVec.push_back(H[i]);
            block++;
        }
        else if(H[i] < prev)
        {
            if(find(stoneVec.begin(), stoneVec.end(), H[i]) == stoneVec.end())
            {
                stoneVec.push_back(H[i]);
                block++;
            }

        }
        cout << "At H[" << i << "]=" << H[i] << ", prev=" << prev << ", block#=" << block << ", localMin at " << localMin << endl; 
        prev = H[i];
    }
    return block;
}

int solution_efficient(vector<int> &H)
{
    int N = H.size();
    int block = 0;
    vector<int> stoneVec;

    if(N == 0) return 0;
    if(N == 1) return 1;

    int prev = 0;
    for(int i = 0; i < N; i++)
    {
        if(H[i] > prev)
        {
            stoneVec.push_back(H[i]);
            block++;
        }
        else if(H[i] < prev)
        {
            int j=stoneVec.size()-1;
            //cout << "popping stoneVec[" << j << "]=" << stoneVec[j] << endl;
            while(H[i] < stoneVec[j])
            {
                stoneVec.pop_back();
                j--;
            }
            if(H[i] != stoneVec[stoneVec.size()-1])
            {
                //cout << "What the " << H[i] << ", " << stoneVec[stoneVec.size()-1] << endl;
                block++;
                stoneVec.push_back(H[i]);
            }
        }
        //cout << "At H[" << i << "]=" << H[i] << ", prev=" << prev << ", block#=" << block << ", last element at vec is: " << stoneVec[stoneVec.size()-1] << endl; 
        prev = H[i];
    }
    return block;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    //int array_A[] = {8,8,5,7,9,8,7,4,8};
    //int array_A[] = {3,2,1};
    //int array_A[] = {0,0,0,0,0};
    int array_A[] = {1,2,3,4,5,6,7,8,9,8,7,6,5,4,3,2,1};

    vector<int> vec_A = {array_A, array_A + sizeof(array_A)/sizeof(array_A[0])};

    int result = solution_efficient(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
