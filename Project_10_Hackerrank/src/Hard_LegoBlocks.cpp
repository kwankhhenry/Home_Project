#include <bits/stdc++.h>

using namespace std;

string ltrim(const string &);
string rtrim(const string &);
vector<string> split(const string &);

/*
 * Complete the 'legoBlocks' function below.
 *
 * The function is expected to return an INTEGER.
 * The function accepts following parameters:
 *  1. INTEGER n
 *  2. INTEGER m
 */

// Declare the "modulo" int 10^9 + 7 to avoid int overflow
const int modulo = 1000000007;

// max height and width of the wall
const int maxn = 1000;

// Initialize a matrix and two vectors of the max dimension
long long T[maxn+1][maxn+1];
long long B[maxn+1], G[maxn+1];

void init(){
    T[1][0] = 1;

    // Fix the row i=1 and iterate through all the columns
    for(int j = 1; j <= maxn; j++){
        T[1][j] = T[1][j-1];

        if(j >= 2) T[1][j] += T[1][j-2];
        if(j >= 3) T[1][j] += T[1][j-3];
        if(j >= 4) T[1][j] += T[1][j-4];

        // now we use the modulo variable
        T[1][j] %= modulo;
    }

    // Now we iterate thru all the remaining elements of the matrix
    for(int i = 2; i <= maxn; i++){
        for(int j = 1; j <= maxn; j++){
            T[i][j] = T[i-1][j] * T[1][j];
            T[i][j] %= modulo;
        }
    }
}

int legoBlocks(int n, int m) {
    init();

    // Initialize the second value of the two vectors
    B[1] = 0;
    G[1] = 1;

    // Now iterate through all the remaining elements of the vector and matrix
    for(int j = 2; j <= m; j++){
        B[j] = 0;
        for(int k=1; k<j; k++){
            B[j] += T[n][j-k] * G[k];
            B[j] %= modulo;
        }
        G[j] = (T[n][j] + modulo - B[j]) % modulo;
    }
    return G[m];
}

int main()
{
    std::ifstream file("input/Hard_LegoBlocks.txt");
    if(file.is_open())
    {
        string t_temp;
        file >> t_temp;
        file.ignore();
        int t = stoi(ltrim(rtrim(t_temp)));

        for (int t_itr = 0; t_itr < t; t_itr++) {
            string first_multiple_input_temp;
            std::getline(file, first_multiple_input_temp);

            vector<string> first_multiple_input = split(rtrim(first_multiple_input_temp));

            int n = stoi(first_multiple_input[0]);

            int m = stoi(first_multiple_input[1]);
            //cout << "Input: n:" << n << ", m: " << m << endl;
            int result = legoBlocks(n, m);
            cout << "Result is: " << result << endl;
        }
    }
    file.close();
    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(
        s.begin(),
        find_if(s.begin(), s.end(), [](int c) {return !std::isspace(c);})
    );

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
        find_if(s.rbegin(), s.rend(), [](int c) {return !std::isspace(c);}).base(),
        s.end()
    );

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}