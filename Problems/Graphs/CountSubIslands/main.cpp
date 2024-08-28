/**
https://leetcode.com/problems/count-sub-islands/description/

You are given two m x n binary matrices grid1 and grid2 containing only 0's (representing water) and 1's (representing land). An island is a group of 1's connected 4-directionally (horizontal or vertical). Any cells outside of the grid are considered water cells.

An island in grid2 is considered a sub-island if there is an island in grid1 that contains all the cells that make up this island in grid2.

Return the number of islands in grid2 that are considered sub-islands.

Example 1:

Input: grid1 = [[1,1,1,0,0],[0,1,1,1,1],[0,0,0,0,0],[1,0,0,0,0],[1,1,0,1,1]], grid2 = [[1,1,1,0,0],[0,0,1,1,1],[0,1,0,0,0],[1,0,1,1,0],[0,1,0,1,0]]
Output: 3
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island. There are three sub-islands.

Example 2:

Input: grid1 = [[1,0,1,0,1],[1,1,1,1,1],[0,0,0,0,0],[1,1,1,1,1],[1,0,1,0,1]], grid2 = [[0,0,0,0,0],[1,1,1,1,1],[0,1,0,1,0],[0,1,0,1,0],[1,0,0,0,1]]
Output: 2 
Explanation: In the picture above, the grid on the left is grid1 and the grid on the right is grid2.
The 1s colored red in grid2 are those considered to be part of a sub-island. There are two sub-islands.

Constraints:

m == grid1.length == grid2.length
n == grid1[i].length == grid2[i].length
1 <= m, n <= 500
grid1[i][j] and grid2[i][j] are either 0 or 1.
*/

#include <iostream>
#include <vector>
#include <queue>

class Solution
{
public:
    int countSubIslands(std::vector<std::vector<int>>& grid1, std::vector<std::vector<int>>& grid2)
    {
        std::ios_base::sync_with_stdio(false);
        std::cin.tie(nullptr);

        int count = 0;
        int m = grid1.size();
        int n = grid1[0].size();
        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid2[i][j] == 1)
                {
                    count += BFS(grid1, grid2, m, n, i, j);
                }
            }
        }

        return count;
    }
private:
    bool BFS(std::vector<std::vector<int>>& grid1, std::vector<std::vector<int>>& grid2, int m, int n, int r, int c)
    {
        bool isSub = true;

        std::queue<std::pair<int, int>> Q;
        Q.push({r, c});
        grid2[r][c] = 0;

        std::vector<std::pair<int, int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        while (!Q.empty())
        {
            std::pair<int, int> cur = Q.front();
            Q.pop();

            if (grid1[cur.first][cur.second] == 0)
            {
                isSub = false;
            }

            for (std::pair<int, int> dir : directions)
            {
                int newRow = cur.first + dir.first;
                int newCol = cur.second + dir.second;

                if (newRow >= 0 && newRow < m && newCol >= 0 && newCol < n && grid2[newRow][newCol] == 1)
                {
                    Q.push({newRow, newCol});
                    grid2[newRow][newCol] = 0;
                }
            }
        }

        return isSub;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> grid1 = {
        {1,1,1,0,0},
        {0,1,1,1,1},
        {0,0,0,0,0},
        {1,0,0,0,0},
        {1,1,0,1,1}
    };
    std::vector<std::vector<int>> grid2 = {
        {1,1,1,0,0},
        {0,0,1,1,1},
        {0,1,0,0,0},
        {1,0,1,1,0},
        {0,1,0,1,0}
    };
    std::cout << sol.countSubIslands(grid1, grid2) << std::endl;
    return 0;
}