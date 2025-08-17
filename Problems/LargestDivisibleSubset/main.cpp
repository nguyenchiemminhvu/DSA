/**
https://leetcode.com/problems/largest-divisible-subset/
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
    vector<int> largestDivisibleSubset(vector<int>& nums)
    {
        std::sort(nums.begin(), nums.end());

        int n = nums.size();
        std::vector<int> dp(n, 1);
        for (int i = 1; i < n; i++)
        {
            for (int j = 0; j < i; j++)
            {
                if (nums[i] % nums[j] == 0)
                {
                    dp[i] = std::max(dp[i], dp[j] + 1);
                }
            }
        }

        int max_dp = 1;
        int max_idx = -1;
        for (int i = 0; i < n; i++)
        {
            if (max_dp <= dp[i])
            {
                max_dp = dp[i];
                max_idx = i;
            }
        }

        std::vector<int> res;
        res.push_back(nums[max_idx]);
        for (int i = max_idx - 1; i >= 0; i--)
        {
            if (dp[i] == max_dp - 1 && nums[max_idx] % nums[i] == 0)
            {
                res.push_back(nums[i]);
                max_dp--;
                max_idx = i;
            }
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1, 2, 3};
    vector<int> res = s.largestDivisibleSubset(nums);
    for (int i = 0; i < res.size(); i++)
    {
        cout << res[i] << " ";
    }
    cout << endl;
    return 0;
}