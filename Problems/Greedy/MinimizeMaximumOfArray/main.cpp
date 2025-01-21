/**
https://leetcode.com/problems/minimize-maximum-of-array/description/

You are given a 0-indexed array nums comprising of n non-negative integers.

In one operation, you must:

Choose an integer i such that 1 <= i < n and nums[i] > 0.
Decrease nums[i] by 1.
Increase nums[i - 1] by 1.
Return the minimum possible value of the maximum integer of nums after performing any number of operations.

Example 1:

Input: nums = [3,7,1,6]
Output: 5
Explanation:
One set of optimal operations is as follows:
1. Choose i = 1, and nums becomes [4,6,1,6].
2. Choose i = 3, and nums becomes [4,6,2,5].
3. Choose i = 1, and nums becomes [5,5,2,5].
The maximum integer of nums is 5. It can be shown that the maximum number cannot be less than 5.
Therefore, we return 5.

Example 2:

Input: nums = [10,1]
Output: 10
Explanation:
It is optimal to leave nums as is, and since 10 is the maximum value, we return 10.

Constraints:

n == nums.length
2 <= n <= 105
0 <= nums[i] <= 109
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int minimizeArrayValue(vector<int>& nums)
    {
        int res = INT_MAX;
        int mi = INT_MAX, ma = INT_MIN;
        for (int val : nums)
        {
            mi = std::min(mi, val);
            ma = std::max(ma, val);
        }

        int left = mi;
        int right = ma;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (testing(nums, mid))
            {
                right = mid - 1;
                res = std::min(res, mid);
            }
            else
            {
                left = mid + 1;
            }
        }

        return res;
    }
private:
    bool testing(const std::vector<int>& nums, int candidate)
    {
        long long carry = 0;
        
        for (int i = nums.size() - 1; i >= 0; --i)
        {
            if (nums[i] + carry > candidate)
            {
                carry += nums[i] - candidate;
            }
            else
            {
                carry = 0;
            }
        }

        return carry == 0;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {3, 7, 1, 6};
    std::cout << sol.minimizeArrayValue(nums) << std::endl;
    return 0;
}