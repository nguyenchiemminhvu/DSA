/**
https://leetcode.com/problems/minimum-obstacle-removal-to-reach-corner/description/

You are given a 0-indexed 2D integer array grid of size m x n. Each cell has one of two values:

0 represents an empty cell,
1 represents an obstacle that may be removed.
You can move up, down, left, or right from and to an empty cell.

Return the minimum number of obstacles to remove so you can move from the upper left corner (0, 0) to the lower right corner (m - 1, n - 1).

Example 1:

Input: grid = [[0,1,1],[1,1,0],[1,1,0]]
Output: 2
Explanation: We can remove the obstacles at (0, 1) and (0, 2) to create a path from (0, 0) to (2, 2).
It can be shown that we need to remove at least 2 obstacles, so we return 2.
Note that there may be other ways to remove 2 obstacles to create a path.

Example 2:

Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]]
Output: 0
Explanation: We can move from (0, 0) to (2, 4) without removing any obstacles, so we return 0.

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 105
2 <= m * n <= 105
grid[i][j] is either 0 or 1.
grid[0][0] == grid[m - 1][n - 1] == 0
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <deque>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

const int dx[] = {-1, 1, 0, 0};
const int dy[] = {0, 0, -1, 1};

int zeroOneBFS(const vector<vector<int>>& matrix)
{
    int m = matrix.size();
    int n = matrix[0].size();

    if (m == 0 || n == 0) return -1;

    vector<vector<int>> dist(m, vector<int>(n, numeric_limits<int>::max()));
    dist[0][0] = 0; 

    deque<pair<int, int>> dq;
    dq.push_front({0, 0});

    while (!dq.empty())
    {
        std::pair<int, int> cur = dq.front();
        dq.pop_front();
        int x = cur.first;
        int y = cur.second;

        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < m && ny >= 0 && ny < n)
            {
                int new_cost = dist[x][y] + matrix[nx][ny];

                if (new_cost < dist[nx][ny])
                {
                    dist[nx][ny] = new_cost;

                    if (matrix[nx][ny] == 0)
                    {
                        dq.push_front({nx, ny});
                    }
                    else
                    {
                        dq.push_back({nx, ny});
                    }
                }
            }
        }
    }

    return dist[m - 1][n - 1];
}

class Solution
{
public:
    int minimumObstacles(vector<vector<int>>& grid)
    {
        return zeroOneBFS(grid);    
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> grid = {
        {0, 1, 1},
        {1, 1, 0},
        {1, 1, 0}
    };
    std::cout << sol.minimumObstacles(grid) << std::endl;
    return 0;
}