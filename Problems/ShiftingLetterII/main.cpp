/**
https://leetcode.com/problems/shifting-letters-ii/

You are given a string s of lowercase English letters and a 2D integer array shifts where shifts[i] = [starti, endi, directioni]. For every i, shift the characters in s from the index starti to the index endi (inclusive) forward if directioni = 1, or shift the characters backward if directioni = 0.

Shifting a character forward means replacing it with the next letter in the alphabet (wrapping around so that 'z' becomes 'a'). Similarly, shifting a character backward means replacing it with the previous letter in the alphabet (wrapping around so that 'a' becomes 'z').

Return the final string after all such shifts to s are applied.

Example 1:

Input: s = "abc", shifts = [[0,1,0],[1,2,1],[0,2,1]]
Output: "ace"
Explanation: Firstly, shift the characters from index 0 to index 1 backward. Now s = "zac".
Secondly, shift the characters from index 1 to index 2 forward. Now s = "zbd".
Finally, shift the characters from index 0 to index 2 forward. Now s = "ace".

Example 2:

Input: s = "dztz", shifts = [[0,0,0],[1,1,1]]
Output: "catz"
Explanation: Firstly, shift the characters from index 0 to index 0 backward. Now s = "cztz".
Finally, shift the characters from index 1 to index 1 forward. Now s = "catz".

Constraints:

1 <= s.length, shifts.length <= 5 * 104
shifts[i].length == 3
0 <= starti <= endi < s.length
0 <= directioni <= 1
s consists of lowercase English letters.
 */

#include <iostream>
#include <vector>
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
    string shiftingLetters(string& s, vector<vector<int>>& shifts)
    {
        int n = s.length();
        std::vector<int> count(n + 1, 0);

        for (const auto& shift : shifts)
        {
            int delta = (shift[2] == 1) ? 1 : -1;
            count[shift[0]] += delta;
            count[shift[1] + 1] -= delta;
        }

        for (int i = 1; i < n; i++)
        {
            count[i] += count[i - 1];
        }

        for (int i = 0; i < n; i++)
        {
            int shift = count[i] % 26;
            s[i] = 'a' + (((s[i] - 'a') + shift + 26) % 26);
        }

        return s;
    }
};

int main()
{
    Solution sol;
    std::string s = "dztz";
    std::vector<std::vector<int>> shifts = {
        {0,0,0},
        {1,1,1},
    };
    std::cout << sol.shiftingLetters(s, shifts) << std::endl;
    return 0;
}