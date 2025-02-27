/**
https://vjudge.net/contest/690988#problem/F
https://usaco.org/index.php?page=viewproblem2&cpid=720

Farmer John's cows are trying to learn to cross the road effectively. Remembering the old "why did the chicken cross the road?" joke, they figure the chickens must be experts on crossing the road, and go off in search of chickens to help them.
As it turns out, chickens are very busy creatures and have limited time to help the cows. There are C chickens on the farm (1≤C≤20,000), conveniently numbered 1…C, and each chicken i is only willing to help a cow at precisely time Ti. The cows, never in a hurry, have more flexibility in their schedules. There are N cows on the farm (1≤N≤20,000), conveniently numbered 1…N, where cow j is able to cross the road between time A and time B. Figuring the "buddy system" is the best way to proceed, each cow j would ideally like to find a chicken i to help her cross the road; in order for their schedules to be compatible, i and j must satisfy. If each cow can be paired with at most one chicken and each chicken with at most one cow, please help compute the maximum number of cow-chicken pairs that can be constructed.
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution
{
public:
    int maxCowChickenPairs(std::vector<int>& chickenTimes, std::vector<std::pair<int, int>>& cowTimes)
    {
        std::sort(chickenTimes.begin(), chickenTimes.end());
        std::sort(cowTimes.begin(), cowTimes.end(), [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
            return a.second < b.second;
        });

        int maxPairs = 0;

        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;

        for (int i = 0; i < cowTimes.size(); i++)
        {

        }

        return maxPairs;
    }
};

int main()
{
    // freopen("helpcross.in", "r", stdin);
    // freopen("helpcross.out", "w", stdout);

    int c, n;
    std::cin >> c >> n;
    std::vector<int> chickenTimes(c);
    for (int i = 0; i < c; i++)
    {
        int t;
        std::cin >> t;
        chickenTimes[i] = t;
    }

    std::vector<std::pair<int, int>> cowTimes(n);
    for (int i = 0; i < n; i++)
    {
        int a, b;
        std::cin >> a >> b;
        cowTimes[i] = std::make_pair(a, b);
    }

    Solution sol;
    std::cout << sol.maxCowChickenPairs(chickenTimes, cowTimes) << std::endl;

    return 0;
}