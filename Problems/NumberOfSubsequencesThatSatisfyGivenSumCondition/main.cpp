/**
https://leetcode.com/problems/number-of-subsequences-that-satisfy-the-given-sum-condition/description/
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

#define MOD 1000000007

class Solution
{
public:
    int numSubseq(vector<int>& nums, int target)
    {
        long long res = 0LL;

        // Precompute powers of 2 modulo MOD
        int n = nums.size();
        vector<int> power(n, 1);
        for (int i = 1; i < n; i++)
        {
            power[i] = (power[i - 1] * 2) % MOD;
        }

        std::sort(nums.begin(), nums.end());

        int left = 0, right = n - 1;
        while (left <= right)
        {
            if (nums[left] + nums[right] <= target)
            {
                res = (res + power[right - left]) % MOD;
                left++;
            }
            else
            {
                right--;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {3, 5, 6, 7};
    int target = 9;
    std::cout << sol.numSubseq(nums, target) << std::endl;
    return 0;
}