/**
https://vjudge.net/contest/691168#problem/I
https://usaco.guide/problems/usaco-643-diamond-collector/solution

Bessie the cow, always a fan of shiny objects, has taken up a hobby of mining diamonds in her spare time! She has collected N diamonds (N≤50,000) of varying sizes, and she wants to arrange some of them in a pair of display cases in the barn.
Since Bessie wants the diamonds in each of the two cases to be relatively similar in size, she decides that she will not include two diamonds in the same case if their sizes differ by more than K (two diamonds can be displayed together in the same case if their sizes differ by exactly K). Given K, please help Bessie determine the maximum number of diamonds she can display in both cases together.
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Solution
{
public:
    long long maxDiamondOnTwoCases(std::vector<long long>& diamonds, long long K)
    {
        long long res = 0LL;
        long long n = diamonds.size();
        std::sort(diamonds.begin(), diamonds.end());

        std::vector<long long> canTakeFromLeft(n, 0);
        for (long long left = 0; left < n; left++)
        {
            long long right = left;
            while (right < n && diamonds[right] - diamonds[left] <= K)
            {
                right++;
            }

            canTakeFromLeft[left] = right - left;
        }

        std::vector<long long> maxTakeFromRight(n + 1, 0);
        maxTakeFromRight[n] = 0;
        for (long long i = n - 1; i >= 0; i--)
        {
            maxTakeFromRight[i] = std::max(maxTakeFromRight[i + 1], canTakeFromLeft[i]);
        }

        for (long long left = 0; left < n; left++)
        {
            long long right = left + canTakeFromLeft[left];
            res = std::max(res, canTakeFromLeft[left] + maxTakeFromRight[right]);
        }

        return res;
    }
};

int main()
{
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);

    long long n, k;
    std::cin >> n >> k;
    std::vector<long long> diamonds(n);
    for (long long i = 0; i < n; i++)
    {
        std::cin >> diamonds[i];
    }

    Solution sol;
    std::cout << sol.maxDiamondOnTwoCases(diamonds, k) << std::endl;

    return 0;
}