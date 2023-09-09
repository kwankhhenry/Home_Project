#include <iostream>
#include <stack>
#include <algorithm>

#include <stdio.h>
#include <time.h>

using namespace std;

bool solution_naive(string &S)
{
    stack<char> myStack;
    for(auto& ele: S)
    {
        if(ele == '(')
            myStack.push(ele);
        else if(ele == ')')
        {
            if(!myStack.empty())
            {
                //cout << "Popping\n";
                myStack.pop();
            }
            else
                return false;
        }
        //cout << "Size of stack is: " << myStack.size() << endl;
    }

    if(myStack.empty())
        return true;
    else
        return false;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    string array_A = {"(()(()))()"};

    bool result = solution_naive(array_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
