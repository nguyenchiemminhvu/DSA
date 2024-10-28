/**
https://leetcode.com/problems/longest-square-streak-in-an-array

You are given an integer array nums. A subsequence of nums is called a square streak if:

The length of the subsequence is at least 2, and
after sorting the subsequence, each element (except the first element) is the square of the previous number.
Return the length of the longest square streak in nums, or return -1 if there is no square streak.

A subsequence is an array that can be derived from another array by deleting some or no elements without changing the order of the remaining elements.

Example 1:

Input: nums = [4,3,6,16,8,2]
Output: 3
Explanation: Choose the subsequence [4,16,2]. After sorting it, it becomes [2,4,16].
- 4 = 2 * 2.
- 16 = 4 * 4.
Therefore, [4,16,2] is a square streak.
It can be shown that every subsequence of length 4 is not a square streak.

Example 2:

Input: nums = [2,3,5,6,7]
Output: -1
Explanation: There is no square streak in nums so return -1.
 

Constraints:

2 <= nums.length <= 105
2 <= nums[i] <= 105
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int longestSquareStreak(vector<int>& nums)
    {
        int res = -1;
        std::sort(nums.begin(), nums.end());

        for (int i = 0; i < nums.size(); i++)
        {
            int cur_idx = i;
            int count = 1;
            while (cur_idx < nums.size())
            {
                if (((long long)nums[cur_idx] * nums[cur_idx]) > 1000000LL)
                {
                    break;
                }

                int s_idx = binarySearch(nums, nums[cur_idx] * nums[cur_idx]);
                if (s_idx != -1)
                {
                    count++;
                    cur_idx = s_idx;
                }
                else
                {
                    break;
                }
            }

            if (count > 1)
            {
                res = std::max(res, count);
            }
        }

        return res;
    }
private:
    int binarySearch(const std::vector<int>& arr, int val)
    {
        auto found = std::lower_bound(arr.begin(), arr.end(), val);
        if (found != arr.end() && *found == val)
        {
            return std::distance(arr.begin(), found);
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {4,3,6,16,8,2};
    std::cout << sol.longestSquareStreak(nums) << std::endl;
    return 0;
}