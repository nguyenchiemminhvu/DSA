/**
https://leetcode.com/problems/minimum-additions-to-make-valid-string/description/

Given a string word to which you can insert letters "a", "b" or "c" anywhere and any number of times, return the minimum number of letters that must be inserted so that word becomes valid.

A string is called valid if it can be formed by concatenating the string "abc" several times.

Example 1:

Input: word = "b"
Output: 2
Explanation: Insert the letter "a" right before "b", and the letter "c" right next to "b" to obtain the valid string "abc".

Example 2:

Input: word = "aaa"
Output: 6
Explanation: Insert letters "b" and "c" next to each "a" to obtain the valid string "abcabcabc".

Example 3:

Input: word = "abc"
Output: 0
Explanation: word is already valid. No modifications are needed. 

Constraints:

1 <= word.length <= 50
word consists of letters "a", "b" and "c" only. 
 */

#include <iostream>
#include <string>

using namespace std;

class Solution
{
public:
    int addMinimum(const string& s)
    {
        int res = 0;
        std::string basic = "abc";
        int ib = 0;
        for (char c : s)
        {
            while (c != basic[ib])
            {
                ib = ((ib + 1) % 3);
                res++;
            }
            ib = ((ib + 1) % 3);
        }

        res += 'c' - s.back();

        return res;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.addMinimum("b") << std::endl;
    return 0;
}