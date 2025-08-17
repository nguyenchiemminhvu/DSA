/**
https://vjudge.net/contest/690982#problem/E
 */

#include <iostream>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution
{
public:
    int minimizeBucketList(const std::vector<std::vector<int>>& cows)
    {
        int n = cows.size();
        std::vector<std::tuple<int, int, int>> timestamps;
        for (int i = 0; i < n; i++)
        {
            timestamps.push_back(std::make_tuple(cows[i][0], cows[i][2], 1));
            timestamps.push_back(std::make_tuple(cows[i][1], cows[i][2], -1));
        }
        std::sort(timestamps.begin(), timestamps.end(), [](auto& a, auto& b) {
            return std::get<0>(a) < std::get<0>(b);
        });

        int res = 0;
        int cur_buckets = 0;
        for (int i = 0; i < timestamps.size(); i++)
        {
            std::tuple<int, int, int>& timestamp = timestamps[i];
            int num_bucket = std::get<1>(timestamp) * std::get<2>(timestamp);
            cur_buckets += num_bucket;
            res = std::max(res, cur_buckets);
        }

        return res;
    }
};

int main()
{
    freopen("blist.in", "r", stdin);
    freopen("blist.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<std::vector<int>> cows(n);
    for (int i = 0; i < n; i++)
    {
        int s, t;
        int b;
        std::cin >> s >> t >> b;
        cows[i].push_back(s);
        cows[i].push_back(t);
        cows[i].push_back(b);
    }

    Solution sol;
    std::cout << sol.minimizeBucketList(cows) << std::endl;

    return 0;
}