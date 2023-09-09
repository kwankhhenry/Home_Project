#include <iostream>
#include <vector>
#include <algorithm>

#include <stdio.h>
#include <time.h>

using namespace std;

int solution_naive(vector<int> &A)
{
    int max_profit = 0;
    int buy_price = 0;
    for(size_t i = 0; i < A.size(); i++)
    {
        buy_price = A[i];
        for(size_t j = i+1; j < A.size(); j++)
        {
            int pnl = A[j] - buy_price;
            if(pnl > 0 && pnl > max_profit)
                max_profit = pnl;
            //cout << "Buy on Day " << i << ", sell on Day " << j << ", profit = " << pnl << endl;
        }
    }
    return max_profit;
}

int solution_efficient(vector<int> &A)
{
    int max_profit = 0;
    int buy_price = A[0], sell_price = 0;
    int pnl = 0;

    if(A.size() == 0) return 0;

    for(size_t i = 0; i < A.size(); i++)
    {
        if(A[i] < buy_price)
        {
            buy_price = A[i];
            pnl = 0;
        }
        sell_price = A[i];
        pnl = sell_price - buy_price;

        if(pnl > 0 && pnl > max_profit)
            max_profit = pnl;
        //cout << "Buy Price: " << buy_price << ", Sell Price at: " << sell_price << ", Max_profit: " << max_profit << endl;
    }

    return max_profit;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    int array_A[] = {23171,21011,21123,21366,21013,21367};

    vector<int> vec_A(array_A, array_A + sizeof(array_A)/sizeof(int));
    int result = solution_efficient(vec_A);

    cout << "Result is: " << result << endl;
    
    /*************************************************************************/
    printf("\nTime taken: %.8fs\n", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}
