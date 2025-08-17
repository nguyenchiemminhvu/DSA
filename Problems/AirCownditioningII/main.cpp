/**
https://vjudge.net/contest/690986#problem/F
https://usaco.org/index.php?page=viewproblem2&cpid=1276

With the hottest recorded summer ever at Farmer John's farm, he needs a way to cool down his cows. Thus, he decides to invest in some air conditioners.

Farmer John's N cows (1≤N≤20) live in a barn that contains a sequence of stalls in a row, numbered 1…100. Cow i occupies a range of these stalls, starting from stall si and ending with stall ti. The ranges of stalls occupied by different cows are all disjoint from each-other. Cows have different cooling requirements. Cow i must be cooled by an amount ci , meaning every stall occupied by cow i must have its temperature reduced by at least ci units.The barn contains M air conditioners, labeled 1…M (1≤M≤10). The ith air conditioner costs mi units of money to operate and cools the range of stalls starting from stall ai and ending with stall bi. If running, the ith air conditioner reduces the temperature of all the stalls in this range by pi. Ranges of stalls covered by air conditioners may potentially overlap.

Running a farm is no easy business, so FJ has a tight budget. Please determine the minimum amount of money he needs to spend to keep all of his cows comfortable. It is guaranteed that if FJ uses all of his conditioners, then all cows will be comfortable.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
#include <tuple>

using namespace std;

class Solution
{
public:
    int minAmountMoneyForAirConditioner(const std::vector<std::tuple<int, int, int>>& cows, const std::vector<std::tuple<int, int, int, int>>& air_conditioners)
    {
        int n = cows.size();
        int m = air_conditioners.size();

        int min_amount = INT_MAX;

        std::vector<int> stalls(101, 0); // 0 means no need of air conditioner
        for (int i = 0; i < n; i++)
        {
            for (int j = std::get<0>(cows[i]); j <= std::get<1>(cows[i]); j++)
            {
                stalls[j] = std::get<2>(cows[i]);
            }
        }

        for (int mask = 0; mask < (1 << m); mask++)
        {
            std::vector<int> cooler(101, 0);
            int cost = 0;
            for (int i = 0; i < m; i++)
            {
                if (mask & (1 << i))
                {
                    cost += std::get<3>(air_conditioners[i]);
                    for (int j = std::get<0>(air_conditioners[i]); j <= std::get<1>(air_conditioners[i]); j++)
                    {
                        cooler[j] += std::get<2>(air_conditioners[i]);
                    }
                }
            }

            for (int i = 0; i <= 100; i++)
            {
                if (stalls[i] > 0 && cooler[i] < stalls[i])
                {
                    cost = INT_MAX;
                    break;
                }
            }

            min_amount = std::min(min_amount, cost);
        }

        return min_amount;
    }
};

int main()
{
    int n, m;
    std::cin >> n >> m;

    std::vector<std::tuple<int, int, int>> cows;
    for (int i = 0; i < n; i++)
    {
        int s, t, c;
        std::cin >> s >> t >> c;
        cows.push_back(std::make_tuple(s, t, c));
    }

    std::vector<std::tuple<int, int, int, int>> air_conditioners;
    for (int i = 0; i < m; i++)
    {
        int a, b, p, m;
        std::cin >> a >> b >> p >> m;
        air_conditioners.push_back(std::make_tuple(a, b, p, m));
    }

    Solution sol;
    std::cout << sol.minAmountMoneyForAirConditioner(cows, air_conditioners) << std::endl;

    return 0;
}