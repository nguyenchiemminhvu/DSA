/**
https://vjudge.net/contest/691177#problem/A
https://usaco.org/index.php?page=viewproblem2&cpid=895

Farmer John would like to find the area and perimeter of the blob of ice cream having the largest area. The area of a blob is just the number of '#' characters that are part of the blob. If multiple blobs tie for the largest area, he wants to know the smallest perimeter among them. 
 */

#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

std::pair<int, int> BFS(const std::vector<std::string>& grid, int start_r, int start_c, std::vector<std::vector<bool>>& visited)
{
    int n = grid.size();
    std::vector<int> dir_r = {-1, 1, 0, 0};
    std::vector<int> dir_c = {0, 0, -1, 1};

    std::queue<std::pair<int, int>> Q;
    Q.push({start_r, start_c});

    visited[start_r][start_c] = true;

    int total_side = 0;
    int total_area = 0;
    while (!Q.empty())
    {
        std::pair<int, int> cur = Q.front();
        Q.pop();

        total_area++;
        int cur_r = cur.first;
        int cur_c = cur.second;

        int side = 4;
        for (int i = 0; i < 4; i++)
        {
            int next_r = cur_r + dir_r[i];
            int next_c = cur_c + dir_c[i];

            if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < n)
            {
                if (grid[next_r][next_c] == '#')
                {
                    side--;
                    if (!visited[next_r][next_c])
                    {
                        Q.push({next_r, next_c});
                        visited[next_r][next_c] = true;
                    }
                }
            }
        }

        total_side += side;
    }

    return {total_area, total_side};
}

int main()
{
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);

    int n;
    std::cin >> n;

    std::vector<std::string> grid(n);
    for (int i = 0; i < n; i++)
    {
        std::string line;
        std::cin >> line;
        grid[i].swap(line);
    }

    int max_area = INT_MIN;
    int min_p_of_max_area = INT_MAX;
    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (grid[i][j] == '#' && !visited[i][j])
            {
                std::pair<int, int> ap = BFS(grid, i, j, visited);
                if (max_area <= ap.first)
                {
                    max_area = ap.first;
                    min_p_of_max_area = ap.second;
                }
                else if (max_area == ap.first)
                {
                    min_p_of_max_area = std::min(min_p_of_max_area, ap.second);
                }
            }
        }
    }

    std::cout << max_area << " " << min_p_of_max_area << std::endl;

    return 0;
}