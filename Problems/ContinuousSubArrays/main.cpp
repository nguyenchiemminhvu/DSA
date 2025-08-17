/**
https://leetcode.com/problems/continuous-subarrays/description/

You are given a 0-indexed integer array nums. A subarray of nums is called continuous if:

Let i, i + 1, ..., j be the indices in the subarray. Then, for each pair of indices i <= i1, i2 <= j, 0 <= |nums[i1] - nums[i2]| <= 2.
Return the total number of continuous subarrays.

A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [5,4,2,4]
Output: 8
Explanation: 
Continuous subarray of size 1: [5], [4], [2], [4].
Continuous subarray of size 2: [5,4], [4,2], [2,4].
Continuous subarray of size 3: [4,2,4].
Thereare no subarrys of size 4.
Total continuous subarrays = 4 + 3 + 1 = 8.
It can be shown that there are no more continuous subarrays.

Example 2:

Input: nums = [1,2,3]
Output: 6
Explanation: 
Continuous subarray of size 1: [1], [2], [3].
Continuous subarray of size 2: [1,2], [2,3].
Continuous subarray of size 3: [1,2,3].
Total continuous subarrays = 3 + 2 + 1 = 6.

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
 */

#include <iostream>
#include <vector>
#include <deque>
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
    long long continuousSubarrays(vector<int>& nums)
    {
        long long res = 0LL;

        std::deque<int> de_min;
        std::deque<int> de_max;
        int left = 0;
        for (int right = 0; right < nums.size(); right++)
        {
            while (!de_min.empty() && nums[de_min.back()] > nums[right])
            {
                de_min.pop_back();
            }
            de_min.push_back(right);

            while (!de_max.empty() && nums[de_max.back()] < nums[right])
            {
                de_max.pop_back();
            }
            de_max.push_back(right);

            while (nums[de_max.front()] - nums[de_min.front()] > 2)
            {
                if (de_max.front() == left)
                {
                    de_max.pop_front();
                }

                if (de_min.front() == left)
                {
                    de_min.pop_front();
                }
                
                left++;
            }

            res += (right - left + 1);
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1,2,3};
    std::cout << sol.continuousSubarrays(nums) << std::endl;
    return 0;
}