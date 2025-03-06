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
int main()
{
    long long T;
    std::cin >> T;
    for (long long t = 0; t < T; t++)
    {
        long long n;
        std::cin >> n;

        std::vector<long long> a(n);
        std::vector<long long> b(n);
        std::vector<long long> pos(n);
        for (long long i = 0; i < n; i++)
        {
            std::cin >> a[i] >> b[i];
            pos[i] = i;
        }

        std::sort(pos.begin(), pos.end(), [&](long long i, long long j) {
            return a[i] > a[j];
        });

        long long max_second_left = INT_MIN;
        std::multiset<long long> max_second_right({INT_MIN, INT_MAX});
        for (int i = 0; i < n; i++)
        {
            max_second_right.insert(b[i]);
        }

        long long min_diff = LONG_MAX;
        for (long long i = 0; i < n; i++)
        {
            max_second_right.erase(max_second_right.find(b[pos[i]]));
            min_diff = std::min(
                {
                    min_diff, 
                    std::abs(a[pos[i]] - std::max(*max_second_right.lower_bound(a[pos[i]]), max_second_left)), 
                    std::abs(a[pos[i]] - std::max(*std::prev(max_second_right.upper_bound(a[pos[i]])), max_second_left))
                }
            );
            max_second_left = std::max(max_second_left, b[pos[i]]);
        }

        std::cout << min_diff << std::endl;
    }

    return 0;
}