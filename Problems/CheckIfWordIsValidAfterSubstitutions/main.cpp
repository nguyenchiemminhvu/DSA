/**
https://leetcode.com/problems/check-if-word-is-valid-after-substitutions/description/

Given a string s, determine if it is valid.

A string s is valid if, starting with an empty string t = "", you can transform t into s after performing the following operation any number of times:

Insert string "abc" into any position in t. More formally, t becomes tleft + "abc" + tright, where t == tleft + tright. Note that tleft and tright may be empty.
Return true if s is a valid string, otherwise, return false.

Example 1:

Input: s = "aabcbc"
Output: true
Explanation:
"" -> "abc" -> "aabcbc"
Thus, "aabcbc" is valid.

Example 2:

Input: s = "abcabcababcc"
Output: true
Explanation:
"" -> "abc" -> "abcabc" -> "abcabcabc" -> "abcabcababcc"
Thus, "abcabcababcc" is valid.

Example 3:

Input: s = "abccba"
Output: false
Explanation: It is impossible to get "abccba" using the operation.

Constraints:

1 <= s.length <= 2 * 104
s consists of letters 'a', 'b', and 'c'
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    bool isValid(const string& s)
    {
        std::stack<char> st;
        for (char c : s)
        {
            st.push(c);
            if (c == 'c')
            {
                if (st.size() < 3)
                {
                    return false;
                }

                char third = st.top(); st.pop();
                char second = st.top(); st.pop();
                char first = st.top(); st.pop();

                if (first != 'a' || second != 'b' || third != 'c')
                {
                    return false;
                }
            }
        }

        return st.empty();
    }
};

int main()
{
    Solution sol;
    std::cout << sol.isValid("aabcbc") << std::endl;
    return 0;
}