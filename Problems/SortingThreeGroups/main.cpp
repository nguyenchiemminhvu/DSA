/**
https://leetcode.com/problems/sorting-three-groups/description/

You are given an integer array nums. Each element in nums is 1, 2 or 3. In each operation, you can remove an element from nums. Return the minimum number of operations to make nums non-decreasing.

Example 1:

Input: nums = [2,1,3,2,1]

Output: 3

Explanation:

One of the optimal solutions is to remove nums[0], nums[2] and nums[3].

Example 2:

Input: nums = [1,3,2,1,3,3]

Output: 2

Explanation:

One of the optimal solutions is to remove nums[1] and nums[2].

Example 3:

Input: nums = [2,2,2,2,3,3]

Output: 0

Explanation:

nums is already non-decreasing.

Constraints:

1 <= nums.length <= 100
1 <= nums[i] <= 3
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
    int minimumOperations(std::vector<int>& nums)
    {
        int n = nums.size();
        if (n == 0) return 0;

        std::vector<int> dp(n, 1);
        for (int i = 1; i < n; ++i)
        {
            for (int j = 0; j < i; ++j)
            {
                if (nums[i] >= nums[j])
                {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }

        int lis_length = *std::max_element(dp.begin(), dp.end());
        return n - lis_length;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {2, 1, 3, 2, 1};
    std::cout << sol.minimumOperations(nums) << std::endl;
    return 0;
}