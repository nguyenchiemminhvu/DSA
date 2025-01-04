/**
https://leetcode.com/problems/unique-length-3-palindromic-subsequences/description/

Given a string s, return the number of unique palindromes of length three that are a subsequence of s.

Note that even if there are multiple ways to obtain the same subsequence, it is still only counted once.

A palindrome is a string that reads the same forwards and backwards.

A subsequence of a string is a new string generated from the original string with some characters (can be none) deleted without changing the relative order of the remaining characters.

For example, "ace" is a subsequence of "abcde".

Example 1:

Input: s = "aabca"
Output: 3
Explanation: The 3 palindromic subsequences of length 3 are:
- "aba" (subsequence of "aabca")
- "aaa" (subsequence of "aabca")
- "aca" (subsequence of "aabca")

Example 2:

Input: s = "adc"
Output: 0
Explanation: There are no palindromic subsequences of length 3 in "adc".

Example 3:

Input: s = "bbcbaba"
Output: 4
Explanation: The 4 palindromic subsequences of length 3 are:
- "bbb" (subsequence of "bbcbaba")
- "bcb" (subsequence of "bbcbaba")
- "bab" (subsequence of "bbcbaba")
- "aba" (subsequence of "bbcbaba")

Constraints:

3 <= s.length <= 105
s consists of only lowercase English letters.

 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int countPalindromicSubsequence(const std::string& s)
    {
        int res = 0;

        std::vector<std::vector<int>> ch_indices(26);
        for (int i = 0; i < s.length(); i++)
        {
            ch_indices[s[i] - 'a'].push_back(i);
        }

        for (int ch = 0; ch < 26; ch++)
        {
            if (ch_indices[ch].size() < 2) continue;

            int first = ch_indices[ch].front();
            int last = ch_indices[ch].back();

            std::unordered_set<char> middle_chars;
            for (int k = first + 1; k < last; k++)
            {
                middle_chars.insert(s[k]);
            }

            res += middle_chars.size();
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.countPalindromicSubsequence("bbcbaba") << std::endl;
    return 0;
}