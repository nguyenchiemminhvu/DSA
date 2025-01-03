/**
Given an integer array nums, return the number of triplets chosen from the array that can make triangles if we take them as side lengths of a triangle.

Example 1:

Input: nums = [2,2,3,4]
Output: 3
Explanation: Valid combinations are: 
2,3,4 (using the first 2)
2,3,4 (using the second 2)
2,2,3

Example 2:

Input: nums = [4,2,3,4]
Output: 4

Constraints:

1 <= nums.length <= 1000
0 <= nums[i] <= 1000
 */

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    int triangleNumber(vector<int>& nums)
    {
        int res = 0;
        std::sort(nums.begin(), nums.end());
        for (int i = nums.size() - 1; i >= 0; i--)
        {
            int left = 0;
            int right = i - 1;

            while (left < right)
            {
                int a = nums[left];
                int b = nums[right];
                int c = nums[i];
                if (a + b > c)
                {
                    res += (right - left);
                    right--;
                }
                else
                {
                    left++;
                }
            }
        }

        return res;
    }

};

int main()
{
    Solution sol;
    std::cout << sol.triangleNumber({2, 2, 3, 4}) << std::endl;
    return 0;
}