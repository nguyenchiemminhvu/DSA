/**
https://leetcode.com/problems/substring-matching-pattern/

You are given a string s and a pattern string p, where p contains exactly one '*' character.

The '*' in p can be replaced with any sequence of zero or more characters.

Return true if p can be made a substring of s, and false otherwise.

A substring is a contiguous non-empty sequence of characters within a string.

Example 1:

Input: s = "leetcode", p = "ee*e"

Output: true

Explanation:

By replacing the '*' with "tcod", the substring "eetcode" matches the pattern.

Example 2:

Input: s = "car", p = "c*v"

Output: false

Explanation:

There is no substring matching the pattern.

Example 3:

Input: s = "luck", p = "u*"

Output: true

Explanation:

The substrings "u", "uc", and "uck" match the pattern.

Constraints:

1 <= s.length <= 50
1 <= p.length <= 50 
s contains only lowercase English letters.
p contains only lowercase English letters and exactly one '*'
 */

#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    bool hasMatch(const string& s, const string& p)
    {
        int asterisk_idx = p.find("*");
        std::string left = p.substr(0, asterisk_idx);
        std::string right = p.substr(asterisk_idx + 1);

        if (left.empty())
        {
            return s.rfind(right) != std::string::npos;
        }

        if (right.empty())
        {
            return s.find(left) != std::string::npos;
        }

        std::size_t ileft = s.find(left);
        std::size_t iright = s.rfind(right);
        if (ileft == std::string::npos || iright == std::string::npos)
        {
            return false;
        }

        return ileft + left.length() <= iright;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.hasMatch("car", "c*v") << std::endl;
    return 0;
}