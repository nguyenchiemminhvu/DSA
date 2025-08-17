/**
https://vjudge.net/contest/690982#problem/B
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int maxSpeedOverLimit(const std::vector<std::pair<int, int>>& road_segments, const std::vector<std::pair<int, int>>& drive_segments)
    {
        int res = 0;

        std::vector<int> road_limit(101, 0);
        int pos = 0;
        for (int i = 0; i < road_segments.size(); i++)
        {
            for (int j = 0; j < road_segments[i].first; j++)
            {
                road_limit[pos++] = road_segments[i].second;
            }
        }

        std::vector<int> drive_history(101, 0);
        pos = 0;
        for (int i = 0; i < drive_segments.size(); i++)
        {
            for (int j = 0; j < drive_segments[i].first; j++)
            {
                drive_history[pos++] = drive_segments[i].second;
            }
        }

        for (int i = 0; i < 100; i++)
        {
            res = std::max(res, drive_history[i] - road_limit[i]);
        }

        return res;
    }
};

int main()
{
    freopen("speeding.in", "r", stdin);
    freopen("speeding.out", "w", stdout);

    Solution sol;

    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> road_segments(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> road_segments[i].first >> road_segments[i].second;
    }

    std::vector<std::pair<int, int>> drive_segments(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> drive_segments[i].first >> drive_segments[i].second;
    }

    std::cout << sol.maxSpeedOverLimit(road_segments, drive_segments) << std::endl;

    return 0;
}