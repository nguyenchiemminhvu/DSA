/**
https://leetcode.com/problems/number-of-sub-arrays-with-odd-sum/description/

Given an array of integers arr, return the number of subarrays with an odd sum.

Since the answer can be very large, return it modulo 109 + 7.

Example 1:

Input: arr = [1,3,5]
Output: 4
Explanation: All subarrays are [[1],[1,3],[1,3,5],[3],[3,5],[5]]
All sub-arrays sum are [1,4,9,3,8,5].
Odd sums are [1,9,3,5] so the answer is 4.

Example 2:

Input: arr = [2,4,6]
Output: 0
Explanation: All subarrays are [[2],[2,4],[2,4,6],[4],[4,6],[6]]
All sub-arrays sum are [2,6,12,4,10,6].
All sub-arrays have even sum and the answer is 0.

Example 3:

Input: arr = [1,2,3,4,5,6,7]
Output: 16

Constraints:

1 <= arr.length <= 105
1 <= arr[i] <= 100
 */

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

#define MOD (1000000007)

class Solution
{
public:
    int numOfSubarrays(vector<int>& arr)
    {
        int res = 0;
        int cur_sum = 0;
        int odd_count = 0;
        int even_count = 1;
        for (int n : arr)
        {
            cur_sum += n;

            if (cur_sum & 1)
            {
                odd_count++;
                res = ((res % MOD) + (even_count % MOD)) % MOD;
            }
            else
            {
                even_count++;
                res = ((res % MOD) + (odd_count % MOD)) % MOD;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7};
    std::cout << sol.numOfSubarrays(arr) << std::endl;
    return 0;
}