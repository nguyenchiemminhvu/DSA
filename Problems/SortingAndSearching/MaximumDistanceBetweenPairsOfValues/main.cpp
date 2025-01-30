/**
https://leetcode.com/problems/maximum-distance-between-a-pair-of-values/

You are given two non-increasing 0-indexed integer arrays nums1​​​​​​ and nums2​​​​​​.

A pair of indices (i, j), where 0 <= i < nums1.length and 0 <= j < nums2.length, is valid if both i <= j and nums1[i] <= nums2[j]. The distance of the pair is j - i​​​​.

Return the maximum distance of any valid pair (i, j). If there are no valid pairs, return 0.

An array arr is non-increasing if arr[i-1] >= arr[i] for every 1 <= i < arr.length.

Example 1:

Input: nums1 = [55,30,5,4,2], nums2 = [100,20,10,10,5]
Output: 2
Explanation: The valid pairs are (0,0), (2,2), (2,3), (2,4), (3,3), (3,4), and (4,4).
The maximum distance is 2 with pair (2,4).

Example 2:

Input: nums1 = [2,2,2], nums2 = [10,10,1]
Output: 1
Explanation: The valid pairs are (0,0), (0,1), and (1,1).
The maximum distance is 1 with pair (0,1).

Example 3:

Input: nums1 = [30,29,19,5], nums2 = [25,25,25,25,25]
Output: 2
Explanation: The valid pairs are (2,2), (2,3), (2,4), (3,3), and (3,4).
The maximum distance is 2 with pair (2,4).

Constraints:

1 <= nums1.length, nums2.length <= 105
1 <= nums1[i], nums2[j] <= 105
Both nums1 and nums2 are non-increasing.
 */

#include <iostream>
#include <vector>
#include <algorithm>
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
    int maxDistance(vector<int>& nums1, vector<int>& nums2)
    {
        int res = 0;
        for (int i = 0; i < nums1.size(); i++)
        {
            auto it2 = std::lower_bound(nums2.rbegin(), nums2.rend(), nums1[i]);
            if (it2 != nums2.rend())
            {
                int j = nums2.size() - std::distance(nums2.rbegin(), it2) - 1;
                if (j > i)
                {
                    res = std::max(res, j - i);
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums1 = {55, 30, 5, 4, 2};
    vector<int> nums2 = {100, 20, 10, 10, 5};
    std::cout << sol.maxDistance(nums1, nums2) << std::endl;
    return 0;
}