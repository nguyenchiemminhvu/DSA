/**
A string is considered beautiful if it satisfies the following conditions:

Each of the 5 English vowels ('a', 'e', 'i', 'o', 'u') must appear at least once in it.
The letters must be sorted in alphabetical order (i.e. all 'a's before 'e's, all 'e's before 'i's, etc.).
For example, strings "aeiou" and "aaaaaaeiiiioou" are considered beautiful, but "uaeio", "aeoiu", and "aaaeeeooo" are not beautiful.

Given a string word consisting of English vowels, return the length of the longest beautiful substring of word. If no such substring exists, return 0.

A substring is a contiguous sequence of characters in a string.

Example 1:

Input: word = "aeiaaioaaaaeiiiiouuuooaauuaeiu"
Output: 13
Explanation: The longest beautiful substring in word is "aaaaeiiiiouuu" of length 13.

Example 2:

Input: word = "aeeeiiiioooauuuaeiou"
Output: 5
Explanation: The longest beautiful substring in word is "aeiou" of length 5.

Example 3:

Input: word = "a"
Output: 0
Explanation: There is no beautiful substring, so return 0.

Constraints:

1 <= word.length <= 5 * 105
word consists of characters 'a', 'e', 'i', 'o', and 'u'.
*/

#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>

class Solution
{
public:
    int longestBeautifulSubstring(const std::string& word)
    {
        std::ios_base::sync_with_stdio(false);
        std::cout.tie(nullptr);

        int res = 0;

        for (int i = 0; i < word.length(); i++)
        {
            if (word[i] == 'a')
            {
                std::unordered_map<char, bool> checker;
                int j = i + 1;
                while (j < word.length())
                {
                    if (word[j] < word[j - 1])
                    {
                        break;
                    }
                    checker[word[j]] = true;
                    j++;
                }

                if (word[j - 1] == 'u' && checker['e'] && checker['i'] && checker['o'] && checker['u'])
                {
                    res = std::max(res, j - i);
                }

                i = j - 1;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.longestBeautifulSubstring("aeiaaioaaaaeiiiiouuuooaauuaeiu") << std::endl;
    return 0;
}