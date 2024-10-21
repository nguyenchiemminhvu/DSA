/**
https://leetcode.com/problems/split-a-string-into-the-max-number-of-unique-substrings

Given a string s, return the maximum number of unique substrings that the given string can be split into.

You can split string s into any list of non-empty substrings, where the concatenation of the substrings forms the original string. However, you must split the substrings such that all of them are unique.

A substring is a contiguous sequence of characters within a string.

Example 1:

Input: s = "ababccc"
Output: 5
Explanation: One way to split maximally is ['a', 'b', 'ab', 'c', 'cc']. Splitting like ['a', 'b', 'a', 'b', 'c', 'cc'] is not valid as you have 'a' and 'b' multiple times.

Example 2:

Input: s = "aba"
Output: 2
Explanation: One way to split maximally is ['a', 'ba'].

Example 3:

Input: s = "aa"
Output: 1
Explanation: It is impossible to split the string any further.

Constraints:

1 <= s.length <= 16

s contains only lower case English letters.
*/

#include <iostream>
#include <string>
#include <unordered_set>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int maxUniqueSplit(const string& s)
    {
        int res = 0;
        std::unordered_set<std::string> ss;
        backtracking(s, 0, ss, res);
        return res;
    }
private:
    void backtracking(const std::string& s, int left, std::unordered_set<std::string>& ss, int& res)
    {
        if (left >= s.length())
        {
            res = std::max(res, (int)ss.size());
            return;
        }

        for (int right = left; right < s.length(); right++)
        {
            std::string sub(s.begin() + left, s.begin() + right + 1);
            if (ss.find(sub) == ss.end())
            {
                ss.insert(sub);
                backtracking(s, right + 1, ss, res);
                ss.erase(sub);
            }
        }
    }
};

int main()
{
    Solution sol;
    std::cout << sol.maxUniqueSplit("ababccc") << std::endl;
    return 0;
}