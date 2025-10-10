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
    vector<int> searchRange(vector<int>& nums, int target)
    {
        auto lower = std::lower_bound(nums.begin(), nums.end(), target);
        if (lower == nums.end() || *lower != target)
        {
            return {-1, -1};
        }

        auto upper = std::upper_bound(nums.begin(), nums.end(), target);
        return {(int)std::distance(nums.begin(), lower), (int)std::distance(nums.begin(), upper - 1)};
    }
};

int main()
{
    Solution sol;
    vector<int> nums = {5, 7, 7, 8, 8, 10};
    int target = 8;
    vector<int> result = sol.searchRange(nums, target);
    cout << "[" << result[0] << ", " << result[1] << "]" << endl; // Output: [3, 4]
    return 0;
}