/**
https://leetcode.com/problems/longest-happy-string

A string s is called happy if it satisfies the following conditions:

s only contains the letters 'a', 'b', and 'c'.
s does not contain any of "aaa", "bbb", or "ccc" as a substring.
s contains at most a occurrences of the letter 'a'.
s contains at most b occurrences of the letter 'b'.
s contains at most c occurrences of the letter 'c'.
Given three integers a, b, and c, return the longest possible happy string. If there are multiple longest happy strings, return any of them. If there is no such string, return the empty string "".

A substring is a contiguous sequence of characters within a string.

Example 1:

Input: a = 1, b = 1, c = 7
Output: "ccaccbcc"
Explanation: "ccbccacc" would also be a correct answer.

Example 2:

Input: a = 7, b = 1, c = 0
Output: "aabaa"
Explanation: It is the only correct answer in this case.

Constraints:

0 <= a, b, c <= 100
a + b + c > 0
 */

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    string longestDiverseString(int a, int b, int c)
    {
        std::string res;

        std::vector<std::pair<int, char>> buff;
        buff.push_back({a, 'a'});
        buff.push_back({b, 'b'});
        buff.push_back({c, 'c'});

        while (true)
        {
            bool added = false;

            std::sort(buff.begin(), buff.end(), std::greater<std::pair<int, char>>());

            for (int i = 0; i < 3; i++)
            {
                if (buff[i].first <= 0)
                {
                    continue;
                }

                int len = res.length();
                if (len >= 2 && res[len - 1] == buff[i].second && res[len - 2] == buff[i].second)
                {
                    continue;
                }

                res.push_back(buff[i].second);
                buff[i].first--;
                added = true;
                break;
            }

            if (!added)
            {
                break;
            }
        }

        return res;    
    }
};

int main()
{
    Solution sol;
    std::cout << sol.longestDiverseString(7, 1, 1) << std::endl;
    return 0;
}