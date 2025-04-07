/**
https://leetcode.com/problems/minimum-pair-removal-to-sort-array-i/
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int minimumPairRemoval(vector<int>& nums)
    {
        int res = 0;
        
        while (true)
        {
            bool sorted = true;
            bool non_sorted_idx = -1;
            for (int i = 1; i < nums.size(); i++)
            {
                if (nums[i] < nums[i - 1])
                {
                    non_sorted_idx = i;
                    sorted = false;
                    break;
                }
            }

            if (sorted)
            {
                break;
            }

            res++;

            int min_idx = non_sorted_idx;
            int min_sum = nums[non_sorted_idx] + nums[non_sorted_idx - 1];
            for (int i = non_sorted_idx; i < nums.size(); i++)
            {
                if (nums[i] + nums[i - 1] < min_sum)
                {
                    min_idx = i;
                    min_sum = nums[i] + nums[i - 1];
                }
            }

            nums[min_idx - 1] = min_sum;
            for (int i = min_idx + 1; i < nums.size(); i++)
            {
                nums[i - 1] = nums[i];
            }
            nums.pop_back();
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1, 2, 3, 4, 5};
    cout << s.minimumPairRemoval(nums) << endl; // Output: 0
    nums = {5, 4, 3, 2, 1};
    cout << s.minimumPairRemoval(nums) << endl; // Output: 4
    nums = {1, 3, 2, 4, 5};
    cout << s.minimumPairRemoval(nums) << endl; // Output: 1
    return 0;
}