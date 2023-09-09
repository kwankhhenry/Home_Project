#include <iostream>
#include <stack>
#include <map>
#include <algorithm>

#include <stdio.h>
#include <time.h>

using namespace std;

bool solution_naive(string &S)
{
    // Implement your solution here
    int N = S.length();

    // Set up a dictionary for bracket reference
    map<char,char> myMap;
    myMap.insert(pair<char,char>('}','{'));
    myMap.insert(pair<char,char>(']','['));
    myMap.insert(pair<char,char>(')','('));

    stack<char> myStack;
    for(int i = 0; i < N; i++)
    {
        //cout << "A[" << i << "] is: " << A[i] << endl;
        if(S[i] == '{' || S[i] == '[' || S[i] == '(')
            myStack.push(S[i]);
        
        if(S[i] == '}' || S[i] == ']' || S[i] == ')')
        {
            if(!myStack.empty())
            {
                char matchingChar = myMap[S[i]];
                if(matchingChar != myStack.top())
                    return false;
                else
                    myStack.pop();
            }
            else
            {
                return false;
            }
        }
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

    string array_A = {"{[()()]}"};

    bool result = solution_naive(array_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
