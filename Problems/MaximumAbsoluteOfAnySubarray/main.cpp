/**
https://leetcode.com/problems/maximum-absolute-sum-of-any-subarray/description/

You are given an integer array nums. The absolute sum of a subarray [numsl, numsl+1, ..., numsr-1, numsr] is abs(numsl + numsl+1 + ... + numsr-1 + numsr).

Return the maximum absolute sum of any (possibly empty) subarray of nums.

Note that abs(x) is defined as follows:

If x is a negative integer, then abs(x) = -x.
If x is a non-negative integer, then abs(x) = x.

Example 1:

Input: nums = [1,-3,2,3,-4]
Output: 5
Explanation: The subarray [2,3] has absolute sum = abs(2+3) = abs(5) = 5.

Example 2:

Input: nums = [2,-5,1,-4,3,-2]
Output: 8
Explanation: The subarray [-5,1,-4] has absolute sum = abs(-5+1-4) = abs(-8) = 8.

Constraints:

1 <= nums.length <= 105
-104 <= nums[i] <= 104
 */

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return 0;
}();

class Solution
{
public:
    int maxAbsoluteSum(vector<int>& nums)
    {
        return std::max(std::abs(kadane(nums)), std::abs(reverse_kadane(nums)));
    }
private:
    int kadane(const std::vector<int>& nums)
    {
        int max_all = 0;
        int max_cur = 0;
        for (int n : nums)
        {
            max_cur = std::max(n, max_cur + n);
            max_all = std::max(max_all, max_cur);
        }

        return max_all;
    }

    int reverse_kadane(const std::vector<int>& nums)
    {
        int min_all = 0;
        int min_cur = 0;
        for (int n : nums)
        {
            min_cur = std::min(n, min_cur + n);
            min_all = std::min(min_all, min_cur);
        }

        return min_all;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1, -3, 2, 3, -4};
    std::cout << sol.maxAbsoluteSum(nums) << std::endl;
    return 0;
}