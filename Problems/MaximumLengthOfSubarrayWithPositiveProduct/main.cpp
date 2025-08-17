/**
https://leetcode.com/problems/maximum-length-of-subarray-with-positive-product/

Given an array of integers nums, find the maximum length of a subarray where the product of all its elements is positive.

A subarray of an array is a consecutive sequence of zero or more values taken out of that array.

Return the maximum length of a subarray with positive product.

Example 1:

Input: nums = [1,-2,-3,4]
Output: 4
Explanation: The array nums already has a positive product of 24.

Example 2:

Input: nums = [0,1,-2,-3,-4]
Output: 3
Explanation: The longest subarray with positive product is [1,-2,-3] which has a product of 6.
Notice that we cannot include 0 in the subarray since that'll make the product 0 which is not positive.

Example 3:

Input: nums = [-1,-2,-3,0,1]
Output: 2
Explanation: The longest subarray with positive product is [-1,-2] or [-2,-3].

Constraints:

1 <= nums.length <= 105
-109 <= nums[i] <= 109
 */

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int getMaxLen(vector<int>& nums)
    {
        int res = 0;

        nums.push_back(0);
        std::vector<int> temp;
        int count_neg = 0;
        for (int n : nums)
        {
            if (n != 0)
            {
                temp.push_back(n);
                count_neg += (n < 0);
            }
            else
            {
                res = std::max(res, check_subarray(temp, count_neg));
                temp.clear();
                count_neg = 0;
            }
        }

        return res;
    }
private:
    int check_subarray(const std::vector<int>& arr, int count_neg)
    {
        if (count_neg % 2 == 0)
            return arr.size();

        int left = 0;
        int right = arr.size() - 1;
        while (left < arr.size() && arr[left] > 0)
        {
            left++;
        }

        while (right >= 0 && arr[right] > 0)
        {
            right--;
        }

        int exclude_left = arr.size() - (left + 1);  // Exclude the first negative
        int exclude_right = right;                  // Exclude the last negative

        return std::max(exclude_left, exclude_right);
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1,-2,-3,4};
    std::cout << sol.getMaxLen(nums) << std::endl;
    return 0;
}