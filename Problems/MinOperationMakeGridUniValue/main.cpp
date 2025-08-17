/**
https://leetcode.com/problems/minimum-operations-to-make-a-uni-value-grid/description/
 */

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int minOperations(vector<vector<int>>& grid, int x)
    {
        std::vector<int> arr;
        for (const std::vector<int>& row : grid)
        {
            for (int val : row)
            {
                arr.push_back(val);
            }
        }

        int base = arr[0];
        for (int val : arr)
        {
            if ((val - base) % x != 0)
            {
                return -1;
            }
        }

        std::sort(arr.begin(), arr.end());
        int median = arr[arr.size() / 2];

        int res = 0;
        for (int val : arr)
        {
            res += std::abs(val - median) / x;
        }

        return res;
    }
};