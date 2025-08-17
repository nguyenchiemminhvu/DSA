/**
https://leetcode.com/problems/divide-array-in-sets-of-k-consecutive-numbers/
https://leetcode.com/problems/hand-of-straights/description/

Given an array of integers nums and a positive integer k, check whether it is possible to divide this array into sets of k consecutive numbers.

Return true if it is possible. Otherwise, return false.

Example 1:

Input: nums = [1,2,3,3,4,4,5,6], k = 4
Output: true
Explanation: Array can be divided into [1,2,3,4] and [3,4,5,6].

Example 2:

Input: nums = [3,2,1,2,3,4,3,4,5,9,10,11], k = 3
Output: true
Explanation: Array can be divided into [1,2,3] , [2,3,4] , [3,4,5] and [9,10,11].

Example 3:

Input: nums = [1,2,3,4], k = 3
Output: false
Explanation: Each array should be divided in subarrays of size 3.

Constraints:

1 <= k <= nums.length <= 105
1 <= nums[i] <= 109
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

static bool init = []()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return true;
}();

class Solution
{
public:
    bool isPossibleDivide(vector<int>& nums, int k)
    {
        if (nums.size() < k || nums.size() % k != 0)
        {
            return false;
        }

        std::sort(nums.begin(), nums.end());
        
        std::unordered_map<int, int> freq;
        for (int n : nums)
        {
            freq[n]++;
        }

        for (int n : nums)
        {
            if (freq[n] > 0)
            {
                for (int i = n; i < n + k; i++)
                {
                    if (freq[i] == 0)
                    {
                        return false;
                    }
                    freq[i]--;
                }
            }
        }

        return true;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {1,2,3,3,4,4,5,6};
    int k = 4;
    std::cout << sol.isPossibleDivide(nums, k) << std::endl;
    return 0;
}