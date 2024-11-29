/**
https://leetcode.com/problems/minimum-time-to-visit-a-cell-in-a-grid/description/

You are given a m x n matrix grid consisting of non-negative integers where grid[row][col] represents the minimum time required to be able to visit the cell (row, col), which means you can visit the cell (row, col) only when the time you visit it is greater than or equal to grid[row][col].

You are standing in the top-left cell of the matrix in the 0th second, and you must move to any adjacent cell in the four directions: up, down, left, and right. Each move you make takes 1 second.

Return the minimum time required in which you can visit the bottom-right cell of the matrix. If you cannot visit the bottom-right cell, then return -1.

Example 1:

Input: grid = [[0,1,3,2],[5,1,2,5],[4,3,8,6]]
Output: 7
Explanation: One of the paths that we can take is the following:
- at t = 0, we are on the cell (0,0).
- at t = 1, we move to the cell (0,1). It is possible because grid[0][1] <= 1.
- at t = 2, we move to the cell (1,1). It is possible because grid[1][1] <= 2.
- at t = 3, we move to the cell (1,2). It is possible because grid[1][2] <= 3.
- at t = 4, we move to the cell (1,1). It is possible because grid[1][1] <= 4.
- at t = 5, we move to the cell (1,2). It is possible because grid[1][2] <= 5.
- at t = 6, we move to the cell (1,3). It is possible because grid[1][3] <= 6.
- at t = 7, we move to the cell (2,3). It is possible because grid[2][3] <= 7.
The final time is 7. It can be shown that it is the minimum time possible.

Example 2:

Input: grid = [[0,2,4],[3,2,1],[1,0,4]]
Output: -1
Explanation: There is no path from the top left to the bottom-right cell.

Constraints:

m == grid.length
n == grid[i].length
2 <= m, n <= 1000
4 <= m * n <= 105
0 <= grid[i][j] <= 105
grid[0][0] == 0
*/

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

static bool fastIO = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int minimumTime(vector<vector<int>>& grid)
    {
        int dx[] = {0, -1, 0, 1};
        int dy[] = {-1, 0, 1, 0};

        if (grid[0][1] > 1 && grid[1][0] > 1)
        {
            return -1;
        }

        int rows = grid.size();
        int cols = grid[0].size();

        std::vector<std::vector<int>> costed_time(rows, std::vector<int>(cols, INT_MAX));
        costed_time[0][0] = 0;

        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;
        pq.push({0, 0, 0});

        while (!pq.empty())
        {
            std::vector<int> cur = pq.top();
            pq.pop();

            int cur_time = cur[0];
            int r = cur[1];
            int c = cur[2];

            if (r == rows - 1 && c == cols - 1)
            {
                return cur_time;
            }

            for (int i = 0; i < 4; i++)
            {
                int next_r = r + dx[i];
                int next_c = c + dy[i];

                if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols)
                {
                    int next_time = INT_MAX;
                    int diff_time = grid[next_r][next_c] - cur_time;
                    if (cur_time >= grid[next_r][next_c])
                    {
                        next_time = cur_time + 1;
                    }
                    else if (diff_time % 2 == 1)
                    {
                        next_time = grid[next_r][next_c];
                    }
                    else
                    {
                        next_time = grid[next_r][next_c] + 1;
                    }

                    if (next_time < costed_time[next_r][next_c])
                    {
                        costed_time[next_r][next_c] = next_time;
                        pq.push({next_time, next_r, next_c});
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
    std::vector<std::vector<int>> grid = {
        {0,1,3,2},
        {5,1,2,5},
        {4,3,8,6},
    };
    std::cout << sol.minimumTime(grid) << std::endl;

    return 0;
}