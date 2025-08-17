/**
https://leetcode.com/problems/sum-of-prefix-scores-of-strings/

You are given an array words of size n consisting of non-empty strings.

We define the score of a string word as the number of strings words[i] such that word is a prefix of words[i].

For example, if words = ["a", "ab", "abc", "cab"], then the score of "ab" is 2, since "ab" is a prefix of both "ab" and "abc".
Return an array answer of size n where answer[i] is the sum of scores of every non-empty prefix of words[i].

Note that a string is considered as a prefix of itself.

Example 1:

Input: words = ["abc","ab","bc","b"]
Output: [5,4,3,2]
Explanation: The answer for each string is the following:
- "abc" has 3 prefixes: "a", "ab", and "abc".
- There are 2 strings with the prefix "a", 2 strings with the prefix "ab", and 1 string with the prefix "abc".
The total is answer[0] = 2 + 2 + 1 = 5.
- "ab" has 2 prefixes: "a" and "ab".
- There are 2 strings with the prefix "a", and 2 strings with the prefix "ab".
The total is answer[1] = 2 + 2 = 4.
- "bc" has 2 prefixes: "b" and "bc".
- There are 2 strings with the prefix "b", and 1 string with the prefix "bc".
The total is answer[2] = 2 + 1 = 3.
- "b" has 1 prefix: "b".
- There are 2 strings with the prefix "b".
The total is answer[3] = 2.

Example 2:

Input: words = ["abcd"]
Output: [4]
Explanation:
"abcd" has 4 prefixes: "a", "ab", "abc", and "abcd".
Each prefix has a score of one, so the total is answer[0] = 1 + 1 + 1 + 1 = 4.

Constraints:

1 <= words.length <= 1000
1 <= words[i].length <= 1000
words[i] consists of lowercase English letters.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

static const int FastIO = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class TrieNode
{
public:
    unordered_map<char, TrieNode*> children;
    int count = 0;
};

class Trie
{
public:
    TrieNode* root;
    
    Trie()
    {
        root = new TrieNode();
    }

    void insert(const string& word)
    {
        TrieNode* node = root;
        for (char ch : word)
        {
            if (!node->children.count(ch))
            {
                node->children[ch] = new TrieNode();
            }
            node = node->children[ch];
            node->count++;
        }
    }

    int sumPrefixes(const string& word)
    {
        TrieNode* node = root;
        int score = 0;
        for (char ch : word)
        {
            node = node->children[ch];
            score += node->count;
        }
        return score;
    }
};

class Solution
{
public:
    vector<int> sumPrefixScores(vector<string>& words)
    {
        Trie trie;

        for (const std::string& word : words)
        {
            trie.insert(word);
        }

        std::vector<int> res;
        for (const std::string& word : words)
        {
            res.push_back(trie.sumPrefixes(word));
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> words = {
        "abc","ab","bc","b"
    };
    std::vector<int> res = sol.sumPrefixScores(words);

    for (int n : res)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}