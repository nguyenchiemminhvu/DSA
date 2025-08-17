/**
https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/description/

You are given two strings s1 and s2, both of length n, consisting of lowercase English letters.

You can apply the following operation on any of the two strings any number of times:

Choose any two indices i and j such that i < j and the difference j - i is even, then swap the two characters at those indices in the string.
Return true if you can make the strings s1 and s2 equal, and false otherwise.

Example 1:

Input: s1 = "abcdba", s2 = "cabdab"
Output: true
Explanation: We can apply the following operations on s1:
- Choose the indices i = 0, j = 2. The resulting string is s1 = "cbadba".
- Choose the indices i = 2, j = 4. The resulting string is s1 = "cbbdaa".
- Choose the indices i = 1, j = 5. The resulting string is s1 = "cabdab" = s2.

Example 2:

Input: s1 = "abe", s2 = "bea"
Output: false
Explanation: It is not possible to make the two strings equal.
 

Constraints:

n == s1.length == s2.length
1 <= n <= 105
s1 and s2 consist only of lowercase English letters.
*/

#include <iostream>
#include <vector>
#include <array>
#include <string>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    bool checkStrings(const string& s1, const string& s2)
    {
        std::array<int, 26> freq11 = { 0, };
        std::array<int, 26> freq12 = { 0, };
        for (int i = 0; i < s1.length(); i += 2)
        {
            freq11[s1[i] - 'a']++;
        }
        for (int i = 1; i < s1.length(); i += 2)
        {
            freq12[s1[i] - 'a']++;
        }

        std::array<int, 26> freq21 = { 0, };
        std::array<int, 26> freq22 = { 0, };
        for (int i = 0; i < s2.length(); i += 2)
        {
            freq21[s2[i] - 'a']++;
        }
        for (int i = 1; i < s2.length(); i += 2)
        {
            freq22[s2[i] - 'a']++;
        }

        return freq11 == freq21 && freq12 == freq22;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.checkStrings("abcdba", "cabdab") << std::endl;
    return 0;
}