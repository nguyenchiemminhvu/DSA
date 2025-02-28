/**
https://vjudge.net/contest/690988#problem/D

You have a stick of length x and you want to divide it into n sticks, with given lengths, whose total length is x.

On each move you can take any stick and divide it into two sticks. The cost of such an operation is the length of the original stick.

What is the minimum cost needed to create the sticks?
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

class Solution
{
public:
    long long stickDivisions(long long x, long long n, std::vector<long long>& sticks)
    {
        long long res = 0LL;
        std::priority_queue<long long, std::vector<long long>, std::greater<long long>> pq(sticks.begin(), sticks.end());

        while (pq.size() > 1)
        {
            long long first = pq.top();
            pq.pop();
            long long second = pq.top();
            pq.pop();

            long long cost = first + second;
            res += cost;
            pq.push(cost);
        }

        return res;
    }
};

int main()
{
    long long x, n;
    std::cin >> x >> n;
    std::vector<long long> d(n);
    for (long long i = 0; i < n; i++)
    {
        std::cin >> d[i];
    }

    Solution sol;
    std::cout << sol.stickDivisions(x, n, d) << std::endl;

    return 0;
}