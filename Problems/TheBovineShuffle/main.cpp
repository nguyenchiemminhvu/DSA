/**
https://vjudge.net/contest/690982#problem/D
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <algorithm>

using namespace std;

class Solution
{
public:
    void bovineShuffle(std::vector<int>& cows, const std::vector<int>& shuffle)
    {
        std::vector<int> buffer(cows.begin(), cows.end());
        for (int i = 0; i < cows.size(); i++)
        {
            cows[i] = buffer[shuffle[i] - 1];
        }
    }
};

int main()
{
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<int> shuffle(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> shuffle[i];
    }

    std::vector<int> cows(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> cows[i];
    }

    Solution sol;
    for (int t = 0; t < 3; t++)
    {
        sol.bovineShuffle(cows, shuffle);
    }

    for (int i = 0; i < n; i++)
    {
        std::cout << cows[i] << std::endl;
    }

    return 0;
}