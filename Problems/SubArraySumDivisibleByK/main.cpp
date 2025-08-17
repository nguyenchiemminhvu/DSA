/**
https://leetcode.com/problems/subarray-sums-divisible-by-k/description/

Given an integer array nums and an integer k, return the number of non-empty subarrays that have a sum divisible by k.

A subarray is a contiguous part of an array.

Example 1:

Input: nums = [4,5,0,-2,-3,1], k = 5
Output: 7
Explanation: There are 7 subarrays with a sum divisible by k = 5:
[4, 5, 0, -2, -3, 1], [5], [5, 0], [5, 0, -2, -3], [0], [0, -2, -3], [-2, -3]
Example 2:

Input: nums = [5], k = 9
Output: 0

Constraints:

1 <= nums.length <= 3 * 104
-104 <= nums[i] <= 104
2 <= k <= 104
*/

#include <iostream>
#include <vector>
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
    int subarraysDivByK(vector<int>& nums, int k) 
    {
        int count = 0;

        int cur_sum = 0;
        std::unordered_map<int, int> freq;
        freq[0] = 1;
        for (int n : nums)
        {
            cur_sum += n;
            int remain = ((cur_sum % k) + k) % k;
            count += freq[remain];
            freq[remain]++;
        }

        return count;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {4,5,0,-2,-3,1};
    int k = 5;
    std::cout << sol.subarraysDivByK(nums, k) << std::endl;
    return 0;
}