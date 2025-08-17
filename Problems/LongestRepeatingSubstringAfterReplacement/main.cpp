/**
https://leetcode.com/problems/longest-repeating-character-replacement/

You are given a string s and an integer k. You can choose any character of the string and change it to any other uppercase English character. You can perform this operation at most k times.

Return the length of the longest substring containing the same letter you can get after performing the above operations.

Example 1:

Input: s = "ABAB", k = 2
Output: 4
Explanation: Replace the two 'A's with two 'B's or vice versa.
Example 2:

Input: s = "AABABBA", k = 1
Output: 4
Explanation: Replace the one 'A' in the middle with 'B' and form "AABBBBA".
The substring "BBBB" has the longest repeating letters, which is 4.
There may exists other ways to achieve this answer too.

Constraints:

1 <= s.length <= 105
s consists of only uppercase English letters.
0 <= k <= s.length
*/

#include <iostream>
#include <algorithm>
#include <string>
#include <unordered_map>

class Solution
{
public:
    int characterReplacement(const std::string& s, int k)
    {
        int res = 0;

        int n = s.length();
        int left = 0;
        int right = 0;
        std::unordered_map<char, int> freq;
        int maxCount = 0;
        while (right < n)
        {
            freq[s[right]]++;
            if (maxCount < freq[s[right]])
            {
                maxCount = freq[s[right]];
            }

            if (right - left + 1 > maxCount + k)
            {
                freq[s[left]]--;
                left++;
            }

            res = std::max(res, right - left + 1);
            right++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.characterReplacement("AABABBA", 1) << std::endl;
    return 0;
}