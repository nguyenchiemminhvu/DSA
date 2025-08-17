/**
https://leetcode.com/problems/short-encoding-of-words/description/

A valid encoding of an array of words is any reference string s and array of indices indices such that:

words.length == indices.length
The reference string s ends with the '#' character.
For each index indices[i], the substring of s starting from indices[i] and up to (but not including) the next '#' character is equal to words[i].
Given an array of words, return the length of the shortest reference string s possible of any valid encoding of words.

Example 1:

Input: words = ["time", "me", "bell"]
Output: 10
Explanation: A valid encoding would be s = "time#bell#" and indices = [0, 2, 5].
words[0] = "time", the substring of s starting from indices[0] = 0 to the next '#' is underlined in "time#bell#"
words[1] = "me", the substring of s starting from indices[1] = 2 to the next '#' is underlined in "time#bell#"
words[2] = "bell", the substring of s starting from indices[2] = 5 to the next '#' is underlined in "time#bell#"

Example 2:

Input: words = ["t"]
Output: 2
Explanation: A valid encoding would be s = "t#" and indices = [0].

Constraints:

1 <= words.length <= 2000
1 <= words[i].length <= 7
words[i] consists of only lowercase letters.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class TrieNode
{
public:
    std::unordered_map<char, TrieNode*> children;
};

class Trie
{
public:
    TrieNode* root;
    std::unordered_map<TrieNode*, int> freq;

    Trie()
    {
        root = new TrieNode();
        freq.clear();
    }

    void insert(const std::string& word)
    {
        TrieNode* curr = root;
        for (char c : word)
        {
            if (curr->children.find(c) == curr->children.end())
            {
                curr->children[c] = new TrieNode();
            }
            curr = curr->children[c];
        }
        
        if (curr->children.size() == 0)
        {
            freq[curr] = word.length();
        }
    }
};

class Solution
{
public:
    int minimumLengthEncoding(vector<string>& words)
    {
        std::sort(words.begin(), words.end(), [](const std::string& a, const std::string& b) {
            return a.length() > b.length();
        });

        Trie t;
        for (const std::string& s : words)
        {
            t.insert(std::string(s.rbegin(), s.rend()));
        }

        int res = 0;
        for (const auto& p : t.freq)
        {
            res += p.second + 1;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> words = {
        "time", "me", "bell"
    };
    std::cout << sol.minimumLengthEncoding(words) << std::endl;
    return 0;
}