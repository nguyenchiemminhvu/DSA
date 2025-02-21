/**
https://leetcode.com/problems/longest-palindrome-by-concatenating-two-letter-words/description/

You are given an array of strings words. Each element of words consists of two lowercase English letters.

Create the longest possible palindrome by selecting some elements from words and concatenating them in any order. Each element can be selected at most once.

Return the length of the longest palindrome that you can create. If it is impossible to create any palindrome, return 0.

A palindrome is a string that reads the same forward and backward.

Example 1:

Input: words = ["lc","cl","gg"]
Output: 6
Explanation: One longest palindrome is "lc" + "gg" + "cl" = "lcggcl", of length 6.
Note that "clgglc" is another longest palindrome that can be created.

Example 2:

Input: words = ["ab","ty","yt","lc","cl","ab"]
Output: 8
Explanation: One longest palindrome is "ty" + "lc" + "cl" + "yt" = "tylcclyt", of length 8.
Note that "lcyttycl" is another longest palindrome that can be created.

Example 3:

Input: words = ["cc","ll","xx"]
Output: 2
Explanation: One longest palindrome is "cc", of length 2.
Note that "ll" is another longest palindrome that can be created, and so is "xx".

Constraints:

1 <= words.length <= 105
words[i].length == 2
words[i] consists of lowercase English letters.
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
    int longestPalindrome(vector<string>& words)
    {
        std::unordered_map<std::string, int> freq;
        for (const std::string& word : words)
        {
            freq[word]++;
        }

        int res = 0;
        for (auto& p : freq)
        {
            if (p.second <= 0)
            {
                continue;
            }

            std::string left = p.first;
            std::string right = std::string(p.first.rbegin(), p.first.rend());
            if (left[0] == left[1])
            {
                int times = p.second - (p.second & 1);
                if (times > 1)
                {
                    res += (4 * (times / 2));
                    p.second -= times;
                }
            }
            else if (freq.find(right) != freq.end())
            {
                int times = std::min(p.second, freq[right]);
                res += (4 * times);
                p.second -= times;
                freq[right] -= times;
            }
        }

        for (auto& p : freq)
        {
            if (p.first[0] == p.first[1] && p.second)
            {
                res += 2;
                break;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> words = {"lc", "cl", "gg"};
    std::cout << sol.longestPalindrome(words) << std::endl;
    return 0;
}