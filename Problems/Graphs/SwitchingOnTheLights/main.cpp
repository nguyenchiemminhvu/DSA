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

int count_lit = 1;
int N, M;
std::vector<std::vector<bool>> visited(100, std::vector<bool>(100, false));
std::vector<std::vector<bool>> lit(100, std::vector<bool>(100, false));
std::map<std::pair<int, int>, std::set<std::pair<int, int>>> connections;

int dir_r[] = {-1, 0, 1, 0};
int dir_c[] = {0, 1, 0, -1};

void DFS(int r, int c)
{
    if (r < 0 || r >= N || c < 0 || c >= N)
    {
        return;
    }

    if (visited[r][c])
    {
        return;
    }

    if (!lit[r][c])
    {
        return;
    }

    bool connected = false;
    for (int i = 0; i < 4; i++)
    {
        int next_r = r + dir_r[i];
        int next_c = c + dir_c[i];
        if (next_r >= 0 && next_r < N && next_c >= 0 && next_c < N)
        {
            if (visited[next_r][next_c])
            {
                connected = true;
                break;
            }
        }
    }

    if (!connected && !(r == 0 && c == 0))
    {
        return;
    }

    visited[r][c] = true;

    for (int i = 0; i < 4; i++)
    {
        int next_r = r + dir_r[i];
        int next_c = c + dir_c[i];
        DFS(next_r, next_c);
    }

    for (const std::pair<int, int>& room : connections[{r, c}])
    {
        int room_r = room.first;
        int room_c = room.second;
        if (!lit[room_r][room_c])
        {
            count_lit++;
        }

        lit[room_r][room_c] = true;
        DFS(room_r, room_c);
    }
}

int main()
{
    freopen("lightson.in", "r", stdin);
    freopen("lightson.out", "w", stdout);

    std::cin >> N >> M;
    for (int i = 0; i < M; i++)
    {
        int x, y;
        int a, b;
        std::cin >> x >> y >> a >> b;
        connections[{x - 1, y - 1}].insert({a - 1, b - 1});
    }

    lit[0][0] = true;
    DFS(0, 0);
    std::cout << count_lit << std::endl;

    return 0;
}