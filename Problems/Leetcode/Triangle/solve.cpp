#include <iostream>
#include <cmath>
#include <numeric>
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
    int minimumTotal(vector<vector<int>>& triangle)
    {
        const long long MAX = 1e4 + 1;
        int n = triangle.size();
        if (n == 1)
        {
            return triangle[0][0];
        }

        std::vector<long long> dp(n, MAX);
        dp[0] = triangle[0][0];
        for (int i = 1; i < n; i++)
        {
            std::vector<long long> temp(n, MAX);
            std::copy(triangle[i].begin(), triangle[i].end(), temp.begin());
            temp[0] += dp[0];
            for (int j = 1; j < n; j++)
            {
                temp[j] = std::min(temp[j] + dp[j - 1], temp[j] + dp[j]);
            }

            dp = temp;
        }

        return (int)*std::min_element(dp.begin(), dp.end());
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> triangle = {
        {2},
        {3, 4},
        {6, 5, 7},
        {4, 1, 8, 3}
    };
    cout << sol.minimumTotal(triangle) << endl;
    return 0;
}