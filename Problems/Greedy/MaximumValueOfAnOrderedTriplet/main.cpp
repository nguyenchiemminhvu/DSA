/**
https://leetcode.com/problems/maximum-value-of-an-ordered-triplet-ii
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
    long long maximumTripletValue(vector<int>& nums)
    {
        int n = nums.size();
        std::vector<int> max_left(n, INT_MIN);
        for (int i = 1; i < n; i++)
        {
            max_left[i] = std::max(max_left[i - 1], nums[i - 1]);
        }
        
        std::vector<int> max_right(n, INT_MIN);
        for (int i = n - 2; i >= 0; i--)
        {
            max_right[i] = std::max(max_right[i + 1], nums[i + 1]);
        }

        long long res = 0LL;
        for (int i = 1; i < n; i++)
        {
            if (max_left[i] > nums[i])
            {
                res = std::max(res, (long long)(max_left[i] - nums[i]) * max_right[i]);
            }
        }
        return res;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << sol.maximumTripletValue(nums) << endl; // Output: 6
    nums = {5, 1, 3, 2, 4};
    cout << sol.maximumTripletValue(nums) << endl; // Output: 6
    nums = {1, 2, 3};
    cout << sol.maximumTripletValue(nums) << endl; // Output: 0
    nums = {1, 2, 3, 4};
    cout << sol.maximumTripletValue(nums) << endl; // Output: 6
    return 0;
}