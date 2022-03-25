#include <iostream>
#include <vector>
#include <algorithm>
#include <set>

#include <stdio.h>
#include <time.h>

using namespace std;

vector<int> solution(string &S, vector<int> &P, vector<int> &Q)
{
    // A -> 1, C -> 2, G -> 3, T -> 4  
    vector<int> A(S.size(),0), C(S.size(),0), G(S.size(),0), T(S.size(),0);
    int a = 0, c = 0, g = 0, t = 0;
    vector<int> outVec;
    for(size_t i = 0; i < S.length(); i++)
    {
        if(S[i]=='A') ++a;
        if(S[i]=='C') ++c;
        if(S[i]=='G') ++g;
        if(S[i]=='T') ++t;

        A[i] = a;
        C[i] = c;
        G[i] = g;
        T[i] = t;
    }

    for(size_t j = 0; j < P.size(); j++)
    {
        //cout << "Query: " << j + 1 << endl;
        if(Q[j] == P[j])
        {
            if(A[Q[j]] == A[P[j]] && S[P[j]] == 'A') outVec.push_back(1);
            else if(C[Q[j]] == C[P[j]] && S[P[j]] == 'C') outVec.push_back(2);
            else if(G[Q[j]] == G[P[j]] && S[P[j]] == 'G') outVec.push_back(3);
            else if(T[Q[j]] == T[P[j]] && S[P[j]] == 'T') outVec.push_back(4);
        }

        else if(A[Q[j]] > A[P[j]] || S[P[j]] == 'A') outVec.push_back(1);
        else if(C[Q[j]] > C[P[j]] || S[P[j]] == 'C') outVec.push_back(2);
        else if(G[Q[j]] > G[P[j]] || S[P[j]] == 'G') outVec.push_back(3);
        else if(T[Q[j]] > T[P[j]] || S[P[j]] == 'T') outVec.push_back(4);

        //cout << "outVec: " << outVec[j] << endl;
    }
    return outVec;
}

int main()
{
    clock_t tStart = clock();
    /*************************************************************************/

    string s = "CAGCCTA";
    int array_P[] = {2, 5, 0};
    int array_Q[] = {4, 5, 6};

    vector<int> vec_P(array_P, array_P + sizeof(array_P)/sizeof(int));
    vector<int> vec_Q(array_Q, array_Q + sizeof(array_Q)/sizeof(int));
    vector<int> result = solution(s, vec_P, vec_Q);

    cout << "Result is: ";
    for(vector<int>::iterator it = result.begin(); it != result.end(); ++it)
        cout << *it << " ";
    
    /*************************************************************************/
    printf("\n\nTime taken: %.8fs", (double)(clock() - tStart)/CLOCKS_PER_SEC);
    return 0;
}