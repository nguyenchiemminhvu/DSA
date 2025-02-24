/**
https://vjudge.net/contest/691170#problem/C
https://usaco.org/index.php?page=viewproblem2&cpid=594
 */

#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <climits>

using namespace std;

class Solution
{
public:
    int solve(int n, int k, std::vector<int>& pos)
    {
        std::sort(pos.begin(), pos.end());

        int left = 1;
        int right = pos.back() - pos.front();
        int res = right;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (testing(n, k, pos, mid))
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
    bool testing(int n, int k, const std::vector<int>& sorted, int r)
    {
        int count = 1;
        int last_pick = 0;
        for (int i = 1; i < n; i++)
        {
            if (sorted[i] - sorted[last_pick] > r * 2)
            {
                last_pick = i;
                count++;
            }

            if (count > k)
            {
                return false;
            }
        }

        return true;
    }
};

int main()
{
    freopen("angry.in", "r", stdin);
    freopen("angry.out", "w", stdout);

    Solution sol;

    int n, k;
    cin >> n >> k;
    std::vector<int> pos(n);
    for (int i = 0; i < n; i++)
    {
        cin >> pos[i];
    }

    std::cout << sol.solve(n, k, pos) << std::endl;

    return 0;
}