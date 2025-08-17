/**
https://leetcode.com/problems/max-sum-of-a-pair-with-equal-sum-of-digits/description/

You are given a 0-indexed array nums consisting of positive integers. You can choose two indices i and j, such that i != j, and the sum of digits of the number nums[i] is equal to that of nums[j].

Return the maximum value of nums[i] + nums[j] that you can obtain over all possible indices i and j that satisfy the conditions.

Example 1:

Input: nums = [18,43,36,13,7]
Output: 54
Explanation: The pairs (i, j) that satisfy the conditions are:
- (0, 2), both numbers have a sum of digits equal to 9, and their sum is 18 + 36 = 54.
- (1, 4), both numbers have a sum of digits equal to 7, and their sum is 43 + 7 = 50.
So the maximum sum that we can obtain is 54.

Example 2:

Input: nums = [10,12,19,14]
Output: -1
Explanation: There are no two numbers that satisfy the conditions, so we return -1.

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int maximumSum(vector<int>& nums)
    {
        int res = -1;
        std::unordered_map<int, int> M;
        for (int i = 0; i < nums.size(); i++)
        {
            int s = sumDigits(nums[i]);
            if (M.find(s) != M.end())
            {
                res = std::max(res, nums[i] + nums[M[s]]);
                if (nums[i] > nums[M[s]])
                {
                    M[s] = i;
                }
            }
            else
            {
                M[s] = i;
            }
        }

        return res;
    }
private:
    int sumDigits(int n)
    {
        int s = 0;
        while (n)
        {
            s += (n % 10);
            n /= 10;
        }
        return s;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {18, 43, 36, 13, 7};
    std::cout << sol.maximumSum(nums) << std::endl;
    return 0;
}