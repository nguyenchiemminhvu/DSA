/**
https://vjudge.net/contest/691177#problem/B
https://usaco.guide/problems/cf-solve-the-maze/solution

A person can move to a cell only if it shares a side with their current cell and does not contain a wall. Vivek wants to block some of the empty cells by replacing them with walls in such a way, that all the good people are able to escape, while none of the bad people are able to. A cell that initially contains 'G' or 'B' cannot be blocked and can be travelled through.

Help him determine if there exists a way to replace some (zero or more) empty cells with walls to satisfy the above conditions.

It is guaranteed that the cell (n,m) is empty. Vivek can also block this cell.
*/

#include <iostream>
#include <string>
#include <vector>
#include <set>
#include <queue>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
    const std::vector<int> dir_r = {-1, 1, 0, 0};
    const std::vector<int> dir_c = {0, 0, -1, 1};

public:
    bool solveTheMaze(std::vector<std::string>& maze, 
        std::set<std::pair<int, int>>& good_locations, 
        std::set<std::pair<int, int>>& bad_locations)
    {
        int n = maze.size();
        int m = maze[0].size();

        // if there is no good person, just block the exit cell
        if (good_locations.size() == 0)
        {
            return true;
        }

        // make all cells surrounding each bad person a wall cell
        for (const auto& bad_pos : bad_locations)
        {
            for (int i = 0; i < 4; i++)
            {
                int next_r = bad_pos.first + dir_r[i];
                int next_c = bad_pos.second + dir_c[i];
                if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < m)
                {
                    if (next_r == n - 1 && next_c == m - 1)
                    {
                        return false;
                    }

                    if (maze[next_r][next_c] == 'G')
                    {
                        return false;
                    }

                    maze[next_r][next_c] = '#';
                }
            }
        }

        // BFS from the exit cell, count the number of reached good persons
        int count_good = BFS(maze, n - 1, m - 1);
        if (count_good < good_locations.size())
        {
            return false;
        }

        return true;
    }
private:
    int BFS(const std::vector<std::string>& maze, int exit_r, int exit_c)
    {
        int count_good = 0;

        int n = maze.size();
        int m = maze[0].size();

        std::queue<std::pair<int, int>> Q;
        Q.push({exit_r, exit_c});

        std::vector<std::vector<bool>> visited(n, std::vector<bool>(m, false));
        visited[exit_r][exit_c] = true;

        while (!Q.empty())
        {
            std::pair<int, int> cur = Q.front();
            Q.pop();

            if (maze[cur.first][cur.second] == 'G')
            {
                count_good++;
            }

            for (int i = 0; i < 4; i++)
            {
                int next_r = cur.first + dir_r[i];
                int next_c = cur.second + dir_c[i];
                if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < m)
                {
                    if (maze[next_r][next_c] != '#' && !visited[next_r][next_c])
                    {
                        visited[next_r][next_c] = true;
                        Q.push({next_r, next_c});
                    }
                }
            }
        }

        return count_good;
    }
};

int main()
{
    int t;
    std::cin >> t;
    while (t)
    {
        t--;

        int n, m;
        std::cin >> n >> m;

        std::vector<std::string> maze(n);

        std::set<std::pair<int, int>> good_locations;
        std::set<std::pair<int, int>> bad_locations;
        for (int i = 0; i < n; i++)
        {
            std::string row;
            std::cin >> row;
            maze[i].swap(row);

            for (int j = 0; j < maze[i].length(); j++)
            {
                if (maze[i][j] == 'G')
                {
                    good_locations.insert({i, j});
                }
                else if (maze[i][j] == 'B')
                {
                    bad_locations.insert({i, j});
                }
            }
        }

        Solution sol;
        if (sol.solveTheMaze(maze, good_locations, bad_locations))
        {
            std::cout << "Yes" << std::endl;
        }
        else
        {
            std::cout << "No" << std::endl;
        }
    }
    return 0;
}