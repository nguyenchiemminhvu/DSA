/**
https://vjudge.net/contest/691174#problem/A
https://usaco.guide/problems/cf-powered-addition/solution
https://graphics.stanford.edu/%7Eseander/bithacks.html#RoundUpPowerOf2
 */

#include <iostream>
#include <vector>

using namespace std;

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    long long minSeconds(const std::vector<long long>& arr, long long n)
    {
        long long max_bits = 0;
        long long prev = arr[0];

        for (long long i = 1; i < n; i++)
        {
            if (arr[i] < prev)
            {
                long long diff = prev - arr[i];
                max_bits = max(max_bits, get_required_bits(diff));
            }
            prev = max(prev, arr[i]);
        }
        return max_bits;
    }

private:
    long long get_required_bits(long long val)
    {
        long long bits = 0;
        while (val > 0)
        {
            bits++;
            val >>= 1;
        }
        return bits;
    }
};

int main()
{
    long long t;
    std::cin >> t;
    while (t)
    {
        long long n;
        std::cin >> n;
        std::vector<long long> arr(n);
        for (long long i = 0; i < n; i++)
        {
            std::cin >> arr[i];
        }

        Solution sol;
        std::cout << sol.minSeconds(arr, n) << std::endl;

        t--;
    }
    return 0;
}