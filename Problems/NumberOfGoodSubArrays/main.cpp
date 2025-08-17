/**
https://leetcode.com/problems/count-the-number-of-good-subarrays/

Given an integer array nums and an integer k, return the number of good subarrays of nums.
A subarray arr is good if it there are at least k pairs of indices (i, j) such that i < j and arr[i] == arr[j].
A subarray is a contiguous non-empty sequence of elements within an array.

Example 1:

Input: nums = [1,1,1,1,1], k = 10
Output: 1
Explanation: The only good subarray is the array nums itself.

Example 2:

Input: nums = [3,1,4,3,2,2,4], k = 2
Output: 4
Explanation: There are 4 different good subarrays:
- [3,1,4,3,2,2] that has 2 pairs.
- [3,1,4,3,2,2,4] that has 3 pairs.
- [1,4,3,2,2,4] that has 2 pairs.
- [4,3,2,2,4] that has 2 pairs.

Constraints:

1 <= nums.length <= 105
1 <= nums[i], k <= 109
*/

#include <iostream>
#include <vector>
#include <unordered_map>

class Solution
{
public:
    long long countGood(std::vector<int>& nums, int k)
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        long long res = 0;

        int n = nums.size();
        int left = 0;
        int right = 0;
        std::unordered_map<int, int> counter;
        int cur_pair = 0;
        while (right < n)
        {
            cur_pair += counter[nums[right]];
            counter[nums[right]]++;

            while (cur_pair >= k)
            {
                res += (n - right);

                counter[nums[left]]--;
                cur_pair -= (counter[nums[left]]);
                left++;
            }

            right++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> input = {3,1,4,3,2,2,4};
    std::cout << sol.countGood(input, 2) << std::endl;
    return 0;
}