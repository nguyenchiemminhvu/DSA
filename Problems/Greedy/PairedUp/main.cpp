/**
https://vjudge.net/contest/691168#problem/D
https://usaco.org/index.php?page=viewproblem2&cpid=738

Farmer John finds that his cows are each easier to milk when they have another cow nearby for moral support. He therefore wants to take his M cows (M≤1,000,000,000, M even) and partition them into M/2 pairs. Each pair of cows will then be ushered off to a separate stall in the barn for milking. The milking in each of these M/2 stalls will take place simultaneously.
To make matters a bit complicated, each of Farmer John's cows has a different milk output. If cows of milk outputs A and B are paired up, then it takes a total of A+B units of time to milk them both.

Please help Farmer John determine the minimum possible amount of time the entire milking process will take to complete, assuming he pairs the cows up in the best possible way.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int minimumMilkTime(std::vector<std::pair<int, int>>& cows)
    {
        std::sort(cows.begin(), cows.end(), [](const auto& a, const auto& b) {
            return a.second < b.second;
        });

        int res = 0;

        int left = 0;
        int right = cows.size() - 1;
        while (left <= right)
        {
            res = std::max(res, cows[left].second + cows[right].second);
            int count = std::min(cows[left].first, cows[right].first);
            if (left == right)
            {
                count /= 2;
            }
            cows[left].first -= count;
            cows[right].first -= count;

            if (cows[left].first == 0)
            {
                left++;
            }
            if (cows[right].first == 0)
            {
                right--;
            }
        }

        return res;
    }
};

int main()
{
    freopen("pairup.in", "r", stdin);
    freopen("pairup.out", "w", stdout);

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> cows(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> cows[i].first >> cows[i].second;
    }

    Solution sol;
    std::cout << sol.minimumMilkTime(cows) << std::endl;

    return 0;
}