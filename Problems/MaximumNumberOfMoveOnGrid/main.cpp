/**
https://leetcode.com/problems/maximum-number-of-moves-in-a-grid

You are given a 0-indexed m x n matrix grid consisting of positive integers.

You can start at any cell in the first column of the matrix, and traverse the grid in the following way:

From a cell (row, col), you can move to any of the cells: (row - 1, col + 1), (row, col + 1) and (row + 1, col + 1) such that the value of the cell you move to, should be strictly bigger than the value of the current cell.
Return the maximum number of moves that you can perform.

Example 1:

Input: grid = [[2,4,3,5],[5,4,9,3],[3,4,2,11],[10,9,13,15]]
Output: 3
Explanation: We can start at the cell (0, 0) and make the following moves:
- (0, 0) -> (0, 1).
- (0, 1) -> (1, 2).
- (1, 2) -> (2, 3).
It can be shown that it is the maximum number of moves that can be made.

Example 2:

Input: grid = [[3,2,4],[2,1,9],[1,1,7]]
Output: 0
Explanation: Starting from any cell in the first column we cannot perform any moves.

Constraints:

m == grid.length
n == grid[i].length
2 <= m, n <= 1000
4 <= m * n <= 105
1 <= grid[i][j] <= 106
 */

#include <iostream>
#include <vector>
#include <functional>
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
    int maxMoves(std::vector<std::vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        int res = 0;

        std::vector<std::vector<int>> dp(m, std::vector<int>(n, -1));
        std::function<int(int, int)> dfs = [&](int row, int col) -> int
        {
            if (col == n - 1) return 0; // Reached last column
            if (dp[row][col] != -1) return dp[row][col];

            int max_moves = 0;
            // Possible directions: right, down-right, up-right
            if (row > 0 && grid[row][col] < grid[row - 1][col + 1])
            {
                max_moves = std::max(max_moves, 1 + dfs(row - 1, col + 1));
            }
            if (grid[row][col] < grid[row][col + 1])
            {
                max_moves = std::max(max_moves, 1 + dfs(row, col + 1));
            }
            if (row < m - 1 && grid[row][col] < grid[row + 1][col + 1])
            {
                max_moves = std::max(max_moves, 1 + dfs(row + 1, col + 1));
            }

            return dp[row][col] = max_moves;
        };

        for (int row = 0; row < m; row++)
        {
            res = std::max(res, dfs(row, 0));
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> grid = {
        {3,2,4},
        {2,1,9},
        {1,1,7},
    };
    std::cout << sol.maxMoves(grid) << std::endl;
    return 0;
}