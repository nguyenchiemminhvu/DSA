/**
https://vjudge.net/contest/691170#problem/B
https://usaco.org/index.php?page=viewproblem2&cpid=858
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

class Solution
{
public:
    int grassEatingConvention(int n, int m, int c, std::vector<int>& a)
    {
        int res = INT_MAX;

        std::sort(a.begin(), a.end());
        int left = 1;
        int right = 1e9 + 1;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (testing(n, m, c, a, mid))
            {
                res = std::min(res, mid);
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return res;
    }
private:
    bool testing(int n, int m, int c, const std::vector<int>& sorted, int dur)
    {
        int bus = 1;
        int last_pick = 0; // last cow picked
        int picked = 0; // total cows are picked
        int count = 0; // count of cows in the current bus
        for (int i = 0; i < n; i++)
        {
            if (count == 0)
            {
                count++;
                picked++;
            }
            else 
            {
                if (sorted[i] - sorted[last_pick] > dur || count == c)
                {
                    count = 0;
                    bus++;
                    last_pick = i;
                }
                
                count++;
                picked++;
                
                if (bus > m)
                {
                    return false;
                }

                if (picked >= n)
                {
                    return true;
                }
            }
        }

        return true;
    }
};

int main()
{
    freopen("convention.in", "r", stdin);
    freopen("convention.out", "w", stdout);

    int n, m, c;
    std::cin >> n >> m >> c;
    std::vector<int> a(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> a[i];
    }

    Solution s;
    std::cout << s.grassEatingConvention(n, m, c, a) << std::endl;

    return 0;
}