/**
https://vjudge.net/contest/691170#problem/D
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    long long solve(int n, int m, vector<pair<long long, long long>>& mut)
    {
        sort(mut.begin(), mut.end());

        long long left = 1, right = (mut.back().second - mut.front().first) / (n - 1), res = 0;

        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            if (canPlaceCows(n, m, mut, mid))
            {
                res = std::max(res, mid);
                left = mid + 1;
            }
            else
            {
                right = mid - 1;
            }
        }
        return res;
    }

private:
    bool canPlaceCows(int n, int m, const vector<pair<long long, long long>>& sorted, long long d)
    {
        int count = 1;
        long long pos = sorted[0].first;
        int intervalIndex = 0;

        while (count < n)
        {
            pos += d;
            
            while (intervalIndex < m && pos > sorted[intervalIndex].second)
            {
                intervalIndex++;
            }

            if (intervalIndex == m)
                return false;

            if (pos < sorted[intervalIndex].first)
            {
                pos = sorted[intervalIndex].first;
            }

            count++;
        }

        return true;
    }
};

int main()
{
    freopen("socdist.in", "r", stdin);
    freopen("socdist.out", "w", stdout);

    int n, m;
    cin >> n >> m;
    vector<pair<long long, long long>> mut(m);

    for (int i = 0; i < m; i++)
    {
        cin >> mut[i].first >> mut[i].second;
    }

    Solution sol;
    cout << sol.solve(n, m, mut) << endl;

    return 0;
}
