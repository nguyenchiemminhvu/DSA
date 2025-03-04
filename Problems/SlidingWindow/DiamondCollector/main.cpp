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
    int maxDiamondOnTwoCases(std::vector<int>& diamonds, int K)
    {
        int n = diamonds.size();
        std::sort(diamonds.begin(), diamonds.end());

        // store the intervals [left, right] where (d[right] - d[left] <= K)
        std::vector<std::vector<int>> intervals;
        intervals.push_back({0, 0, 0});
        int left = 0;
        for (int right = 0; right < n; right++)
        {
            if (diamonds[right] - diamonds[left] <= K)
            {
                intervals.back()[0] = left;
                intervals.back()[1] = right;
                intervals.back()[2] = right - left + 1;
            }
            else
            {
                intervals.push_back({right, right, 0});
                while (diamonds[right] - diamonds[left] > K)
                {
                    left++;
                }
            }
        }

        // the problem becomes: find the couple of non-overlap intervals with maximum value,
        // where value of an interval is (end - start + 1).
        // Return the maximum value of that non-overlap interval couple.
        // Reference: https://www.geeksforgeeks.org/maximum-sum-of-at-most-two-non-overlapping-intervals-in-a-list-of-intervals-interval-scheduling-problem/
        int maxDiamonds = 0;
        std::priority_queue<std::vector<int>> pq; // sorted by greater end time of intervals
        int cur_max = 0;
        for (const std::vector<int> interval : intervals)
        {
            if (!pq.empty())
            {
                if (pq.top()[0] > interval[0])
                {
                    // overlap, don't calculate max from sum of this couple
                    break;
                }

                // calculate the max value of the previous non-overlap interval,
                // prepare to combine with the current non-overlap interval
                cur_max = std::max(cur_max, pq.top()[1]);
                pq.pop();
            }

            maxDiamonds = std::max(maxDiamonds, cur_max + interval[2]);
            pq.push({interval[1], interval[2]});
        }

        return maxDiamonds;
    }
};

int main()
{
    freopen("diamond.in", "r", stdin);
    freopen("diamond.out", "w", stdout);

    int n, k;
    std::cin >> n >> k;
    std::vector<int> diamonds(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> diamonds[i];
    }

    Solution sol;
    std::cout << sol.maxDiamondOnTwoCases(diamonds, k) << std::endl;

    return 0;
}