/**
https://leetcode.com/problems/check-if-number-is-a-sum-of-powers-of-three/

Given an integer n, return true if it is possible to represent n as the sum of distinct powers of three. Otherwise, return false.

An integer y is a power of three if there exists an integer x such that y == 3x.

Example 1:

Input: n = 12
Output: true
Explanation: 12 = 31 + 32

Example 2:

Input: n = 91
Output: true
Explanation: 91 = 30 + 32 + 34

Example 3:

Input: n = 21
Output: false

Constraints:

1 <= n <= 107
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    bool checkPowersOfThree(int n)
    {
        std::vector<int> nums;
        for (int exp = 0; exp <= 16; exp++)
        {
            nums.push_back((int)pow(3, exp));
        }

        return trying(nums, 0, n);
    }
private:
    bool trying(const std::vector<int>& nums, int idx, int val)
    {
        if (val < 0)
        {
            return false;
        }

        if (idx > nums.size())
        {
            return val == 0;
        }

        return trying(nums, idx + 1, val) || trying(nums, idx + 1, val - nums[idx]);
    }
};

int main()
{
    Solution sol;
    std::cout << sol.checkPowersOfThree(12) << std::endl;
    std::cout << sol.checkPowersOfThree(91) << std::endl;
    std::cout << sol.checkPowersOfThree(21) << std::endl;
    return 0;
}