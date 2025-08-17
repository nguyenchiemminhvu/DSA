/**
https://vjudge.net/contest/691177#problem/I
https://usaco.org/index.php?page=viewproblem2&cpid=860

With plenty of free time on their hands (or rather, hooves), the cows on Farmer John's farm often pass the time by playing video games. One of their favorites is based on a popular human video game called Puyo Puyo; the cow version is of course called Mooyo Mooyo.
The game of Mooyo Mooyo is played on a tall narrow grid N cells tall (1≤N≤100) and 10 cells wide. Here is an example with N=6:

0000000000
0000000300
0054000300
1054502230
2211122220
1111111223

Each cell is either empty (indicated by a 0), or a haybale in one of nine different colors (indicated by characters 1..9). Gravity causes haybales to fall downward, so there is never a 0 cell below a haybale.

Two cells belong to the same connected region if they are directly adjacent either horizontally or vertically, and they have the same nonzero color. Any time a connected region exists with at least K cells, its haybales all disappear, turning into zeros. If multiple such connected regions exist at the same time, they all disappear simultaneously. Afterwards, gravity might cause haybales to fall downward to fill some of the resulting cells that became zeros. In the resulting configuration, there may again be connected regions of size at least K cells. If so, they also disappear (simultaneously, if there are multiple such regions), then gravity pulls the remaining cells downward, and the process repeats until no connected regions of size at least K exist.

Given the state of a Mooyo Mooyo board, please output a final picture of the board after these operations have occurred.
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

void BFS(int n, 
         int start_r, 
         int start_c, 
         const std::vector<std::string>& grid, 
         std::vector<std::vector<bool>>& visited, 
         std::vector<std::pair<int, int>>& component)
{
    std::vector<int> dir_r = {-1, 1, 0, 0};
    std::vector<int> dir_c = {0, 0, -1, 1};

    std::queue<std::pair<int, int>> Q;
    Q.push({start_r, start_c});
    visited[start_r][start_c] = true;
    component.push_back({start_r, start_c});

    while (!Q.empty())
    {
        std::pair<int, int> cur = Q.front();
        Q.pop();

        int r = cur.first;
        int c = cur.second;
        for (int i = 0; i < 4; i++)
        {
            int next_r = r + dir_r[i];
            int next_c = c + dir_c[i];
            if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < 10 
            && !visited[next_r][next_c]
            && grid[next_r][next_c] == grid[start_r][start_c])
            {
                Q.push({next_r, next_c});
                visited[next_r][next_c] = true;
                component.push_back({next_r, next_c});
            }
        }
    }
}

int main()
{
    freopen("mooyomooyo.in", "r", stdin);
    freopen("mooyomooyo.out", "w", stdout);

    int n, k;
    std::cin >> n >> k;

    std::vector<std::string> grid(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> grid[i];
    }

    while (true)
    {
        std::vector<std::vector<bool>> visited(n, std::vector<bool>(10, false));
        std::vector<std::vector<std::pair<int, int>>> connected_components;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < 10; j++)
            {
                if (!visited[i][j] && grid[i][j] != '0')
                {
                    std::vector<std::pair<int, int>> component;
                    BFS(n, i, j, grid, visited, component);
                    if (component.size() >= k)
                    {
                        connected_components.push_back(component);
                    }
                }
            }
        }

        if (connected_components.empty())
        {
            break;
        }

        for (const std::vector<std::pair<int, int>>& component : connected_components)
        {
            for (const std::pair<int, int>& pos : component)
            {
                int r = pos.first;
                int c = pos.second;
                grid[r][c] = '0';
            }
        }

        // simulate gravity effect
        for (int c = 0; c < 10; c++)
        {
            int empty_row = n - 1;
            for (int r = n - 1; r >= 0; r--)
            {
                if (grid[r][c] != '0')
                {
                    if (r != empty_row)
                    {
                        grid[empty_row][c] = grid[r][c];
                        grid[r][c] = '0';
                    }
                    empty_row--;
                }
            }
        }
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << grid[i] << std::endl;
    }

    return 0;
}