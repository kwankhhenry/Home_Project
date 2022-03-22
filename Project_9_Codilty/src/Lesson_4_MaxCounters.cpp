#include <iostream>
#include <vector>
#include <algorithm>
#include <map>

#include <stdio.h>
#include <time.h>

using namespace std;

vector<int> solution(int N, vector<int> &A)
{
    vector<int> myVec(N, 0);
    int max_num = 0, curr = 0;
    int bottomline = 0;

    for(vector<int>::iterator it = A.begin(); it != A.end(); ++it)
    {
        if(*it <= N && *it >= 1)
        {
            if(myVec[*it - 1] < bottomline)
            {
                myVec[*it - 1] = bottomline + 1;
                curr = myVec[*it - 1];
            }
            else
                curr = ++myVec[*it - 1];

            if(curr > max_num)
                max_num = curr;
        }
        
        if(*it > N)
        {
            //myVec.assign(N, max_num);
            bottomline = max_num;
        }
        
        /*cout << "myVec is: (";
        for(vector<int>::iterator it = myVec.begin(); it != myVec.end(); ++it)
            cout << *it << ", ";
        cout << ")\n";*/
    }
    //cout << "Bottom line is: " << bottomline << endl;
    for(int i = 0; i < N; i++)
    {
        if(myVec[i] < bottomline)
            myVec[i] = bottomline;
    }
    return myVec;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int arr[] = {3, 4, 4, 6, 1, 4, 4};
    //int arr[] = {1, 1, 2, 1};
    vector<int> v(arr, arr+sizeof(arr)/sizeof(int));

    vector<int> result = solution(5, v);

    for(vector<int>::iterator x = result.begin(); x != result.end(); ++x)
        cout << *x << endl;

    //cout << "Result is: " << result << endl;

    /*************************************************************************/
    printf("\n\nTime taken: %.8fs", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}