/**
https://leetcode.com/problems/find-the-most-competitive-subsequence/

Given an integer array nums and a positive integer k, return the most competitive subsequence of nums of size k.

An array's subsequence is a resulting sequence obtained by erasing some (possibly zero) elements from the array.

We define that a subsequence a is more competitive than a subsequence b (of the same length) if in the first position where a and b differ, subsequence a has a number less than the corresponding number in b. For example, [1,3,4] is more competitive than [1,3,5] because the first position they differ is at the final number, and 4 is less than 5.

Example 1:

Input: nums = [3,5,2,6], k = 2
Output: [2,6]
Explanation: Among the set of every possible subsequence: {[3,5], [3,2], [3,6], [5,2], [5,6], [2,6]}, [2,6] is the most competitive.

Example 2:

Input: nums = [2,4,3,3,5,4,9,6], k = 4
Output: [2,3,3,4]

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
1 <= k <= nums.length
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
    vector<int> mostCompetitive(vector<int>& nums, int k)
    {
        std::vector<int> stack;
        int n = nums.size();

        for (int i = 0; i < n; i++)
        {
            // While the stack is not empty, the current element is smaller than the top of the stack,
            // and there are enough elements left to fill the subsequence, pop the stack
            while (!stack.empty() && stack.back() > nums[i] && stack.size() + (n - i) > k)
            {
                stack.pop_back();
            }

            if (stack.size() < k)
            {
                stack.push_back(nums[i]);
            }
        }

        return stack;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {2, 4, 3, 3, 5, 4, 9, 6};
    int k = 4;
    std::vector<int> res = sol.mostCompetitive(nums, k);
    for (int n : res)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}