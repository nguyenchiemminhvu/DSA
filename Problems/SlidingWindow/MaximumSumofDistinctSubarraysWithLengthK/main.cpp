/**
https://leetcode.com/problems/maximum-sum-of-distinct-subarrays-with-length-k/description

You are given an integer array nums and an integer k. Find the maximum subarray sum of all the subarrays of nums that meet the following conditions:

The length of the subarray is k, and
All the elements of the subarray are distinct.
Return the maximum subarray sum of all the subarrays that meet the conditions. If no subarray meets the conditions, return 0.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [1,5,4,2,9,9,9], k = 3
Output: 15
Explanation: The subarrays of nums with length 3 are:
- [1,5,4] which meets the requirements and has a sum of 10.
- [5,4,2] which meets the requirements and has a sum of 11.
- [4,2,9] which meets the requirements and has a sum of 15.
- [2,9,9] which does not meet the requirements because the element 9 is repeated.
- [9,9,9] which does not meet the requirements because the element 9 is repeated.
We return 15 because it is the maximum subarray sum of all the subarrays that meet the conditions

Example 2:

Input: nums = [4,4,4], k = 3
Output: 0
Explanation: The subarrays of nums with length 3 are:
- [4,4,4] which does not meet the requirements because the element 4 is repeated.
We return 0 because no subarrays meet the conditions.

Constraints:

1 <= k <= nums.length <= 105
1 <= nums[i] <= 105
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    long long maximumSubarraySum(std::vector<int>& nums, int k)
    {
        long long res = 0LL;
        long long cur_sum = 0LL;
        int n = nums.size();
        std::unordered_map<int, int> freq;
        int left = 0;

        for (int right = 0; right < n; ++right)
        {
            cur_sum += nums[right];
            freq[nums[right]]++;

            while (right - left + 1 > k)
            {
                cur_sum -= nums[left];
                if (--freq[nums[left]] == 0)
                {
                    freq.erase(nums[left]);
                }
                left++;
            }

            if (right - left + 1 == k && freq.size() == k)
            {
                res = std::max(res, cur_sum);
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1,5,4,2,9,9,9};
    int k = 3;
    std::cout << sol.maximumSubarraySum(nums, k) << std::endl;
    return 0;
}