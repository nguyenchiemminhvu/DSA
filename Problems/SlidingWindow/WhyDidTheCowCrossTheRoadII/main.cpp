/**
https://vjudge.net/contest/690993#problem/E
https://usaco.guide/problems/usaco-712-why-did-the-cow-cross-the-road-ii/solution

To allow cows to cross at these crosswalks, FJ installs electric crossing signals, which light up with a green cow icon when it is ok for the cow to cross, and red otherwise. Unfortunately, a large electrical storm has damaged some of his signals. Given a list of the damaged signals, please compute the minimum number of signals that FJ needs to repair in order for there to exist some contiguous block of at least K working signals.
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

int main()
{
    freopen("maxcross.in", "r", stdin);
    freopen("maxcross.out", "w", stdout);

    int n, k, b;
    std::cin >> n >> k >> b;

    std::vector<int> broken(n + 1, 0);
    for (int i = 0; i < b; i++)
    {
        int broken_idx;
        std::cin >> broken_idx;
        broken[broken_idx] = 1;
    }

    for (int i = 1; i <= n; i++)
    {
        broken[i] += broken[i - 1];
    }

    int res = INT_MAX;
    for (int i = k; i <= n; i++)
    {
        res = std::min(res, broken[i] - broken[i - k]);
    }

    std::cout << res << std::endl;

    return 0;
}