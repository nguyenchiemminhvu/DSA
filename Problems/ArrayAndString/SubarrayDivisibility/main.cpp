/**
https://vjudge.net/contest/690993#problem/D
https://usaco.guide/problems/cses-1662-subarray-divisibility/solution

Given an array of n integers, your task is to count the number of subarrays where the sum of values is divisible by n.
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
    long long n;
    std::cin >> n;

    long long res = 0;
    long long cur_sum = 0;
    std::map<long long, long long> mod_freq;
    mod_freq[0] = 1;

    long long val;
    for (long long i = 0; i < n; i++)
    {
        std::cin >> val;

        cur_sum += val;
        long long remain = ((cur_sum % n) + n) % n;
        res += mod_freq[remain];

        mod_freq[remain]++;
    }

    std::cout << res << std::endl;

    return 0;
}