/**
https://leetcode.com/problems/count-number-of-bad-pairs/description/

You are given a 0-indexed integer array nums. A pair of indices (i, j) is a bad pair if i < j and j - i != nums[j] - nums[i].

Return the total number of bad pairs in nums.

Example 1:

Input: nums = [4,1,3,3]
Output: 5
Explanation: The pair (0, 1) is a bad pair since 1 - 0 != 1 - 4.
The pair (0, 2) is a bad pair since 2 - 0 != 3 - 4, 2 != -1.
The pair (0, 3) is a bad pair since 3 - 0 != 3 - 4, 3 != -1.
The pair (1, 2) is a bad pair since 2 - 1 != 3 - 1, 1 != 2.
The pair (2, 3) is a bad pair since 3 - 2 != 3 - 3, 1 != 0.
There are a total of 5 bad pairs, so we return 5.

Example 2:

Input: nums = [1,2,3,4,5]
Output: 0
Explanation: There are no bad pairs.

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
    long long countBadPairs(vector<int>& nums)
    {
        long long res = 0LL;

        std::unordered_map<int, int> counter;
        for (int i = 0; i < nums.size(); i++)
        {
            int cur = nums[i] - i;
            res += i - counter[cur];
            counter[cur]++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {4, 1, 3, 3}; // Example input
    std::cout << sol.countBadPairs(nums) << std::endl;
    return 0;
}