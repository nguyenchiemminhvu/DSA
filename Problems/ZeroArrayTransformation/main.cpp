/**
https://leetcode.com/problems/zero-array-transformation-i/description/

You are given an integer array nums of length n and a 2D array queries, where queries[i] = [li, ri].

For each queries[i]:

Select a 
subset
 of indices within the range [li, ri] in nums.
Decrement the values at the selected indices by 1.
A Zero Array is an array where all elements are equal to 0.

Return true if it is possible to transform nums into a Zero Array after processing all the queries sequentially, otherwise return false.

Example 1:

Input: nums = [1,0,1], queries = [[0,2]]

Output: true

Explanation:

For i = 0:
Select the subset of indices as [0, 2] and decrement the values at these indices by 1.
The array will become [0, 0, 0], which is a Zero Array.

Example 2:

Input: nums = [4,3,2,1], queries = [[1,3],[0,2]]

Output: false

Explanation:

For i = 0:
Select the subset of indices as [1, 2, 3] and decrement the values at these indices by 1.
The array will become [4, 2, 1, 0].
For i = 1:
Select the subset of indices as [0, 1, 2] and decrement the values at these indices by 1.
The array will become [3, 1, 0, 0], which is not a Zero Array.

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 105
1 <= queries.length <= 105
queries[i].length == 2
0 <= li <= ri < nums.length
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
    bool isZeroArray(vector<int>& nums, vector<vector<int>>& queries)
    {
        std::vector<int> diff_arr(nums.size() + 1, 0);
        for (const std::vector<int>& query : queries)
        {
            diff_arr[query[0]]++;
            diff_arr[query[1] + 1]--;
        }

        for (int i = 1; i < diff_arr.size(); i++)
        {
            diff_arr[i] += diff_arr[i - 1];
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > diff_arr[i])
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1, 0, 1};
    std::vector<std::vector<int>> queries = {{0, 2}};
    std::cout << sol.isZeroArray(nums, queries) << std::endl;
    return 0;
}