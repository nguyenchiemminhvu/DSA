/**
https://leetcode.com/problems/grid-game/description/

You are given a 0-indexed 2D array grid of size 2 x n, where grid[r][c] represents the number of points at position (r, c) on the matrix. Two robots are playing a game on this matrix.

Both robots initially start at (0, 0) and want to reach (1, n-1). Each robot may only move to the right ((r, c) to (r, c + 1)) or down ((r, c) to (r + 1, c)).

At the start of the game, the first robot moves from (0, 0) to (1, n-1), collecting all the points from the cells on its path. For all cells (r, c) traversed on the path, grid[r][c] is set to 0. Then, the second robot moves from (0, 0) to (1, n-1), collecting the points on its path. Note that their paths may intersect with one another.

The first robot wants to minimize the number of points collected by the second robot. In contrast, the second robot wants to maximize the number of points it collects. If both robots play optimally, return the number of points collected by the second robot.

Example 1:

Input: grid = [[2,5,4],[1,5,1]]
Output: 4
Explanation: The optimal path taken by the first robot is shown in red, and the optimal path taken by the second robot is shown in blue.
The cells visited by the first robot are set to 0.
The second robot will collect 0 + 0 + 4 + 0 = 4 points.

Example 2:

Input: grid = [[3,3,1],[8,5,2]]
Output: 4
Explanation: The optimal path taken by the first robot is shown in red, and the optimal path taken by the second robot is shown in blue.
The cells visited by the first robot are set to 0.
The second robot will collect 0 + 3 + 1 + 0 = 4 points.

Example 3:

Input: grid = [[1,3,1,15],[1,3,3,1]]
Output: 7
Explanation: The optimal path taken by the first robot is shown in red, and the optimal path taken by the second robot is shown in blue.
The cells visited by the first robot are set to 0.
The second robot will collect 0 + 1 + 3 + 3 + 0 = 7 points.

Constraints:

grid.length == 2
n == grid[r].length
1 <= n <= 5 * 104
1 <= grid[r][c] <= 105
 */

#include <iostream>
#include <vector>
#include <cstdint>
#include <algorithm>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    long long gridGame(vector<vector<int>>& grid)
    {
        long long res = LLONG_MAX;
        int n = grid[0].size();

        std::vector<long long> prefix_top(n, 0);
        std::vector<long long> prefix_bot(n, 0);

        prefix_top[0] = grid[0][0];
        prefix_bot[0] = grid[1][0];
        for (int i = 1; i < n; i++)
        {
            prefix_top[i] = prefix_top[i - 1] + grid[0][i];
            prefix_bot[i] = prefix_bot[i - 1] + grid[1][i];
        }

        long long sum_top = prefix_top.back();
        long long sum_bot = prefix_bot.back();
        for (int i = 0; i < n; i++)
        {
            long long left_over_top = sum_top - prefix_top[i];
            long long left_over_bot = (i == 0) ? 0 : prefix_bot[i - 1];
            long long max_second_move = std::max(left_over_top, left_over_bot);
            res = std::min(res, max_second_move);
        }
        
        return res;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{2, 5, 4}, {1, 5, 1}};
    std::cout << sol.gridGame(grid) << std::endl;
    return 0;
}