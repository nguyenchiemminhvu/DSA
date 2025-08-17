/**
https://leetcode.com/problems/minimum-cost-to-make-at-least-one-valid-path-in-a-grid

Given an m x n grid. Each cell of the grid has a sign pointing to the next cell you should visit if you are currently in this cell. The sign of grid[i][j] can be:

1 which means go to the cell to the right. (i.e go from grid[i][j] to grid[i][j + 1])
2 which means go to the cell to the left. (i.e go from grid[i][j] to grid[i][j - 1])
3 which means go to the lower cell. (i.e go from grid[i][j] to grid[i + 1][j])
4 which means go to the upper cell. (i.e go from grid[i][j] to grid[i - 1][j])
Notice that there could be some signs on the cells of the grid that point outside the grid.

You will initially start at the upper left cell (0, 0). A valid path in the grid is a path that starts from the upper left cell (0, 0) and ends at the bottom-right cell (m - 1, n - 1) following the signs on the grid. The valid path does not have to be the shortest.

You can modify the sign on a cell with cost = 1. You can modify the sign on a cell one time only.

Return the minimum cost to make the grid have at least one valid path.

Example 1:

Input: grid = [[1,1,1,1],[2,2,2,2],[1,1,1,1],[2,2,2,2]]
Output: 3
Explanation: You will start at point (0, 0).
The path to (3, 3) is as follows. (0, 0) --> (0, 1) --> (0, 2) --> (0, 3) change the arrow to down with cost = 1 --> (1, 3) --> (1, 2) --> (1, 1) --> (1, 0) change the arrow to down with cost = 1 --> (2, 0) --> (2, 1) --> (2, 2) --> (2, 3) change the arrow to down with cost = 1 --> (3, 3)
The total cost = 3.
Example 2:

Input: grid = [[1,1,3],[3,2,2],[1,1,4]]
Output: 0
Explanation: You can follow the path from (0, 0) to (2, 2).

Example 3:

Input: grid = [[1,2],[4,3]]
Output: 1

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 100
1 <= grid[i][j] <= 4
 */

#include <iostream>
#include <vector>
#include <queue>
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
    int minCost(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();

        std::vector<std::pair<int, int>> directions = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

        std::priority_queue<std::tuple<int, int, int>, std::vector<std::tuple<int, int, int>>, std::greater<std::tuple<int, int, int>>> Q; // {cost, r, c}
        Q.push({0, 0, 0});

        std::vector<std::vector<int>> dist(m, std::vector<int>(n, INT_MAX));
        dist[0][0] = 0;

        while (!Q.empty())
        {
            std::tuple<int, int, int> cur = Q.top();
            Q.pop();
            int cost = std::get<0>(cur);
            int r = std::get<1>(cur);
            int c = std::get<2>(cur);

            if (r == m - 1 && c == n - 1)
            {
                return cost;
            }

            if (cost > dist[r][c])
            {
                continue;
            }

            for (int i = 0; i < 4; i++)
            {
                int next_r = r + directions[i].first;
                int next_c = c + directions[i].second;
                int next_cost = cost;
                if (next_r >= 0 && next_r < m && next_c >= 0 && next_c < n)
                {
                    if (grid[r][c] != (i + 1))
                    {
                        next_cost++;
                    }

                    if (next_cost < dist[next_r][next_c])
                    {
                        dist[next_r][next_c] = next_cost;
                        Q.push({next_cost, next_r, next_c});
                    }
                }
            }
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{1, 1, 1, 1}, {2, 2, 2, 2}, {1, 1, 1, 1}, {2, 2, 2, 2}};
    std::cout << sol.minCost(grid) << std::endl;
    return 0;
}