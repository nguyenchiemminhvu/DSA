/**
https://vjudge.net/contest/691168#problem/E
https://usaco.guide/problems/cf-cellular-network/solution

You are given n points on the straight line — the positions (x-coordinates) of the cities and m points on the same line — the positions (x-coordinates) of the cellular towers. All towers work in the same way — they provide cellular network for all cities, which are located at the distance which is no more than r from this tower.

Your task is to find minimal r that each city has been provided by cellular network, i.e. for each city there is at least one cellular tower at the distance which is no more than r.
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

bool is_covered(const std::vector<int>& towers, const std::vector<int>& cities, int r)
{
    int it = 0;
    for (int ic = 0; ic < cities.size(); ic++)
    {
        while (it < towers.size() && towers[it] < cities[ic] - r)
        {
            it++;
        }

        if (it == towers.size() || towers[it] > cities[ic] + r)
        {
            return false;
        }
    }

    return true;
}

int main()
{
    int n, m;
    std::cin >> n >> m;
    std::vector<int> cities(n);
    for (int i = 0; i < n; i++)
    {
        int pos;
        std::cin >> pos;
        cities[i] = pos;
    }

    std::vector<int> towers(m);
    for (int i = 0; i < m; i++)
    {
        int pos;
        std::cin >> pos;
        towers[i] = pos;
    }

    std::sort(cities.begin(), cities.end());
    int city_left = cities.front();
    int city_right = cities.back();

    std::sort(towers.begin(), towers.end());
    int tower_left = towers.front();
    int tower_right = towers.back();

    int r_left = 0;
    int r_right = std::max(std::abs(tower_left - city_right), std::abs(tower_right - city_left));
    int r_min = r_right;
    while (r_left <= r_right)
    {
        int r_mid = r_left + (r_right - r_left) / 2;
        if (is_covered(towers, cities, r_mid))
        {
            r_min = r_mid;
            r_right = r_mid - 1;
        }
        else
        {
            r_left = r_mid + 1;
        }
    }

    std::cout << r_min << std::endl;

    return 0;
}