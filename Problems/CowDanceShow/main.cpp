/**
https://vjudge.net/contest/691170#problem/A
https://vjudge.net/contest/691170/problemPdf/A?descKey=2724105935840367
 */

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>

using namespace std;

class Solution
{
public:
    int cowDanceShow(int n, int t, const std::vector<int>& d)
    {
        int res = n;

        int left = 1;
        int right = n;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;
            if (testing(n, t, d, mid))
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
    bool testing(int n, int t, const std::vector<int>& d, int k)
    {
        std::priority_queue<int, std::vector<int>, std::greater<int>> pq;
        for (int i = 0; i < n; i++)
        {
            int last_time = 0;
            if (pq.size() == k)
            {
                last_time = pq.top();
                pq.pop();
            }

            if (last_time + d[i] > t)
            {
                return false;
            }

            pq.push(last_time + d[i]);
        }

        return true;
    }
};

int main()
{
    freopen("cowdance.in", "r", stdin);
    freopen("cowdance.out", "w", stdout);

    int n, t;
    std::cin >> n >> t;
    std::vector<int> d(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> d[i];
    }

    Solution sol;
    std::cout << sol.cowDanceShow(n, t, d) << std::endl;

    return 0;
}