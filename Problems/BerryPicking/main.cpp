/**
https://vjudge.net/contest/690988#problem/G

Bessie and her little sister Elsie are picking berries in Farmer John's berry patch. Farmer John's patch has exactly N berry trees (1≤N≤1000); tree i contains exactly Bi berries (1 ≤ Bi ≤1000). Bessie has exactly K baskets (1≤K≤1000, K even). Each basket can hold as many berries from a single tree as Bessie wants, but cannot contain berries from two different trees as their flavors will clash with each other. Baskets may remain empty.
Bessie wants to maximize the number of berries she collects. However, Farmer John wants Bessie to share with her little sister, and so Bessie will have to give Elsie the K/2 baskets with the largest number of berries. This means that Elsie may even end up with more berries than Bessie, which is very unfair, but unfortunately, sibling dynamics are not always fair.

Help Bessie figure out the maximum number of berries she can collect.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <numeric>

using namespace std;

int main()
{
    freopen("berries.in", "r", stdin);
    freopen("berries.out", "w", stdout);

    long long n, k;
    std::cin >> n >> k;

    std::vector<long long> berries(n);
    long long max_berry = 0;
    for (long long i = 0; i < n; i++)
    {
        std::cin >> berries[i];
        max_berry = std::max(max_berry, berries[i]);
    }

    long long max_berries_for_bessie = 0;
    for (long long berry_each_basket = max_berry; berry_each_basket >= 1; berry_each_basket--)
    {
        std::priority_queue<long long> pq;
        for (int berry : berries)
        {
            pq.push(berry);
        }

        std::vector<long long> baskets;
        while (!pq.empty() && baskets.size() < k)
        {
            int cur_berry = pq.top();
            pq.pop();

            if (cur_berry >= berry_each_basket)
            {
                int full_basket = cur_berry / berry_each_basket;
                int left_over = cur_berry % berry_each_basket;

                for (int j = 0; j < full_basket; j++)
                {
                    baskets.push_back(berry_each_basket);
                }

                pq.push(left_over);
            }
            else
            {
                baskets.push_back(cur_berry);
            }
        }

        while (baskets.size() < k)
        {
            baskets.push_back(0LL);
        }

        std::sort(baskets.begin(), baskets.end());
        max_berries_for_bessie = std::max(max_berries_for_bessie, std::accumulate(baskets.begin(), baskets.begin() + k / 2, 0LL));
    }

    std::cout << max_berries_for_bessie << std::endl;

    return 0;
}