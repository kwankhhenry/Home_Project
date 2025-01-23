#include <iostream>

// A transformation sequence from word beginWord to word endWord using a dictionary wordList is a sequence of words such that:
/*- The first word in the sequence is beginWord
- The last word in the sequence is endWord
- Only one letter is different between each adjacent pair of words in the sequence
Given two words, beginWord and endWord and a dictionary wordList, return the number of words in the shortest transformation sequence
from beginWord to endWord, or -1 if no such  sequence exists.
Example
beginWord="hit" endWord="cog" wordList=["hot", "dot", "dog", "lot", "log", "cog"]
Output = 5
beginWord="hit" endWord="cog" wordList=["hot", "dot", "dog", "lot", "log", "cog"]
Output = 5
Sequence is hit->hot->dot->dog->Cog
beginWord="hit" endWord="cog" wordList=["hot", "hat',"hut", "dot", "dog", "lot", "log", "cog"]
*/

#include <string>
#include <algorithm>
#include <vector>

#include <iostream>
#include <string>
#include <vector>
#include <unordered_set>
#include <queue>

int ladderLength(const std::string& beginWord, const std::string& endWord, const std::vector<std::string>& wordList) {
    std::unordered_set<std::string> wordSet(wordList.begin(), wordList.end());
    if (wordSet.find(endWord) == wordSet.end()) {
        return 0;
    }

    std::queue<std::pair<std::string, int>> toVisit;
    toVisit.push({beginWord, 1});

    while (!toVisit.empty()) {
        auto [currentWord, level] = toVisit.front();
        toVisit.pop();

        for (int i = 0; i < currentWord.size(); ++i) {
            std::string tempWord = currentWord;
            for (char c = 'a'; c <= 'z'; ++c) {
                tempWord[i] = c;
                if (tempWord == endWord) {
                    return level + 1;
                }
                if (wordSet.find(tempWord) != wordSet.end()) {
                    toVisit.push({tempWord, level + 1});
                    wordSet.erase(tempWord);
                }
            }
        }
    }
    return 0;
}

int main() {
    std::string beginWord = "hit";
    std::string endWord = "cog";
    std::vector<std::string> wordList = {"hot", "dot", "dog", "lot", "log", "cog"};

    int result = ladderLength(beginWord, endWord, wordList);
    std::cout << "Length of shortest transformation sequence: " << result << std::endl;

    return 0;
}

