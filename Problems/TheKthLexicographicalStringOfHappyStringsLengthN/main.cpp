/**
https://leetcode.com/problems/the-k-th-lexicographical-string-of-all-happy-strings-of-length-n/

A happy string is a string that:

consists only of letters of the set ['a', 'b', 'c'].
s[i] != s[i + 1] for all values of i from 1 to s.length - 1 (string is 1-indexed).
For example, strings "abc", "ac", "b" and "abcbabcbcb" are all happy strings and strings "aa", "baa" and "ababbc" are not happy strings.

Given two integers n and k, consider a list of all happy strings of length n sorted in lexicographical order.

Return the kth string of this list or return an empty string if there are less than k happy strings of length n.

Example 1:

Input: n = 1, k = 3
Output: "c"
Explanation: The list ["a", "b", "c"] contains all happy strings of length 1. The third string is "c".

Example 2:

Input: n = 1, k = 4
Output: ""
Explanation: There are only 3 happy strings of length 1.

Example 3:

Input: n = 3, k = 9
Output: "cab"
Explanation: There are 12 different happy string of length 3 ["aba", "abc", "aca", "acb", "bab", "bac", "bca", "bcb", "cab", "cac", "cba", "cbc"]. You will find the 9th string = "cab"

Constraints:

1 <= n <= 10
1 <= k <= 100
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    string getHappyString(int n, int k)
    {
        std::vector<std::string> happy_strings;
        std::string temp;
        generating(n, 0, temp, happy_strings);

        if (happy_strings.size() >= k)
        {
            return happy_strings[k - 1];
        }

        return "";
    }
private:
    void generating(int n, int i, std::string temp, std::vector<std::string>& strs)
    {
        if (i == n)
        {
            strs.push_back(temp);
            return;
        }

        for (char c = 'a'; c <= 'c'; c++)
        {
            if (temp.empty() || c != temp.back())
            {
                temp.push_back(c);
                generating(n, i + 1, temp, strs);
                temp.pop_back();
            }
            else
            {
                continue;
            }
        }
    }
};

int main()
{
    Solution sol;
    std::cout << sol.getHappyString(1, 3) << std::endl;
    return 0;
}