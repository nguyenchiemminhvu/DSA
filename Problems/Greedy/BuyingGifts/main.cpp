/**
https://vjudge.net/contest/690988#problem/J
https://www.cnblogs.com/onlyblues/p/17201939.html

Little Sasha has two friends, whom he wants to please with gifts on the Eighth of March. To do this, he went to the largest shopping center in the city.
There are n departments in the mall, each of which has exactly two stores. For convenience, we number the departments with integers from 1 to n. It is known that gifts in the first store of the i department cost ai rubles, and in the second store of the i department — bi rubles.

Entering the mall, Sasha will visit each of the n departments of the mall, and in each department, he will enter exactly one store. When Sasha gets into the i-th department, he will perform exactly one of two actions:
- Buy a gift for the first friend, spending ai rubles on it.
- Buy a gift for the second friend, spending bi rubles on it.

Sasha is going to buy at least one gift for each friend. Moreover, he wants to pick up gifts in such a way that the price difference of the most expensive gifts bought for friends is as small as possible so that no one is offended.
 */

#include <iostream>
#include <vector>
#include <set>
#include <climits>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

/**
- Sort the indices based on the prices in the first store (a[i]), not the pairs directly.
- Maintain a prefix maximum for the prices in the second store (b[i]).
- Handle the multiset operations correctly to find the closest prices.
 */
class Solution
{
    const long long INF = (long long)(1e9);

public:
    long long minPriceDifference(std::vector<std::pair<long long, long long>>& prices)
    {
        long long n = prices.size();

        std::vector<long long> max_first_idx(n);
        for (long long i = 0; i < n; i++)
        {
            max_first_idx[i] = i;
        }
        std::sort(max_first_idx.begin(), max_first_idx.end(), [prices](const long long i, const long long j) {
            return prices[i].first > prices[j].first;
        });

        long long max_second_prefix = -INF; // max of second prices from 0 to i - 1
        std::multiset<long long> max_second_suffix; // max of second prices from i + 1 to n - 1
        max_second_suffix.insert(-INF);
        max_second_suffix.insert(INF);
        for (long long i = 0; i < n; i++)
        {
            max_second_suffix.insert(prices[i].second);
        }

        long long min_diff = INF;
        for (long long i = 0; i < n; i++)
        {
            // remove the current second price at current index of max first price
            max_second_suffix.erase(max_second_suffix.find(prices[max_first_idx[i]].second));

            long long max_second_candidate = -INF; // max of second price prefix and suffix

            min_diff = std::min(
                {
                    min_diff, 
                    std::abs(prices[max_first_idx[i]].first - std::max(max_second_prefix, *max_second_suffix.lower_bound(prices[max_first_idx[i]].first))), 
                    std::abs(prices[max_first_idx[i]].first - std::max(max_second_prefix, *max_second_suffix.upper_bound(prices[max_first_idx[i]].first)))
                }
            );

            // update max second prefix 0...i-1 with current i index
            max_second_prefix = std::max(max_second_prefix, prices[max_first_idx[i]].second);
        }
        return min_diff;
    }
};

int main()
{
    long long T;
    std::cin >> T;
    for (long long t = 0; t < T; t++)
    {
        long long n;
        std::cin >> n;

        std::vector<std::pair<long long, long long>> prices(n);
        for (long long i = 0; i < n; i++)
        {
            std::cin >> prices[i].first >> prices[i].second;
        }

        Solution sol;
        std::cout << sol.minPriceDifference(prices) << std::endl;
    }

    return 0;
}