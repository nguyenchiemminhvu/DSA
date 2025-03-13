/**
https://vjudge.net/contest/691177#problem/H
https://usaco.guide/problems/usaco-713-why-did-the-cow-cross-the-road-iii/solution
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <set>
#include <unordered_map>

using namespace std;

int BFS(int n, 
         int start_r, 
         int start_c, 
         const std::set<std::vector<int>>& cow_pos, 
         const std::vector<std::vector<int>>& roads, 
         std::vector<std::vector<bool>>& visited)
{
    std::vector<int> dir_r = {-1, 1, 0, 0};
    std::vector<int> dir_c = {0, 0, -1, 1};

    int count = 0;
    std::queue<std::pair<int, int>> Q;
    Q.push({start_r, start_c});
    visited[start_r][start_c] = true;

    while (!Q.empty())
    {
        std::pair<int, int> cur = Q.front();
        Q.pop();

        int r = cur.first;
        int c = cur.second;
        if (cow_pos.find({r, c}) != cow_pos.end())
        {
            count++;
        }

        for (int i = 0; i < 4; i++)
        {
            int next_r = r + dir_r[i];
            int next_c = c + dir_c[i];
            if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < n && !visited[next_r][next_c])
            {
                // search if {r, c} and {next_r, next_c} appears in the vector of roads
                bool road_exists = false;
                for (const auto& road : roads)
                {
                    if ((road[0] == r && road[1] == c && road[2] == next_r && road[3] == next_c) ||
                        (road[0] == next_r && road[1] == next_c && road[2] == r && road[3] == c))
                    {
                        road_exists = true;
                        break;
                    }
                }

                if (!road_exists)
                {
                    Q.push({next_r, next_c});
                    visited[next_r][next_c] = true;
                }
            }
        }
    }

    return count;
}

int main()
{
    freopen("countcross.in", "r", stdin);
    freopen("countcross.out", "w", stdout);

    int n, k, r;
    std::cin >> n >> k >> r;

    std::vector<std::vector<int>> roads;
    for (int i = 0; i < r; i++)
    {
        int ar, ac;
        int br, bc;
        std::cin >> ar >> ac >> br >> bc;
        roads.push_back({ar - 1, ac - 1, br - 1, bc - 1});
    }

    std::set<std::vector<int>> cow_pos;
    for (int i = 0; i < k; i++)
    {
        int r, c;
        std::cin >> r >> c;
        cow_pos.insert({r - 1, c - 1});
    }

    std::vector<std::vector<bool>> visited(n, std::vector<bool>(n, false));

    std::unordered_map<int, int> cows_per_region;
    int region_id = 0;

    for (const std::vector<int>& cow : cow_pos)
    {
        int r = cow[0];
        int c = cow[1];
        if (!visited[r][c])
        {
            int count = BFS(n, r, c, cow_pos, roads, visited);
            cows_per_region[region_id] = count;
            region_id++;
        }
    }

    std::vector<std::vector<int>> regions;
    for (const auto& p : cows_per_region)
    {
        regions.push_back({p.first, p.second});
    }

    int pairs = 0;
    for (int i = 0; i < regions.size(); i++)
    {
        for (int j = i + 1; j < regions.size(); j++)
        {
            pairs += (regions[i][1] * regions[j][1]);
        }
    }

    std::cout << pairs << std::endl;

    return 0;   
}