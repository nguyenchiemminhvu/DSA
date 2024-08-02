/**
https://leetcode.com/problems/minimum-swaps-to-group-all-1s-together-ii/

A swap is defined as taking two distinct positions in an array and swapping the values in them.
A circular array is defined as an array where we consider the first element and the last element to be adjacent.
Given a binary circular array nums, return the minimum number of swaps required to group all 1's present in the array together at any location.

Example 1:

Input: nums = [0,1,0,1,1,0,0]
Output: 1
Explanation: Here are a few of the ways to group all the 1's together:
[0,0,1,1,1,0,0] using 1 swap.
[0,1,1,1,0,0,0] using 1 swap.
[1,1,0,0,0,0,1] using 2 swaps (using the circular property of the array).
There is no way to group all 1's together with 0 swaps.
Thus, the minimum number of swaps required is 1.

Example 2:

Input: nums = [0,1,1,1,0,0,1,1,0]
Output: 2
Explanation: Here are a few of the ways to group all the 1's together:
[1,1,1,0,0,0,0,1,1] using 2 swaps (using the circular property of the array).
[1,1,1,1,1,0,0,0,0] using 2 swaps.
There is no way to group all 1's together with 0 or 1 swaps.
Thus, the minimum number of swaps required is 2.

Example 3:

Input: nums = [1,1,0,0,1]
Output: 0
Explanation: All the 1's are already grouped together due to the circular property of the array.
Thus, the minimum number of swaps required is 0.

Constraints:

1 <= nums.length <= 105
nums[i] is either 0 or 1.
*/

#include <iostream>
#include <vector>
#include <climits>
#include <algorithm>
#include <numeric>

class Solution
{
public:
    int minSwaps(std::vector<int>& nums)
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(0);
        std::cout.tie(0);

        int sum = std::accumulate(nums.begin(), nums.end(), 0);
        int n = nums.size();
        
        if (sum == n || sum <= 1)
        {
            return 0;
        }

        nums.insert(nums.end(), nums.begin(), nums.end());
        
        int min_zero = INT_MAX;
        int left = 0;
        int right = 0;
        int cur_sum = 0;
        while (right < 2 * n)
        {
            cur_sum += nums[right];
            if (right - left + 1 == sum)
            {
                min_zero = std::min(min_zero, sum - cur_sum);
                cur_sum -= nums[left];
                left++;
            }
            right++;
        }
        
        return min_zero;
    }
};

int main()
{
    Solution sol;
    std::vector<int> input = {0,1,1,1,0,0,1,1,0};
    std::cout << sol.minSwaps(input) << std::endl;
    return 0;
}