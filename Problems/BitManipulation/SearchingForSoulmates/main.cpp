/**
https://vjudge.net/contest/691174#problem/E
https://usaco.org/index.php?page=viewproblem2&cpid=1182
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

class Solution
{
public:
    long long min_operations(long long a, long long b)
    {
        if (a > b)
        {
            if (a % 2LL == 1LL)
            {
                a++;
            }
            else
            {
                a /= 2LL;
            }
            return 1LL + min_operations(a, b);
        }
        else if (a < b)
        {
            long long add_flag = 0LL;
            if (b % 2LL == 1LL)
            {
                add_flag = 1LL;
            }

            return std::min(b - a, 1LL + add_flag + min_operations(a, b / 2LL));
        }

        return 0LL; // a == b, no additional step
    }
};

int main()
{
    int n;
    std::cin >> n;

    Solution sol;
    for (int i = 0; i < n; i++)
    {
        long long a, b;
        std::cin >> a >> b;
        std::cout << sol.min_operations(a, b) << std::endl;
    }

    return 0;
}