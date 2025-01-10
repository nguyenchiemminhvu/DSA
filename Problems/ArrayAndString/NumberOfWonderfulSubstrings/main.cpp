/**
https://leetcode.com/problems/number-of-wonderful-substrings/description/

A wonderful string is a string where at most one letter appears an odd number of times.

For example, "ccjjc" and "abab" are wonderful, but "ab" is not.
Given a string word that consists of the first ten lowercase English letters ('a' through 'j'), return the number of wonderful non-empty substrings in word. If the same substring appears multiple times in word, then count each occurrence separately.

A substring is a contiguous sequence of characters in a string.

Example 1:

Input: word = "aba"
Output: 4
Explanation: The four wonderful substrings are underlined below:
- "aba" -> "a"
- "aba" -> "b"
- "aba" -> "a"
- "aba" -> "aba"

Example 2:

Input: word = "aabb"
Output: 9
Explanation: The nine wonderful substrings are underlined below:
- "aabb" -> "a"
- "aabb" -> "aa"
- "aabb" -> "aab"
- "aabb" -> "aabb"
- "aabb" -> "a"
- "aabb" -> "abb"
- "aabb" -> "b"
- "aabb" -> "bb"
- "aabb" -> "b"

Example 3:

Input: word = "he"
Output: 2
Explanation: The two wonderful substrings are underlined below:
- "he" -> "h"
- "he" -> "e"

Constraints:

1 <= word.length <= 105
word consists of lowercase English letters from 'a' to 'j'.
 */

#include <iostream>
#include <vector>
#include <string>
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
    long long wonderfulSubstrings(const string& word)
    {
        long long res = 0LL;
        std::unordered_map<int, int> freq;
        freq[0] = 1;
        int mask = 0;
        for (char c : word)
        {
            mask ^= (1 << (c - 'a'));

            res += freq[mask];

            for (int i = 0; i < 10; i++)
            {
                int temp_mask = mask ^ (1 << i);
                if (freq.find(temp_mask) != freq.end())
                {
                    res += freq[temp_mask];
                }
            }

            freq[mask]++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.wonderfulSubstrings("aba") << std::endl;
    return 0;
}