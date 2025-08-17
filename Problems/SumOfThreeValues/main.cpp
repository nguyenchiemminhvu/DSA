/**
https://vjudge.net/contest/691168#problem/C

You are given an array of n integers, and your task is to find three values (at distinct positions) whose sum is x.

Output
Print three integers: the positions of the values. If there are several solutions, you may print any of them. If there are no solutions, print IMPOSSIBLE.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    std::vector<int> threeSum(std::vector<int>& arr, int x)
    {
        int n = arr.size();
        std::vector<std::pair<int, int>> couples(n);
        for (int i = 0; i < n; i++)
        {
            couples[i].first = arr[i];
            couples[i].second = i;
        }
        std::sort(couples.begin(), couples.end());

        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                int sum = couples[i].first + couples[j].first;
                int target = x - sum;

                auto it = std::lower_bound(couples.begin() + j + 1, couples.end(), target, [](const std::pair<int, int>& a, int b) {
                    return a.first < b;
                });

                if (it != couples.end() && it->first == target)
                {
                    std::vector<int> res = {couples[i].second, couples[j].second, it->second};
                    std::sort(res.begin(), res.end());
                    return res;
                }
            }
        }

        throw -1;
    }
};

int main()
{
    int n, x;
    std::cin >> n >> x;
    std::vector<int> arr(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    Solution sol;
    try
    {
        std::vector<int> res = sol.threeSum(arr, x);
        for (int idx : res)
        {
            std::cout << idx + 1 << " ";
        }
        std::cout << std::endl;
    }
    catch (int val)
    {
        std::cout << "IMPOSSIBLE" << std::endl;
    }

    return 0;
}
