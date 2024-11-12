/**
https://leetcode.com/problems/simplified-fractions/description/

Given an integer n, return a list of all simplified fractions between 0 and 1 (exclusive) such that the denominator is less-than-or-equal-to n. You can return the answer in any order.

Example 1:

Input: n = 2
Output: ["1/2"]
Explanation: "1/2" is the only unique fraction with a denominator less-than-or-equal-to 2.

Example 2:

Input: n = 3
Output: ["1/2","1/3","2/3"]

Example 3:

Input: n = 4
Output: ["1/2","1/3","1/4","2/3","3/4"]
Explanation: "2/4" is not a simplified fraction because it can be simplified to "1/2".

Constraints:

1 <= n <= 100
*/

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <numeric>
#include <utility>

using namespace std;

class Solution
{
public:
    vector<string> simplifiedFractions(int n)
    {
        std::vector<std::string> res;
        for (int up = 1; up < n; up++)
        {
            for (int down = 2; down <= n; down++)
            {
                int g = std::__gcd(up, down);
                if (up < down && g == 1)
                {
                    std::string temp;
                    temp += std::to_string(up) + "/" + std::to_string(down);
                    res.push_back(temp);
                }
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> res = sol.simplifiedFractions(3);
    for (const std::string& s : res)
    {
        std::cout << s << " ";
    }
    std::cout << std::endl;
    return 0;
}