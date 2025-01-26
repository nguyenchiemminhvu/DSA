/**
https://leetcode.com/problems/sum-of-mutated-array-closest-to-target/description/

Given an integer array arr and a target value target, return the integer value such that when we change all the integers larger than value in the given array to be equal to value, the sum of the array gets as close as possible (in absolute difference) to target.

In case of a tie, return the minimum such integer.

Notice that the answer is not neccesarilly a number from arr.

Example 1:

Input: arr = [4,9,3], target = 10
Output: 3
Explanation: When using 3 arr converts to [3, 3, 3] which sums 9 and that's the optimal answer.

Example 2:

Input: arr = [2,3,5], target = 10
Output: 5

Example 3:

Input: arr = [60864,25176,27249,21296,20204], target = 56803
Output: 11361

Constraints:

1 <= arr.length <= 104
1 <= arr[i], target <= 105
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
    int findBestValue(vector<int>& arr, int target)
    {
        auto sum_with_threshold = [](const vector<int>& nums, int threshold)
        {
            int s = 0;
            for (int val : nums)
            {
                s += (val > threshold) ? threshold : val;
            }
            return s;
        };

        int left = 0;
        int right = *std::max_element(arr.begin(), arr.end());
        int result = 0;
        int closest_diff = INT_MAX;

        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            int cur_sum = sum_with_threshold(arr, mid);
            int cur_diff = std::abs(cur_sum - target);

            if (cur_diff < closest_diff || (cur_diff == closest_diff && mid < result))
            {
                closest_diff = cur_diff;
                result = mid;
            }

            if (cur_sum < target)
            {
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }

        return result;
    }
};

int main()
{
    Solution sol;
    vector<int> arr = {4, 9, 3};
    int target = 10;
    std::cout << sol.findBestValue(arr, target) << std::endl;
    return 0;
}