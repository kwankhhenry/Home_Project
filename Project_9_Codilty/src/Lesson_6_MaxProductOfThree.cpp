#include <iostream>
#include <vector>
#include <algorithm>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A)
{
    // Implement your solution here
    std::sort(A.begin(), A.end());
    vector<int> T;

    if(A.size() < 3)
        return 0;
    else if(A.size() == 3)
        return A[0]*A[1]*A[2];
    else if(A.size() == 4)
    {
        T.push_back(A[0]);
        T.push_back(A[A.size()-3]);
        T.push_back(A[A.size()-2]);
        T.push_back(A[A.size()-1]);
    }
    else
    {
        T.push_back(A[0]);
        T.push_back(A[1]);
        T.push_back(A[A.size()-3]);
        T.push_back(A[A.size()-2]);
        T.push_back(A[A.size()-1]);
    }

    int max_product = 0, cur_product = 0;
    for(size_t i = 0; i < T.size(); i++)
    {
        for(size_t j = i+1; j < T.size(); j++)
        {
            for(size_t k = j+1; k < T.size(); k++)
            {
                cur_product = T[i] * T[j] * T[k];

                /*cout << "i:" << i << ",";
                cout << "j:" << j << ",";
                cout << "k:" << k << ".";
                cout << "Cur_product: " << cur_product << ".";
                cout << "Max_product: " << max_product << ".\n";*/

                if(cur_product > max_product)
                    max_product = cur_product;
            }
        }
    }
    return max_product;
}

int solution_efficient(vector<int> &A)
{
    // Implement your solution here
    int N = A.size();
    std::sort(A.begin(), A.end());

    if(A.size() == 3)
        return A[0]*A[1]*A[2];
    
    int p1 = A[0]*A[1]*A[N-1];
    int p2 = A[N-3]*A[N-2]*A[N-1];

    return max(p1,p2);
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {-3, 1, 2, -2, 5, 6};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_naive(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
