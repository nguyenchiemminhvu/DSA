/**
https://vjudge.net/contest/690993#problem/H
https://usaco.guide/problems/ac-gcd-on-blackboard/solution
 */

#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <numeric>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int maxGCD(const std::vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> prefix(n, 1);
        std::vector<int> suffix(n, 1);

        prefix[0] = nums[0];
        suffix.back() = nums.back();

        for (int i = 1; i < nums.size(); i++)
        {
            prefix[i] = std::gcd(prefix[i - 1], nums[i]);
        }

        for (int i = n - 2; i >= 0; i--)
        {
            suffix[i] = std::gcd(suffix[i + 1], nums[i]);
        }

        int res = 1;
        for (int i = 0; i < n; i++)
        {
            if (i == 0)
            {
                res = std::max(res, suffix[i + 1]);
            }
            else if (i == n - 1)
            {
                res = std::max(res, prefix[i - 1]);
            }
            else
            {
                res = std::max(res, std::gcd(prefix[i - 1], suffix[i + 1]));
            }
        }
        return res;
    }
};

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> nums[i];
    }

    Solution sol;
    std::cout << sol.maxGCD(nums) << std::endl;

    return 0;
}