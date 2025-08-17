/**
https://vjudge.net/contest/690982#problem/J
https://usaco.org/index.php?page=viewproblem2&cpid=593
 */

#include <iostream>
#include <vector>
#include <cstdio>
#include <map>
#include <unordered_map>
#include <tuple>
#include <climits>

using namespace std;

class Solution
{
    std::vector<int> dir_row = {0, 0, 1, -1}; // right, left, down, up
    std::vector<int> dir_col = {1, -1, 0, 0}; // right, left, down, up
    std::unordered_map<char, int> dir_map = {{'E', 0}, {'W', 1}, {'S', 2}, {'N', 3}};

public:
    int mowingTheField(const std::vector<std::tuple<char, int>>& moves)
    {
        int r = 0, c = 0;

        std::map<std::pair<int, int>, int> visited;
        visited[{r, c}] = 0;
        int timestamp = 0;
        int min_time_diff = INT_MAX;

        for (int i = 0; i < moves.size(); i++)
        {
            char dir = std::get<0>(moves[i]);
            int steps = std::get<1>(moves[i]);

            for (int j = 0; j < steps; j++)
            {
                r += dir_row[dir_map[dir]];
                c += dir_col[dir_map[dir]];
                timestamp++;

                if (visited.find({r, c}) != visited.end())
                {
                    int time_diff = timestamp - visited[{r, c}];
                    min_time_diff = min(min_time_diff, time_diff);
                }

                visited[{r, c}] = timestamp;
            }
        }

        return (min_time_diff == INT_MAX) ? -1 : min_time_diff;
    }
};

int main()
{
    freopen("mowing.in", "r", stdin);
    freopen("mowing.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<std::tuple<char, int>> moves(n);
    for (int i = 0; i < n; i++)
    {
        char dir;
        int steps;
        std::cin >> dir >> steps;
        moves[i] = std::make_tuple(dir, steps);
    }

    Solution sol;
    std::cout << sol.mowingTheField(moves) << std::endl;

    return 0;
}