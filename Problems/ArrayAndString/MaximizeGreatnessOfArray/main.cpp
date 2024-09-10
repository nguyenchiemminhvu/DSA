/**
https://leetcode.com/problems/maximize-greatness-of-an-array/

You are given a 0-indexed integer array nums. You are allowed to permute nums into a new array perm of your choosing.
We define the greatness of nums be the number of indices 0 <= i < nums.length for which perm[i] > nums[i].
Return the maximum possible greatness you can achieve after permuting nums.

Example 1:

Input: nums = [1,3,5,2,1,3,1]
Output: 4
Explanation: One of the optimal rearrangements is perm = [2,5,1,3,3,1,1].
At indices = 0, 1, 3, and 4, perm[i] > nums[i]. Hence, we return 4.
Example 2:

Input: nums = [1,2,3,4]
Output: 3
Explanation: We can prove the optimal perm is [2,3,4,1].
At indices = 0, 1, and 2, perm[i] > nums[i]. Hence, we return 3.

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int maximizeGreatness(vector<int>& nums)
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL), cout.tie(NULL);

        int res = 0;
        std::sort(nums.begin(), nums.end());

        int left = 0;
        int right = 0;
        int n = nums.size();
        while (right < n)
        {
            if (nums[left] < nums[right])
            {
                left++;
                res++;
            }

            right++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1,3,5,2,1,3,1};
    std::cout << sol.maximizeGreatness(nums) << std::endl;

    return 0;
}