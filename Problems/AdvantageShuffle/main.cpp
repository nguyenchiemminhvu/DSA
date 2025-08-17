/**
https://leetcode.com/problems/advantage-shuffle/description/

You are given two integer arrays nums1 and nums2 both of the same length. The advantage of nums1 with respect to nums2 is the number of indices i for which nums1[i] > nums2[i].

Return any permutation of nums1 that maximizes its advantage with respect to nums2.

Example 1:

Input: nums1 = [2,7,11,15], nums2 = [1,10,4,11]
Output: [2,11,7,15]

Example 2:

Input: nums1 = [12,24,8,32], nums2 = [13,25,32,11]
Output: [24,32,8,12]

Constraints:

1 <= nums1.length <= 105
nums2.length == nums1.length
0 <= nums1[i], nums2[i] <= 109
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
    vector<int> advantageCount(vector<int>& nums1, vector<int>& nums2)
    {
        std::sort(nums1.begin(), nums1.end(), std::greater<int>());
        std::vector<std::pair<int, int>> temp(nums2.size());
        for (int i = 0; i < nums2.size(); i++)
        {
            temp[i] = {nums2[i], i};
        }
        std::sort(temp.begin(), temp.end(), std::greater<std::pair<int, int>>());

        std::vector<int> res(nums2.size());
        int left = 0;
        int right = nums1.size() - 1;
        for (int i = 0; i < temp.size(); i++)
        {
            if (nums1[left] > temp[i].first)
            {
                res[temp[i].second] = nums1[left];
                left++;
            }
            else
            {
                res[temp[i].second] = nums1[right];
                right--;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums1 = {2, 7, 11, 15};
    std::vector<int> nums2 = {1, 10, 4, 11};
    std::vector<int> res = sol.advantageCount(nums1, nums2);
    for (int i = 0; i < res.size(); i++)
    {
        std::cout << res[i] << " ";
    }
    std::cout << std::endl;
    return 0;
}