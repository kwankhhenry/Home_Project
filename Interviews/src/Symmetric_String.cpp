#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

/* Question: A string of even number of characters ("<" and/or ">") is called symmetric.
Given a string S made of N characters ("<",">", and/or "?"), returns the length of the longest symmetric substring
that can be obtained after replacing question marks with "<" or ">" characters.

E.g. "<><??>>", should return 4.
E.g. "??????", should return 6.
E.g. "<<?", should return 2.
*/

int calculate(vector<string> &S)
{
    int length = S.size();
    int left = 0, right = 0;
    int maxCount = 0;

    for(size_t i = 0; i < S.size(); i++)
    {
        left = i;
        right = i + 1;

        while (left >= 0 && right < length && S[left] == "<" && S[right] == ">")
        {
            //cout << "B: Left is: " << left << ", right is: " << right  << endl;
            //cout << "B MaxCount is: " << maxCount << ", calculated: " << right - left + 1 << endl;
            if(right - left + 1 > maxCount)
                maxCount = right - left + 1;
            left -= 1;
            right += 1;
            //cout << "B: Left After is: " << left << ", right After is: " << right  << endl;
        }

        // "?" Cases
        if(right < length && S[right] == "?")
        {
            // Assume we fill in "<"
            S[right] = "<";
            
        }
    }
    return maxCount;
}

int main()
{
    ifstream file("input/Symmetric_String.txt");
    if(file.is_open())
    {
        string str;
        vector<string> vec;
        while(getline(file,str))
        {
            // For each line
            string c;
            stringstream ss(str);
            //cout << "line is: " << str << endl;
            while(getline(ss,c,','))
            {
                vec.push_back(c);
            }

            // Calculate for result
            int result = calculate(vec);
            vec.clear();
            cout << str << ": " << result << endl;
        }
    }
    file.close();
    return 0;
}