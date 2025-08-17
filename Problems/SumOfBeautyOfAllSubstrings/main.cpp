/**
https://leetcode.com/problems/sum-of-beauty-of-all-substrings/

The beauty of a string is the difference in frequencies between the most frequent and least frequent characters.

For example, the beauty of "abaacc" is 3 - 1 = 2.
Given a string s, return the sum of beauty of all of its substrings.

Example 1:

Input: s = "aabcb"
Output: 5
Explanation: The substrings with non-zero beauty are ["aab","aabc","aabcb","abcb","bcb"], each with beauty equal to 1.

Example 2:

Input: s = "aabcbaa"
Output: 17

Constraints:

1 <= s.length <= 500
s consists of only lowercase English letters.
*/

#include <iostream>
#include <array>
#include <vector>
#include <string>
#include <algorithm>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int beautySum(const string& s)
    {
        std::vector<std::array<int, 26>> freq(s.length() + 1);
        freq[1][s[0] - 'a']++;
        for (int i = 1; i < s.length(); i++)
        {
            freq[i + 1] = freq[i];
            freq[i + 1][s[i] - 'a']++;
        }

        int res = 0;
        for (int left = 1; left < freq.size(); left++)
        {
            for (int right = left + 1; right < freq.size(); right++)
            {
                std::array<int, 26> temp;
                int mi = INT_MAX;
                int ma = INT_MIN;
                for (int i = 0; i < 26; i++)
                {
                    temp[i] = freq[right][i] - freq[left - 1][i];
                    if (temp[i] > 0)
                    {
                        mi = std::min(mi, temp[i]);
                        ma = std::max(ma, temp[i]);
                    }
                }

                res += (ma - mi);
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.beautySum("aabcb") << std::endl;
    return 0;
}