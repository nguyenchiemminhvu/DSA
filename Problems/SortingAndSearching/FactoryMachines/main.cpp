/**
https://vjudge.net/contest/691170#problem/J

A factory has n machines which can be used to make products. Your goal is to make a total of t products.

For each machine, you know the number of seconds it needs to make a single product. The machines can work simultaneously, and you can freely decide their schedule.

What is the shortest time needed to make t products?
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
    long long solve(std::vector<long long>& times, long long t)
    {
        long long left = 1LL;
        long long right = static_cast<long long>(*min_element(times.begin(), times.end())) * t;
        long long res = LONG_MAX;
        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            if (canProduce(times, t, mid))
            {
                res = mid;
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
    bool canProduce(const std::vector<long long>& times, long long t, long long timeLimit)
    {
        long long totalProducts = 0LL;
        for (long long time : times)
        {
            totalProducts += (timeLimit / time);
            if (totalProducts >= t)
            {
                return true;
            }
        }
        return false;
    }
};

int main()
{
    long long n, t;
    cin >> n >> t;
    vector<long long> times(n);
    for (long long i = 0; i < n; i++)
    {
        cin >> times[i];
    }

    Solution sol;
    std::cout << sol.solve(times, t) << std::endl;

    return 0;
}