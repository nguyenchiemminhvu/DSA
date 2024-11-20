/**
https://leetcode.com/problems/take-k-of-each-character-from-left-and-right

You are given a string s consisting of the characters 'a', 'b', and 'c' and a non-negative integer k. Each minute, you may take either the leftmost character of s, or the rightmost character of s.

Return the minimum number of minutes needed for you to take at least k of each character, or return -1 if it is not possible to take k of each character.

Example 1:

Input: s = "aabaaaacaabc", k = 2
Output: 8
Explanation: 
Take three characters from the left of s. You now have two 'a' characters, and one 'b' character.
Take five characters from the right of s. You now have four 'a' characters, two 'b' characters, and two 'c' characters.
A total of 3 + 5 = 8 minutes is needed.
It can be proven that 8 is the minimum number of minutes needed.

Example 2:

Input: s = "a", k = 1
Output: -1
Explanation: It is not possible to take one 'b' or 'c' so return -1.

Constraints:

1 <= s.length <= 105
s consists of only the letters 'a', 'b', and 'c'.
0 <= k <= s.length
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int takeCharacters(const string& s, int k)
    {
        if (k == 0)
        {
            return 0;
        }

        int n = s.length();
        int total_a = 0;
        int total_b = 0;
        int total_c = 0;
        for (int i = n - 1; i >= 0; i--)
        {
            total_a += (s[i] == 'a');
            total_b += (s[i] == 'b');
            total_c += (s[i] == 'c');
        }

        if (total_a < k || total_b < k || total_c < k)
        {
            return -1;
        }

        int max_window = 0;
        int count_a = 0;
        int count_b = 0;
        int count_c = 0;

        int left = 0;
        int right = 0;
        while (right < n)
        {
            count_a += (s[right] == 'a');
            count_b += (s[right] == 'b');
            count_c += (s[right] == 'c');

            while (count_a > total_a - k || count_b > total_b - k || count_c > total_c - k)
            {
                count_a -= (s[left] == 'a');
                count_b -= (s[left] == 'b');
                count_c -= (s[left] == 'c');
                left++;
            }

            max_window = std::max(max_window, right - left + 1);

            right++;
        }

        return n - max_window;
    }
};

int main()
{
    Solution sol;
    std::cout << sol.takeCharacters("aabaaaacaabc", 2) << std::endl;

    return 0;
}