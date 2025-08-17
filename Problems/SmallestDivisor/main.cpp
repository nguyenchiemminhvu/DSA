/**
https://leetcode.com/problems/find-the-smallest-divisor-given-a-threshold/description/

Given an array of integers nums and an integer threshold, we will choose a positive integer divisor, divide all the array by it, and sum the division's result. Find the smallest divisor such that the result mentioned above is less than or equal to threshold.

Each result of the division is rounded to the nearest integer greater than or equal to that element. (For example: 7/3 = 3 and 10/2 = 5).

The test cases are generated so that there will be an answer.

Example 1:

Input: nums = [1,2,5,9], threshold = 6
Output: 5
Explanation: We can get a sum to 17 (1+2+5+9) if the divisor is 1. 
If the divisor is 4 we can get a sum of 7 (1+1+2+3) and if the divisor is 5 the sum will be 5 (1+1+1+2). 

Example 2:

Input: nums = [44,22,33,11,1], threshold = 5
Output: 44

Constraints:

1 <= nums.length <= 5 * 104
1 <= nums[i] <= 106
nums.length <= threshold <= 106
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <climits>
#include <cstdint>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int smallestDivisor(vector<int>& nums, int threshold)
    {
        int res = INT_MAX;
        long long left = 1;
        long long right = 1e7 + 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (testing(nums, threshold, mid))
            {
                res = std::min(res, mid);
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return res;
    }

private:
    bool testing(const std::vector<int>& nums, int threshold, long long div)
    {
        long long sum = 0LL;
        for (int val : nums)
        {
            sum += std::ceil((double)val / div);
        }
        return sum <= threshold;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1, 2, 5, 9};
    int threshold = 6;
    std::cout << sol.smallestDivisor(nums, threshold) << std::endl;
    return 0;
}