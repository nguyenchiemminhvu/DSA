/**
https://leetcode.com/problems/count-the-number-of-fair-pairs

Given a 0-indexed integer array nums of size n and two integers lower and upper, return the number of fair pairs.

A pair (i, j) is fair if:

0 <= i < j < n, and
lower <= nums[i] + nums[j] <= upper
 

Example 1:

Input: nums = [0,1,7,4,4,5], lower = 3, upper = 6
Output: 6
Explanation: There are 6 fair pairs: (0,3), (0,4), (0,5), (1,3), (1,4), and (1,5).

Example 2:

Input: nums = [1,7,9,2,5], lower = 11, upper = 11
Output: 1
Explanation: There is a single fair pair: (2,3).

Constraints:

1 <= nums.length <= 105
nums.length == n
-109 <= nums[i] <= 109
-109 <= lower <= upper <= 109
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
    long long countFairPairs(std::vector<int>& nums, int lower, int upper)
    {
        long long res = 0LL;

        std::sort(nums.begin(), nums.end());
        for (int i = 0; i < nums.size(); i++)
        {
            auto left = std::lower_bound(nums.begin() + i + 1, nums.end(), lower - nums[i]);
            auto right = std::upper_bound(nums.begin() + i + 1, nums.end(), upper - nums[i]);
            res += std::distance(left, right);
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {0,1,7,4,4,5};
    std::cout << sol.countFairPairs(nums, 3, 6) << std::endl;
    return 0;
}