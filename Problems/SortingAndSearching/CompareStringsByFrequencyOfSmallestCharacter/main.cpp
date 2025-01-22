/**
https://leetcode.com/problems/compare-strings-by-frequency-of-the-smallest-character/description/

Let the function f(s) be the frequency of the lexicographically smallest character in a non-empty string s. For example, if s = "dcce" then f(s) = 2 because the lexicographically smallest character is 'c', which has a frequency of 2.

You are given an array of strings words and another array of query strings queries. For each query queries[i], count the number of words in words such that f(queries[i]) < f(W) for each W in words.

Return an integer array answer, where each answer[i] is the answer to the ith query.

Example 1:

Input: queries = ["cbd"], words = ["zaaaz"]
Output: [1]
Explanation: On the first query we have f("cbd") = 1, f("zaaaz") = 3 so f("cbd") < f("zaaaz").

Example 2:

Input: queries = ["bbb","cc"], words = ["a","aa","aaa","aaaa"]
Output: [1,2]
Explanation: On the first query only f("bbb") < f("aaaa"). On the second query both f("aaa") and f("aaaa") are both > f("cc").

Constraints:

1 <= queries.length <= 2000
1 <= words.length <= 2000
1 <= queries[i].length, words[i].length <= 10
queries[i][j], words[i][j] consist of lowercase English letters.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unrodered_map>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<int> numSmallerByFrequency(vector<string>& queries, vector<string>& words)
    {
        std::vector<int> res;

        std::vector<int> f(words.size(), 0);
        for (int i = 0; i < words.size(); i++)
        {
            f[i] = get_f(words[i]);
        }

        std::sort(f.begin(), f.end());

        for (const std::string& query : queries)
        {
            int fq = get_f(query);
            int count = words.size() - std::distance(f.begin(), std::upper_bound(f.begin(), f.end(), fq));
            res.push_back(count);
        }

        return res;    
    }
private:
    int get_f(const std::string& s)
    {
        std::unordered_map<int, int> freq;
        for (char c : s)
        {
            freq[c]++;
        }

        for (int c = 'a'; c <= 'z'; c++)
        {
            if (freq[c] > 0)
            {
                return freq[c];
            }
        }

        return 0;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> queries = {"cbd"};
    std::vector<std::string> words = {"zaaaz"};
    std::vector<int> res = sol.numSmallerByFrequency(queries, words);
    for (int num : res)
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
    return 0;
}