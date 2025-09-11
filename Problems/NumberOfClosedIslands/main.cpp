// https://leetcode.com/problems/number-of-closed-islands/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

static bool fast = []() {
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

const std::vector<int> dir_r = {-1, 1, 0, 0};
const std::vector<int> dir_c = {0, 0, -1, 1};

class Solution
{
public:
    int closedIsland(vector<vector<int>>& grid)
    {
        int m = grid.size();
        int n = grid[0].size();
        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));

        auto f_bfs = [&](int r, int c) -> bool
        {
            std::queue<std::pair<int, int>> Q;
            Q.push({r, c});
            visited[r][c] = true;
            bool res = true;
            while (!Q.empty())
            {
                auto cur = Q.front();
                Q.pop();

                r = cur.first;
                c = cur.second;
                if (r == 0 || c == 0 || r == m - 1 || c == n - 1)
                {
                    res = false;
                }

                for (int i = 0; i < 4; i++)
                {
                    int next_r = r + dir_r[i];
                    int next_c = c + dir_c[i];
                    if (next_r >= 0 && next_r < m && next_c >= 0 && next_c < n)
                    {
                        if (grid[next_r][next_c] == 0 && !visited[next_r][next_c])
                        {
                            visited[next_r][next_c] = true;
                            Q.push({next_r, next_c});
                        }                   
                    }
                }
            }

            return res;
        };

        int count = 0;
        for (int i = 1; i < m - 1; i++)
        {
            for (int j = 1; j < n - 1; j++)
            {
                if (grid[i][j] == 0 && !visited[i][j])
                {
                    if (f_bfs(i, j))
                    {
                        count++;
                    }
                }
            }
        }

        return count;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {
        {1,1,1,1,1,1,1,0},
        {1,0,0,0,0,1,1,0},
        {1,0,1,0,1,1,1,0},
        {1,0,0,0,0,1,0,1},
        {1,1,1,1,1,1,1,0}
    };
    cout << sol.closedIsland(grid) << "\n";
    return 0;
}