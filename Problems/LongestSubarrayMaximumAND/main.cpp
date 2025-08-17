/**
https://leetcode.com/problems/longest-subarray-with-maximum-bitwise-and/description/

You are given an integer array nums of size n.

Consider a non-empty subarray from nums that has the maximum possible bitwise AND.

In other words, let k be the maximum value of the bitwise AND of any subarray of nums. Then, only subarrays with a bitwise AND equal to k should be considered.
Return the length of the longest such subarray.

The bitwise AND of an array is the bitwise AND of all the numbers in it.

A subarray is a contiguous sequence of elements within an array.

Example 1:

Input: nums = [1,2,3,3,2,2]
Output: 2
Explanation:
The maximum possible bitwise AND of a subarray is 3.
The longest subarray with that value is [3,3], so we return 2.

Example 2:

Input: nums = [1,2,3,4]
Output: 1
Explanation:
The maximum possible bitwise AND of a subarray is 4.
The longest subarray with that value is [4], so we return 1.

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 106
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static auto _ = [](){
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return nullptr;
}();

class Solution
{
public:
    int longestSubarray(std::vector<int>& nums)
    {
        int maxElement = *std::max_element(nums.begin(), nums.end());
        int maxLength = 0;
        int currentLength = 0;

        for (int num : nums)
        {
            if (num == maxElement)
            {
                currentLength++;
                maxLength = std::max(maxLength, currentLength);
            }
            else
            {
                currentLength = 0;
            }
        }

        return maxLength;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {100, 5, 5};
    std::cout << sol.longestSubarray(nums) << std::endl;
    return 0;
}