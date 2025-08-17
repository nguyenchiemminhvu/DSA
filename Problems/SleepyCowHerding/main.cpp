/**
https://vjudge.net/contest/691168#problem/K
https://usaco.org/index.php?page=viewproblem2&cpid=918
https://usaco.guide/problems/usaco-918-sleepy-cow-herding/solution

Farmer John's N cows are always wandering off to the far reaches of the farm! He needs your help herding them back together.
The main field in the farm is long and skinny -- we can think of it as a number line, on which a cow can occupy any integer location. The N cows are currently situated at different integer locations, and Farmer John wants to move them so they occupy consecutive locations (e.g., positions 3, 4, 5, 6, 7, and 8).

Unfortunately, the cows are rather sleepy, and Farmer John has trouble getting their attention to make them move. At any point in time, he can only make a cow move if she is an "endpoint" (either the minimum or maximum position among all the cows). When he moves a cow, he can instruct her to move to any unoccupied integer location as long as in this new location she is no longer an endpoint. Observe that over time, these types of moves tend to push the cows closer and closer together.

Please determine the minimum and maximum number of moves possible before the cows become grouped in N consecutive locations.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    std::pair<int, int> minMaxMovesGroupCowsTogether(std::vector<int>& pos)
    {
        int n = pos.size();
        std::pair<int, int> res = { 0, 0 };

        std::sort(pos.begin(), pos.end());

        // 2 special cases
        if (pos[n - 2] - pos[0] == n - 2 && pos[n - 1] - pos[n - 2] > 2)
        {
            // XXXXX___X
            res.first = 2;
        }
        else if (pos[n - 1] - pos[1] == n - 2 && pos[1] - pos[0] > 2)
        {
            // X___XXXXX
            res.first = 2;
        }
        else
        {
            int max_range = 0;
            int right = 0;
            for (int left = 0; left < n; left++)
            {
                while (right < n - 1 && pos[right + 1] - pos[left] + 1 <= n)
                {
                    right++;
                }

                max_range = std::max(max_range, right - left + 1);
            }

            res.first = n - max_range;
        }

        int count_gap = 0;
        for (int i = 1; i < n; i++)
        {
            count_gap += pos[i] - pos[i - 1] - 1;
        }

        res.second = std::max(count_gap - (pos[1] - pos[0] - 1), count_gap - (pos[n - 1] - pos[n - 2] - 1));

        return res;
    }
};

int main()
{
    freopen("herding.in", "r", stdin);
    freopen("herding.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> pos[i];
    }

    Solution sol;
    std::pair<int, int> res = sol.minMaxMovesGroupCowsTogether(pos);
    std::cout << res.first << std::endl;
    std::cout << res.second << std::endl;

    return 0;
}