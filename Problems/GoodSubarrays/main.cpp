/**
https://vjudge.net/contest/690993#problem/G
https://usaco.guide/problems/cf-good-subarrays/solution
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

class Solution
{
public:
    long long numberOfGoodSubarrays(const std::string& nums)
    {
        long long n = nums.length();
        std::vector<long long> prefix(n + 1, 0);
        for (long long i = 0; i < n; i++)
        {
            prefix[i + 1] = prefix[i] + (nums[i] - '0');
        }

        long long res = 0;
        std::map<long long, long long> freq;
        freq[0] = 1LL;
        for (long long i = 1; i <= n; i++)
        {
            res += freq[prefix[i] - i];
            freq[prefix[i] - i]++;
        }

        return res;
    }
};

int main()
{
    long long T;
    std::cin >> T;

    for (long long t = 0; t < T; t++)
    {
        int n;
        std::cin >> n;

        std::string line;
        std::cin >> line;

        Solution sol;
        std::cout << sol.numberOfGoodSubarrays(line) << std::endl;
    }

    return 0;
}