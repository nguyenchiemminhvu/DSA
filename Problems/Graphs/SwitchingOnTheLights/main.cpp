/**
https://vjudge.net/contest/691177#problem/D
https://usaco.org/index.php?page=viewproblem2&cpid=570

Bessie starts in room (1,1), the only room that is initially lit. In some rooms, she will find light switches that she can use to toggle the lights in other rooms.

Please determine the maximum number of rooms Bessie can illuminate.
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <map>
#include <set>

using namespace std;

int BFS(int n, 
        std::map<std::pair<int, int>, std::vector<std::pair<int, int>>>& adj_rooms, 
        std::vector<std::vector<bool>>& visited)
{
    std::vector<int> dir_r = {-1, 1, 0, 0};
    std::vector<int> dir_c = {0, 0, -1, 1};

    std::queue<std::pair<int, int>> Q;
    Q.push({0, 0});

    std::set<std::pair<int, int>> activated;
    activated.insert({0, 0});
    visited[0][0] = true;

    while (!Q.empty())
    {
        std::pair<int, int> cur = Q.front();
        Q.pop();

        int r = cur.first;
        int c = cur.second;

        for (const std::pair<int, int>& adj_room : adj_rooms[{r, c}])
        {
            if (activated.find(adj_room) == activated.end())
            {
                activated.insert(adj_room);

                // if surrounding rooms are already visited, then push this adj_room to Q because it is accessible
                for (int i = 0; i < 4; i++)
                {
                    int adj_r = adj_room.first + dir_r[i];
                    int adj_c = adj_room.second + dir_c[i];
                    if (adj_r >= 0 && adj_r < n && adj_c >= 0 && adj_c < n)
                    {
                        if (visited[adj_r][adj_c])
                        {
                            Q.push(adj_room);
                            break;
                        }
                    }
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            int next_r = r + dir_r[i];
            int next_c = c + dir_c[i];
            if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < n)
            {
                if (!visited[next_r][next_c] && activated.find({next_r, next_c}) != activated.end())
                {
                    visited[next_r][next_c] = true;
                    Q.push({next_r, next_c});
                }
            }
        }
    }

    return activated.size();
}

int main()
{
    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;

    std::map<std::pair<int, int>, std::vector<std::pair<int, int>>> adj_rooms;
    for (int i = 0; i < m; i++)
    {
        int x, y;
        int a, b;
        std::cin >> x >> y >> a >> b;
        adj_rooms[{x - 1, y - 1}].push_back({a - 1, b - 1});
    }

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));
    int max_access = BFS(n, adj_rooms, visited);
    std::cout << max_access << std::endl;

    return 0;
}