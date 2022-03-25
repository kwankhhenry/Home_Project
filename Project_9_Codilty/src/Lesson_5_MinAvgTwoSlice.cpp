#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution(vector<int> &A)
{

}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {4, 2, 2, 5, 1, 5, 8};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\n\nTime taken: %.8fs", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}