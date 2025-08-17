/**
https://vjudge.net/contest/690993#problem/C
https://usaco.guide/problems/cses-1661-subarray-sums-ii/solution

Given an array of n integers, your task is to count the number of subarrays having sum x.
 */

#include <iostream>
#include <vector>
#include <map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

int main()
{
    long long res = 0;
    std::map<long long, long long> sum_freq;
    sum_freq[0] = 1;
    long long cur_sum = 0;

    long long n, x;
    std::cin >> n >> x;
    int val;
    for (long long i = 0; i < n; i++)
    {
        std::cin >> val;

        cur_sum += val;
        long long prev_sum = cur_sum - x;
        res += sum_freq[cur_sum - x];

        sum_freq[cur_sum]++;
    }

    std::cout << res << std::endl;

    return 0;
}