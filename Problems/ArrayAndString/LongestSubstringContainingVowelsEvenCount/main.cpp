/**
https://leetcode.com/problems/find-the-longest-substring-containing-vowels-in-even-counts/description/

Given the string s, return the size of the longest substring containing each vowel an even number of times. That is, 'a', 'e', 'i', 'o', and 'u' must appear an even number of times.

Example 1:

Input: s = "eleetminicoworoep"
Output: 13
Explanation: The longest substring is "leetminicowor" which contains two each of the vowels: e, i and o and zero of the vowels: a and u.

Example 2:

Input: s = "leetcodeisgreat"
Output: 5
Explanation: The longest substring is "leetc" which contains two e's.

Example 3:

Input: s = "bcbcbc"
Output: 6
Explanation: In this case, the given string "bcbcbc" is the longest because all vowels: a, e, i, o and u appear zero times.

Constraints:

1 <= s.length <= 5 x 10^5
s contains only lowercase English letters.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

#define MASK_A (0b00001)
#define MASK_E (0b00010)
#define MASK_I (0b00100)
#define MASK_O (0b01000)
#define MASK_U (0b10000)

static const auto kds = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution
{
public:
    int findTheLongestSubstring(const string& s)
    {
        int res = 0;

        std::unordered_map<int, int> maskIndex;
        maskIndex[0] = -1;

        int mask = 0b00000;

        for (int i = 0; i < s.length(); i++)
        {
            if (s[i] == 'a')
            {
                mask ^= MASK_A;
            }
            else if (s[i] == 'e')
            {
                mask ^= MASK_E;
            }
            else if (s[i] == 'i')
            {
                mask ^= MASK_I;
            }
            else if (s[i] == 'o')
            {
                mask ^= MASK_O;
            }
            else if (s[i] == 'u')
            {
                mask ^= MASK_U;
            }

            if (maskIndex.find(mask) != maskIndex.end())
            {
                res = std::max(res, i - maskIndex[mask]);
            }
            else
            {
                maskIndex[mask] = i;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.findTheLongestSubstring("leetcodeisgreat") << std::endl;
    return 0;
}