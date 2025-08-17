/**
https://leetcode.com/problems/partition-equal-subset-sum/description
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution 
{
public:
    bool canPartition(vector<int>& nums) 
    {
        int sum = 0;
        for (const int& n : nums)
        {
            sum += n;
        }
        
        if (sum & 1)
            return false;
        
        // return checkingBacktrack(nums, nums.size() - 1, sum / 2);
        return checkingDP(nums, sum / 2);
    }
private:
    bool checkingBacktrack(const std::vector<int>& nums, int i, int half_sum)
    {
        if (half_sum == 0)
            return true;
        
        if (half_sum < 0 || i < 0)
            return false;
        
        if (half_sum - nums[i] < 0)
            return checkingBacktrack(nums, i - 1, half_sum);
        
        return checkingBacktrack(nums, i - 1, half_sum - nums[i]) || checkingBacktrack(nums, i - 1, half_sum);
    }
    
    bool checkingDP(const std::vector<int>& nums, int half_sum)
    {
        std::vector<int> dp(half_sum + 1, false);
        dp[0] = true;

        for (int n : nums)
        {
            for (int i = half_sum; i >= 0; i--)
            {
                if (dp[i] == false && i - n >= 0)
                {
                    dp[i] = dp[i] || dp[i - n];
                }
            }
        }

        return dp[half_sum];
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1, 5, 11, 5};
    cout << (s.canPartition(nums) ? "true" : "false") << endl;

    nums = {1, 2, 3, 5};
    cout << (s.canPartition(nums) ? "true" : "false") << endl;

    return 0;
}