/**
https://vjudge.net/contest/691177#problem/F
https://usaco.guide/problems/usaco-615-milk-pails/solution
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>

using namespace std;

int main()
{
    freopen("pails.in", "r", stdin);
    freopen("pails.out", "w", stdout);

    int x, y, k, m;
    std::cin >> x >> y >> k >> m;

    int min_diff = m;

    std::queue<std::vector<int>> Q; // {a, b, steps}
    Q.push({0, 0, 0});

    std::set<std::vector<int>> visited;
    visited.insert({0, 0});

    while (!Q.empty())
    {
        std::vector<int> cur = Q.front();
        Q.pop();

        int a = cur[0];
        int b = cur[1];
        int step = cur[2];

        min_diff = std::min(min_diff, std::abs((a + b) - m));

        if (step == k)
        {
            continue;
        }

        std::vector<std::vector<int>> next_status = {
            {x, b},
            {a, y},
            {0, b},
            {a, 0},
            {std::max(0, a - (y - b)), std::min(y, a + b)},
            {std::min(x, a + b), std::max(0, b - (x - a))}
        };

        for (const std::vector<int>& next : next_status)
        {
            if (visited.find(next) == visited.end())
            {
                visited.insert(next);
                Q.push({next[0], next[1], step + 1});
            }
        }
    }

    std::cout << min_diff << std::endl;

    return 0;
}