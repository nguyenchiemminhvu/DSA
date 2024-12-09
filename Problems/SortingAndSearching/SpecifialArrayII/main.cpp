/**
https://leetcode.com/problems/special-array-ii/description/

An array is considered special if every pair of its adjacent elements contains two numbers with different parity.

You are given an array of integer nums and a 2D integer matrix queries, where for queries[i] = [fromi, toi] your task is to check that 
subarray nums[fromi..toi] is special or not.

Return an array of booleans answer such that answer[i] is true if nums[fromi..toi] is special.

Example 1:

Input: nums = [3,4,1,2,6], queries = [[0,4]]

Output: [false]

Explanation:

The subarray is [3,4,1,2,6]. 2 and 6 are both even.

Example 2:

Input: nums = [4,3,1,6], queries = [[0,2],[2,3]]

Output: [false,true]

Explanation:

The subarray is [4,3,1]. 3 and 1 are both odd. So the answer to this query is false.
The subarray is [1,6]. There is only one pair: (1,6) and it contains numbers with different parity. So the answer to this query is true.

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 105
1 <= queries.length <= 105
queries[i].length == 2
0 <= queries[i][0] <= queries[i][1] <= nums.length - 1
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
    vector<bool> isArraySpecial(vector<int>& nums, vector<vector<int>>& queries)
    {
        std::vector<bool> res;

        std::vector<std::vector<int>> subarrays;
        split(nums, subarrays);

        for (const std::vector<int>& query : queries)
        {
            bool val = (search_subarray(subarrays, query[0]) == search_subarray(subarrays, query[1]));
            res.push_back(val);
        }

        return res;
    }
private:
    void split(const std::vector<int>& nums, std::vector<std::vector<int>>& subarrays)
    {
        int left = 0;
        for (int i = 1; i < nums.size(); i++)
        {
            int prev_parity = nums[i - 1] & 1;
            int cur_parity = nums[i] & 1;
            if (cur_parity == prev_parity)
            {
                subarrays.push_back({left, i - 1});
                left = i;
            }
        }

        subarrays.push_back({left, (int)nums.size() - 1});
    }

    int search_subarray(const std::vector<std::vector<int>>& subarrays, int query)
    {
        int left = 0;
        int right = subarrays.size() - 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (subarrays[mid][0] <= query && subarrays[mid][1] >= query)
            {
                return mid;
            }
            else if (subarrays[mid][0] > query)
            {
                right = mid - 1;
            }
            else if (subarrays[mid][1] < query)
            {
                left = mid + 1;
            }
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {3,4,1,2,6};
    std::vector<std::vector<int>> queries = {
        {0, 4}
    };
    std::vector<bool> res = sol.isArraySpecial(nums, queries);
    for (bool val : res)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}