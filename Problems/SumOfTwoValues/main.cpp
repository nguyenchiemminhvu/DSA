/**
https://vjudge.net/contest/691168#problem/A
https://usaco.guide/problems/cses-1640-sum-of-two-values/solution

You are given an array of n integers, and your task is to find two values (at distinct positions) whose sum is x.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    std::pair<int, int> sumOfTwoValues(std::vector<std::pair<int, int>>& arr, int x)
    {
        std::sort(arr.begin(), arr.end(), [](const auto& a, const auto& b) { return a.first < b.first;});
        int n = arr.size();

        for (int i = 0; i < n; i++)
        {
            int target = x - arr[i].first;
            
            int left = i + 1, right = n - 1;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;
                if (arr[mid].first == target)
                {
                    return {arr[i].second, arr[mid].second};
                }
                else if (arr[mid].first < target)
                {
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }
        }

        return {-1, -1};
    }
};

int main()
{
    int n, x;
    cin >> n >> x;
    std::vector<std::pair<int, int>> arr(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i].first;
        arr[i].second = i + 1;
    }

    Solution sol;
    std::pair<int, int> res = sol.sumOfTwoValues(arr, x);
    if (res.first > res.second)
    {
        std::swap(res.first, res.second);
    }

    if (res.first == -1)
    {
        std::cout << "IMPOSSIBLE" << std::endl;
    }
    else
    {
        std::cout << res.first << " " << res.second << std::endl;
    }

    return 0;
}