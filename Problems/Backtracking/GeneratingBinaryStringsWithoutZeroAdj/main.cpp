/**
https://leetcode.com/problems/generate-binary-strings-without-adjacent-zeros/

You are given a positive integer n.

A binary string x is valid if all 
substrings
 of x of length 2 contain at least one "1".

Return all valid strings with length n, in any order.

Example 1:

Input: n = 3

Output: ["010","011","101","110","111"]

Explanation:

The valid strings of length 3 are: "010", "011", "101", "110", and "111".

Example 2:

Input: n = 1

Output: ["0","1"]

Explanation:

The valid strings of length 1 are: "0" and "1".

Constraints:

1 <= n <= 18
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Solution
{
public:
    vector<string> validStrings(int n)
    {
        std::vector<std::string> res;
        std::string temp;
        generating(n, temp, res);
        return res;    
    }
private:
    void generating(int n, std::string temp, std::vector<std::string>& res)
    {
        if (temp.length() == n)
        {
            res.push_back(temp);
            return;
        }

        if (!temp.empty() && temp.back() == '0')
        {
            temp.push_back('1');
            generating(n, temp, res);
            temp.pop_back();
        }
        else
        {
            for (char c = '0'; c <= '1'; c++)
            {
                temp.push_back(c);
                generating(n, temp, res);
                temp.pop_back();
            }
        }
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> res = sol.validStrings(3);
    for (const std::string& s : res)
    {
        std::cout << s << std::endl;
    }
    return 0;
}