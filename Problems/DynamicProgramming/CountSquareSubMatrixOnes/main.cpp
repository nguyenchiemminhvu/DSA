/**
https://leetcode.com/problems/count-square-submatrices-with-all-ones

Given a m * n matrix of ones and zeros, return how many square submatrices have all ones.

Example 1:

Input: matrix =
[
  [0,1,1,1],
  [1,1,1,1],
  [0,1,1,1]
]
Output: 15
Explanation: 
There are 10 squares of side 1.
There are 4 squares of side 2.
There is  1 square of side 3.
Total number of squares = 10 + 4 + 1 = 15.

Example 2:

Input: matrix = 
[
  [1,0,1],
  [1,1,0],
  [1,1,0]
]
Output: 7
Explanation: 
There are 6 squares of side 1.  
There is 1 square of side 2. 
Total number of squares = 6 + 1 = 7.

Constraints:

1 <= arr.length <= 300
1 <= arr[0].length <= 300
0 <= arr[i][j] <= 1
 */

#include <iostream>
#include <vector>
#include <utility>
#include <numeric>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return false;
}();

class Solution
{
public:
    int countSquares(vector<vector<int>>& matrix)
    {
        std::vector<std::vector<int>> dp(matrix.size(), std::vector<int>(matrix[0].size(), 0));

        for (int i = 0; i < matrix.size(); i++)
        {
            dp[i][0] = matrix[i][0];
        }

        for (int i = 0; i < matrix[0].size(); i++)
        {
            dp[0][i] = matrix[0][i];
        }

        for (int i = 1; i < dp.size(); i++)
        {
            for (int j = 1; j < dp[0].size(); j++)
            {
                if (matrix[i][j] == 1)
                {
                    if (dp[i - 1][j - 1] && dp[i - 1][j] && dp[i][j - 1])
                    {
                        dp[i][j] = std::min(dp[i - 1][j - 1], std::min(dp[i - 1][j], dp[i][j - 1])) + 1;
                    }
                    else
                    {
                        dp[i][j]++;
                    }
                }
            }
        }

        int res = 0;
        for (const std::vector<int>& row : dp)
        {
            res += std::accumulate(row.begin(), row.end(), 0);
        }
        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> matrix = {
        {1, 0, 1},
        {1, 1, 0},
        {1, 1, 0},
    };
    std::cout << sol.countSquares(matrix) << std::endl;
    return 0;
}