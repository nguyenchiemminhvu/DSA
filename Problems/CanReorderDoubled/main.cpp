/**
https://leetcode.com/problems/array-of-doubled-pairs/

Given an integer array of even length arr, return true if it is possible to reorder arr such that arr[2 * i + 1] = 2 * arr[2 * i] for every 0 <= i < len(arr) / 2, or false otherwise.

Example 1:

Input: arr = [3,1,3,6]
Output: false

Example 2:

Input: arr = [2,1,2,6]
Output: false

Example 3:

Input: arr = [4,-2,2,-4]
Output: true
Explanation: We can take two groups, [-2,-4] and [2,4] to form [-2,-4,2,4] or [2,4,-2,-4].

Constraints:

2 <= arr.length <= 3 * 104
arr.length is even.
-105 <= arr[i] <= 105
 */

#include <iostream>
#include <vector>
#include <algorithm>
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
    bool canReorderDoubled(vector<int>& arr)
    {
        std::sort(arr.begin(), arr.end(), [](int a, int b) { return std::abs(a) < std::abs(b); });
        std::unordered_map<int, int> freq;
        for (int val : arr)
        {
            freq[val]++;
        }

        for (int val : arr)
        {
            if (freq[val] == 0)
            {
                continue;
            }

            if (freq[val * 2] == 0)
            {
                return false;
            }

            freq[val]--;
            freq[val * 2]--;
        }

        return true;
    }
};

int main()
{
    Solution sol;
    std::vector<int> arr = {4,-2,2,-4};
    std::cout << sol.canReorderDoubled(arr) << std::endl;

    return 0;
}