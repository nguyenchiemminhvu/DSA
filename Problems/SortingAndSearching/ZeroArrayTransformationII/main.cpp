/**
https://leetcode.com/problems/zero-array-transformation-ii/

You are given an integer array nums of length n and a 2D array queries where queries[i] = [li, ri, vali].

Each queries[i] represents the following action on nums:

Decrement the value at each index in the range [li, ri] in nums by at most vali.
The amount by which each value is decremented can be chosen independently for each index.
A Zero Array is an array with all its elements equal to 0.

Return the minimum possible non-negative value of k, such that after processing the first k queries in sequence, nums becomes a Zero Array. If no such k exists, return -1.

Example 1:

Input: nums = [2,0,2], queries = [[0,2,1],[0,2,1],[1,1,3]]

Output: 2

Explanation:

For i = 0 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
The array will become [1, 0, 1].
For i = 1 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 0, 1] respectively.
The array will become [0, 0, 0], which is a Zero Array. Therefore, the minimum value of k is 2.

Example 2:

Input: nums = [4,3,2,1], queries = [[1,3,2],[0,2,1]]

Output: -1

Explanation:

For i = 0 (l = 1, r = 3, val = 2):
Decrement values at indices [1, 2, 3] by [2, 2, 1] respectively.
The array will become [4, 1, 0, 0].
For i = 1 (l = 0, r = 2, val = 1):
Decrement values at indices [0, 1, 2] by [1, 1, 0] respectively.
The array will become [3, 0, 0, 0], which is not a Zero Array.

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 5 * 105
1 <= queries.length <= 105
queries[i].length == 3
0 <= li <= ri < nums.length
1 <= vali <= 5
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
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries)
    {
        int res = INT_MAX;

        int left = 0;
        int right = queries.size();
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (testing(nums, queries, mid))
            {
                res = std::min(res, mid);
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return (res == INT_MAX) ? -1 : res;
    }
private:
    bool testing(const std::vector<int>& nums, const std::vector<std::vector<int>>& queries, int mid)
    {
        std::vector<int> diff(nums.size() + 1, 0);
        for (int i = 0; i < mid; i++)
        {
            int l = queries[i][0];
            int r = queries[i][1];
            int val = queries[i][2];
            
            diff[l] += val;
            diff[r + 1] -= val;
        }

        for (int i = 1; i < diff.size(); i++)
        {
            diff[i] += diff[i - 1];
        }

        for (int i = 0; i < nums.size(); i++)
        {
            if (nums[i] > diff[i])
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
    vector<int> nums = {2, 0, 2};
    vector<vector<int>> queries = {{0, 2, 1}, {0, 2, 1}, {1, 1, 3}};
    std::cout << sol.minZeroArray(nums, queries) << std::endl;
    return 0;
}