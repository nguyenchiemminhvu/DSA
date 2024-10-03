/**
https://leetcode.com/problems/make-sum-divisible-by-p

Given an array of positive integers nums, remove the smallest subarray (possibly empty) such that the sum of the remaining elements is divisible by p. It is not allowed to remove the whole array.

Return the length of the smallest subarray that you need to remove, or -1 if it's impossible.

A subarray is defined as a contiguous block of elements in the array.

Example 1:

Input: nums = [3,1,4,2], p = 6
Output: 1
Explanation: The sum of the elements in nums is 10, which is not divisible by 6. We can remove the subarray [4], and the sum of the remaining elements is 6, which is divisible by 6.

Example 2:

Input: nums = [6,3,5,2], p = 9
Output: 2
Explanation: We cannot remove a single element to get a sum divisible by 9. The best way is to remove the subarray [5,2], leaving us with [6,3] with sum 9.

Example 3:

Input: nums = [1,2,3], p = 3
Output: 0
Explanation: Here the sum is 6. which is already divisible by 3. Thus we do not need to remove anything.

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= p <= 109
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <numeric>
#include <climits>

using namespace std;

static const int acceleration_hack = []() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    return 0;
}();

class Solution
{
public:
    int minSubarray(vector<int>& nums, int p)
    {
        long long sum = std::accumulate(nums.begin(), nums.end(), 0LL);
        int remainder = sum % p;
        if (remainder == 0)
            return 0;
        
        std::unordered_map<int, int> last_rem_index;
        last_rem_index[0] = -1;

        long long cur_sum = 0LL;
        int min_length = INT_MAX;

        for (int i = 0; i < nums.size(); i++)
        {
            cur_sum += nums[i];
            int cur_rem = cur_sum % p;
            int target_rem = (cur_rem - remainder + p) % p;

            if (last_rem_index.find(target_rem) != last_rem_index.end()) {
                min_length = std::min(min_length, i - last_rem_index[target_rem]);
            }

            last_rem_index[cur_rem] = i;
        }

        return min_length >= nums.size() ? -1 : min_length;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {3,1,4,2};
    int k = 6;
    std::cout << sol.minSubarray(nums, k) << std::endl;
    return 0;
}