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
    int triangleNumber(vector<int>& nums)
    {
        if (nums.size() < 3)
        {
            return 0;
        }

        std::sort(nums.begin(), nums.end());

        int count = 0;
        for (int c = nums.size() - 1; c >= 2; c--)
        {
            int a = 0;
            int b = c - 1;
            while (a < b)
            {
                if (nums[a] + nums[b] <= nums[c])
                {
                    a++;
                }
                else
                {
                    count += (b - a);
                    b--;
                }
            }
        }

        return count;
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {2, 2, 3, 4};
    cout << sol.triangleNumber(nums) << endl; // Output: 3
    return 0;
}