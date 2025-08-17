/**
Given a string s, return the maximum number of occurrences of any substring under the following rules:

The number of unique characters in the substring must be less than or equal to maxLetters.
The substring size must be between minSize and maxSize inclusive.

Example 1:

Input: s = "aababcaab", maxLetters = 2, minSize = 3, maxSize = 4
Output: 2
Explanation: Substring "aab" has 2 occurrences in the original string.
It satisfies the conditions, 2 unique letters and size 3 (between minSize and maxSize).

Example 2:

Input: s = "aaaa", maxLetters = 1, minSize = 3, maxSize = 3
Output: 2
Explanation: Substring "aaa" occur 2 times in the string. It can overlap.

Constraints:

1 <= s.length <= 105
1 <= maxLetters <= 26
1 <= minSize <= maxSize <= min(26, s.length)
s consists of only lowercase English letters.
*/

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    int maxFreq(const std::string& s, int maxLetters, int minSize, int maxSize)
    {
        std::ios_base::sync_with_stdio(false);
        std::cout.tie(nullptr);

        int res = 0;

        std::unordered_map<std::string, int> freq;
        for (int subLen = minSize; subLen <= maxSize; subLen++)
        {
            int left = 0;
            int right = subLen - 1;
            int unique = 0;
            std::unordered_map<char, int> counter;
            for (int i = left; i < right; i++)
            {
                if (counter[s[i]]++ == 0)
                {
                    unique++;
                }
            }

            while (right < s.length())
            {
                if (counter[s[right]]++ == 0)
                {
                    unique++;
                }

                if (unique <= maxLetters)
                {
                    std::string sub(s.begin() + left, s.begin() + right + 1);
                    res = std::max(res, ++freq[sub]);
                }

                if (counter[s[left]]-- == 1)
                {
                    unique--;
                }

                left++;
                right++;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.maxFreq("aababcaab", 2, 3, 4) << std::endl;
    return 0;
}