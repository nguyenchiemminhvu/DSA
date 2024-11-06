/**
https://leetcode.com/problems/number-of-good-ways-to-split-a-string/description/

You are given a string s.

A split is called good if you can split s into two non-empty strings sleft and sright where their concatenation is equal to s (i.e., sleft + sright = s) and the number of distinct letters in sleft and sright is the same.

Return the number of good splits you can make in s.

Example 1:

Input: s = "aacaba"
Output: 2
Explanation: There are 5 ways to split "aacaba" and 2 of them are good. 
("a", "acaba") Left string and right string contains 1 and 3 different letters respectively.
("aa", "caba") Left string and right string contains 1 and 3 different letters respectively.
("aac", "aba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aaca", "ba") Left string and right string contains 2 and 2 different letters respectively (good split).
("aacab", "a") Left string and right string contains 3 and 1 different letters respectively.

Example 2:

Input: s = "abcd"
Output: 1
Explanation: Split the string as follows ("ab", "cd").

Constraints:

1 <= s.length <= 105
s consists of only lowercase English letters.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
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
    int numSplits(const string& s)
    {
        int res = 0;
        std::unordered_map<char, int> freq_left;
        std::unordered_map<char, int> freq_right;

        std::unordered_set<char> s_left;
        std::unordered_set<char> s_right;

        for (char c : s)
        {
            freq_right[c]++;
            s_right.insert(c);
        }

        for (int i = 1; i < s.length(); i++)
        {
            freq_left[s[i - 1]]++;
            s_left.insert(s[i - 1]);

            freq_right[s[i - 1]]--;
            if (freq_right[s[i - 1]] == 0)
            {
                s_right.erase(s[i - 1]);
            }

            res += (s_left.size() == s_right.size());
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.numSplits("aacaba") << std::endl;
    return 0;
}