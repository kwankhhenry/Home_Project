#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution(vector<int> &A)
{
    float min_average = 2147483647;
    int min_i = 0;

    for(unsigned i = 0; i < A.size() - 2; i++)
    {
        float cal_average_A = (float) (A[i] + A[i+1])/2; // T + 2 Average
        float cal_average_B = (float) (A[i] + A[i+1] + A[i+2])/3; // T + 3 Average

        if(cal_average_A < min_average || cal_average_B < min_average)
        {
            min_average = std::min(cal_average_A, cal_average_B);
            min_i = i;
        }
    }

    // Calculate edge case at last 2 elements
    float cal_average_C = (A[A.size()-1] + A[A.size()-2])/2;
    if(cal_average_C < min_average)
    {
        min_average = cal_average_C;
        min_i = A.size() - 2;
    }
    return min_i;
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