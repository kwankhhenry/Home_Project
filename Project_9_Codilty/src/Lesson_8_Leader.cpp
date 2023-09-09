#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &H)
{
    int prev = 0;
    int block = 0;
    stack<int> myStack;

    for(auto& ele: H)
    {
        if(myStack.empty()) 
        {
            myStack.push(ele);
            prev = ele;
            block++;
        }

        if(ele > prev)
        {
            myStack.push(ele);
            block++;
        }
        else
        {
            while(!myStack.empty() && myStack.top() != ele)
            {
                if (myStack.top() > ele)
                {
                    myStack.pop();
                }
                else if (myStack.top() < ele)
                {
                    myStack.push(ele);
                    block++;
                    break;
                }
                else
                {
                    myStack.pop();
                    break;
                }
            }

            if(myStack.empty()) 
            {
                myStack.push(ele);
                block++;
            }
        }
        prev = ele;
        cout << "Current height: " << ele << ", Blocks: " << block << endl;
    }
    return block;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {8,8,5,7,4,8,7,4,8};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_naive(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
