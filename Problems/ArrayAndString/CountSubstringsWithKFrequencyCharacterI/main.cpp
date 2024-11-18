/**
https://leetcode.com/problems/count-substrings-with-k-frequency-characters-i/description/

Given a string s and an integer k, return the total number of substrings of s where at least one character appears at least k times.

Example 1:

Input: s = "abacb", k = 2

Output: 4

Explanation:

The valid substrings are:

"aba" (character 'a' appears 2 times).
"abac" (character 'a' appears 2 times).
"abacb" (character 'a' appears 2 times).
"bacb" (character 'b' appears 2 times).

Example 2:

Input: s = "abcde", k = 1

Output: 15

Explanation:

All substrings are valid because every character appears at least once.

Constraints:

1 <= s.length <= 3000
1 <= k <= s.length
s consists only of lowercase English letters.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int numberOfSubstrings(const string& s, int k)
    {
        int res = 0;

        int left = 0;
        int right = 0;
        std::unordered_map<char, int> freq;
        int count_at_least = 0;
        while (right < s.length())
        {
            freq[s[right]]++;

            if (freq[s[right]] >= k)
            {
                count_at_least++;
            }

            while (left <= right && count_at_least > 0)
            {
                res += s.length() - right;

                int f_before = freq[s[left]];
                freq[s[left]]--;
                if (f_before >= k && freq[s[left]] < k)
                {
                    count_at_least--;
                }
                left++;
            }

            right++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.numberOfSubstrings("abacb", 2) << std::endl;
    return 0;
}