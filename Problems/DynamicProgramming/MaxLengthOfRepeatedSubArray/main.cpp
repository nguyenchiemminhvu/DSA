/**
https://leetcode.com/problems/maximum-length-of-repeated-subarray/

Given two integer arrays nums1 and nums2, return the maximum length of a subarray that appears in both arrays.

Example 1:

Input: nums1 = [1,2,3,2,1], nums2 = [3,2,1,4,7]
Output: 3
Explanation: The repeated subarray with maximum length is [3,2,1].

Example 2:

Input: nums1 = [0,0,0,0,0], nums2 = [0,0,0,0,0]
Output: 5
Explanation: The repeated subarray with maximum length is [0,0,0,0,0].

Constraints:

1 <= nums1.length, nums2.length <= 1000
0 <= nums1[i], nums2[i] <= 100
*/

#include <iostream>
#include <vector>

class Solution
{
public:
    int findLength(std::vector<int>& nums1, std::vector<int>& nums2)
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(0);
        std::cout.tie(0);

        int res = 0;

        // for (int i1 = 0; i1 < nums1.size(); i1++)
        // {
        //     for (int i2 = 0; i2 < nums2.size(); i2++)
        //     {
        //         res = std::max(res, findLengthBF(nums1, i1, nums2, i2));
        //     }
        // }

        res = findLengthDP(nums1, nums2);

        return res;
    }
private:
    int findLengthBF(const std::vector<int>& nums1, int i1, const std::vector<int>& nums2, int i2)
    {
        int res = 0;
        while (i1 < nums1.size() && i2 < nums2.size() && nums1[i1] == nums2[i2])
        {
            i1++;
            i2++;
            res++;
        }
        return res;
    }

    int findLengthDP(const std::vector<int>& nums1, const std::vector<int>& nums2)
    {
        int res = 0;

        std::vector<std::vector<int>> dp(nums1.size() + 1, std::vector<int>(nums2.size() + 1, 0));
        for (int i1 = 1; i1 <= nums1.size(); i1++)
        {
            for (int i2 = 1; i2 <= nums2.size(); i2++)
            {
                if (nums1[i1 - 1] == nums2[i2 - 1])
                {
                    dp[i1][i2] = dp[i1 - 1][i2 - 1] + 1;
                    res = std::max(res, dp[i1][i2]);
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> a1 = {1,2,3,2,1};
    std::vector<int> a2 = {3,2,1,4,7};
    std::cout << sol.findLength(a1, a2) << std::endl;
    return 0;
}