/**
Given a string s and an integer k, return true if you can use all the characters in s to construct k palindrome strings or false otherwise.

Example 1:

Input: s = "annabelle", k = 2
Output: true
Explanation: You can construct two palindromes using all characters in s.
Some possible constructions "anna" + "elble", "anbna" + "elle", "anellena" + "b"

Example 2:

Input: s = "leetcode", k = 3
Output: false
Explanation: It is impossible to construct 3 palindromes using all the characters of s.

Example 3:

Input: s = "true", k = 4
Output: true
Explanation: The only possible solution is to put each character in a separate string.

Constraints:

1 <= s.length <= 105
s consists of lowercase English letters.
1 <= k <= 105
 */

#include <iostream>
#include <vector>
#include <string>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    bool canConstruct(const string& s, int k)
    {
        if (s.length() < k)
        {
            return false;
        }

        int freq[26] = {0, };
        for (char c : s)
        {
            freq[c - 'a']++;
        }

        // std::sort(freq, freq + 26, std::greater<int>());

        int count_odd = 0;
        for (int i = 0; i < 26; i++)
        {
            count_odd += (freq[i] & 1);
        }

        if (count_odd > k)
        {
            return false;
        }

        return true;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.canConstruct("annabelle", 2) << std::endl;
    return 0;
}