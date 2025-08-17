// https://leetcode.com/problems/count-subarrays-where-max-element-appears-at-least-k-times/description/

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
    long long countSubarrays(vector<int>& nums, int k)
    {
        long long res = 0LL;

        int n = nums.size();
        int max_value = *std::max_element(nums.begin(), nums.end());

        int cur_max = 0;
        int left = 0;
        for (int right = 0; right < n; right++)
        {
            if (nums[right] == max_value)
            {
                cur_max++;
            }

            while (cur_max == k)
            {
                if (nums[left] == max_value)
                {
                    cur_max--;
                }
                left++;
            }

            res += left;
        }

        return res;
    }
};

int main()
{
    Solution solution;
    vector<int> nums = {1, 2, 3, 4, 5};
    int k = 2;
    cout << solution.countSubarrays(nums, k) << endl;

    nums = {1, 2, 3, 4, 5, 5};
    k = 3;
    cout << solution.countSubarrays(nums, k) << endl;
    return 0;
}