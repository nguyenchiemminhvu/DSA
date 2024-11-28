/**
https://leetcode.com/problems/find-a-safe-walk-through-a-grid/

You are given an m x n binary matrix grid and an integer health.

You start on the upper-left corner (0, 0) and would like to get to the lower-right corner (m - 1, n - 1).

You can move up, down, left, or right from one cell to another adjacent cell as long as your health remains positive.

Cells (i, j) with grid[i][j] = 1 are considered unsafe and reduce your health by 1.

Return true if you can reach the final cell with a health value of 1 or more, and false otherwise.

Example 1:

Input: grid = [[0,1,0,0,0],[0,1,0,1,0],[0,0,0,1,0]], health = 1

Output: true

Explanation:

The final cell can be reached safely by walking along the gray cells below.


Example 2:

Input: grid = [[0,1,1,0,0,0],[1,0,1,0,0,0],[0,1,1,1,0,1],[0,0,1,0,1,0]], health = 3

Output: false

Explanation:

A minimum of 4 health points is needed to reach the final cell safely.

Example 3:

Input: grid = [[1,1,1],[1,0,1],[1,1,1]], health = 5

Output: true

Explanation:

The final cell can be reached safely by walking along the gray cells below.

Any path that does not go through the cell (1, 1) is unsafe since your health will drop to 0 when reaching the final cell.

Constraints:

m == grid.length
n == grid[i].length
1 <= m, n <= 50
2 <= m * n
1 <= health <= m + n
grid[i][j] is either 0 or 1.
*/

#include <iostream>
#include <vector>
#include <queue>
#include <deque>
#include <algorithm>

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
    dist[0][0] = matrix[0][0]; 

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
    bool findSafeWalk(vector<vector<int>>& grid, int health)
    {
        return zeroOneBFS(grid) < health;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> grid = {
        {0,1,0,0,0},{0,1,0,1,0},{0,0,0,1,0}
    };
    int h = 1;
    std::cout << sol.findSafeWalk(grid, h) << std::endl;
    return 0;
}