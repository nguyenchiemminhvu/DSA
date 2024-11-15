/**
https://leetcode.com/problems/count-the-number-of-special-characters-ii/description/

You are given a string word. A letter c is called special if it appears both in lowercase and uppercase in word, and every lowercase occurrence of c appears before the first uppercase occurrence of c.

Return the number of special letters in word.

Example 1:

Input: word = "aaAbcBC"

Output: 3

Explanation:

The special characters are 'a', 'b', and 'c'.

Example 2:

Input: word = "abc"

Output: 0

Explanation:

There are no special characters in word.

Example 3:

Input: word = "AbBCab"

Output: 0

Explanation:

There are no special characters in word.

Constraints:

1 <= word.length <= 2 * 105
word consists of only lowercase and uppercase English letters.
*/

#include <iostream>
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
    int numberOfSpecialChars(const string& word)
    {
        int res = 0;

        std::unordered_map<char, int> firstUpperIdx;
        std::unordered_map<char, int> lastLowerIdx;
        for (int i = 0; i < word.length(); i++)
        {
            if (std::islower(word[i]))
            {
                lastLowerIdx[word[i]] = i;
            }
            else
            {
                if (firstUpperIdx.find(word[i]) == firstUpperIdx.end())
                {
                    firstUpperIdx[word[i]] = i;
                }
            }
        }

        for (const std::pair<char, int>& p : firstUpperIdx)
        {
            char lower = std::tolower(p.first);
            if (lastLowerIdx.find(lower) != lastLowerIdx.end() && p.second > lastLowerIdx[lower])
            {
                res++;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.numberOfSpecialChars("aaAbcBC") << std::endl;
    return 0;
}