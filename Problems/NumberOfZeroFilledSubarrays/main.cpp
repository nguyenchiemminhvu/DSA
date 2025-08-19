// https://leetcode.com/problems/number-of-zero-filled-subarrays/

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    long long zeroFilledSubarray(vector<int>& nums)
    {
        long long res = 0LL;

        nums.push_back(1);
        int n = nums.size();
        long long count_zero = 0;
        for (int n : nums)
        {
            if (n == 0)
            {
                count_zero++;
            }
            else
            {
                res += (long long)(count_zero * (count_zero + 1) / 2);
                count_zero = 0;
            }
        }

        return res;    
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1, 3, 0, 0, 2, 0, 0, 4};
    cout << sol.zeroFilledSubarray(nums) << endl; // Output: 6
    return 0;
}