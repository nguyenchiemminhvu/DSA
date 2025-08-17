/**
https://vjudge.net/contest/691170#problem/H
https://usaco.guide/problems/cf-1244E/user-solutions

You are given a sequence a consisting of n integers.

You may perform the following operation on this sequence: choose any element and either increase or decrease it by one.

Calculate the minimum possible difference between the maximum element and the minimum element in the sequence, if you can perform the aforementioned operation no more than k times.
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
    long long minimizingDifference(vector<long long>& arr, long long k)
    {
        sort(arr.begin(), arr.end());

        long long n = arr.size();
        long long left = 0, right = n - 1;
        
        while (left < right)
        {
            long long left_count = left + 1;
            long long right_count = n - right;

            if (left_count < right_count)
            {
                long long left_diff = arr[left + 1] - arr[left];
                long long left_ops = left_diff * left_count;
                if (k >= left_ops)
                {
                    k -= left_ops;
                    left++;
                }
                else
                {
                    arr[left] += (k / left_count);
                    return arr[right] - arr[left];
                }
            }
            else
            {
                long long right_diff = arr[right] - arr[right - 1];
                long long right_ops = right_diff * right_count;

                if (k >= right_ops)
                {
                    k -= right_ops;
                    right--;
                }
                else
                {
                    arr[right] -= (k / right_count);
                    return arr[right] - arr[left];
                }
            }
        }

        return 0;
    }
};

int main()
{
    long long n, k;
    std::cin >> n >> k;

    std::vector<long long> arr(n);
    for (long long i = 0; i < n; i++)
    {
        std::cin >> arr[i];
    }

    Solution sol;
    std::cout << sol.minimizingDifference(arr, k) << std::endl;

    return 0;
}