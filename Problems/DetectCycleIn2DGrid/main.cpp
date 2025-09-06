// https://leetcode.com/problems/detect-cycles-in-2d-grid/

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
public:
    bool containsCycle(vector<vector<char>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        vector<vector<bool>> visited(m, vector<bool>(n, false));

        for (int i = 0; i < m; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (!visited[i][j])
                {
                    if (dfs(grid, visited, i, j, -1, -1, grid[i][j]))
                        return true;
                }
            }
        }
        return false;
    }

private:
    vector<int> dir_r = {-1, 1, 0, 0};
    vector<int> dir_c = {0, 0, -1, 1};

    bool dfs(const vector<vector<char>>& grid,
             vector<vector<bool>>& visited,
             int r, int c,
             int pr, int pc,
             char val)
    {
        int m = grid.size();
        int n = grid[0].size();

        visited[r][c] = true;

        for (int d = 0; d < 4; d++)
        {
            int nr = r + dir_r[d];
            int nc = c + dir_c[d];

            if (nr < 0 || nr >= m || nc < 0 || nc >= n)
                continue;

            if (grid[nr][nc] != val)
                continue;

            if (!visited[nr][nc])
            {
                if (dfs(grid, visited, nr, nc, r, c, val))
                    return true;
            }
            else if (!(nr == pr && nc == pc))
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;
    vector<vector<char>> grid = {
        {'a', 'a', 'a', 'a'},
        {'a', 'b', 'b', 'a'},
        {'a', 'b', 'b', 'a'},
        {'a', 'a', 'a', 'a'}
    };
    cout << (sol.containsCycle(grid) ? "true" : "false") << endl;
    return 0;
}