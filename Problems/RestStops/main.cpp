/**
https://vjudge.net/contest/690988#problem/E
https://usaco.org/index.php?page=viewproblem2&cpid=810

Bessie would like to maximize her consumption of tasty grass. But she is worried about Farmer John; she thinks that if at any point along the hike she is behind Farmer John on the trail, he might lose all motivation to continue!

Help Bessie find the maximum total tastiness units she can obtain while making sure that Farmer John completes the hike.
 */

#include <iostream>
#include <vector>
#include <stack>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    long long maxConsumptionGrass(long long length, long long n, long long rf, long long rb, std::vector<std::pair<long long, long long>>& rest_stops)
    {
        std::stack<std::pair<long long, long long>> st;
        for (long long i = n - 1; i >= 0; i--)
        {
            if (st.empty())
            {
                st.push(rest_stops[i]);
            }
            else
            {
                if (rest_stops[i].second > st.top().second)
                {
                    st.push(rest_stops[i]);
                }
            }
        }

        long long max_tastiness = 0;
        long long last_position = 0;

        while (!st.empty())
        {
            std::pair<long long, long long> cur_candidate = st.top();
            st.pop();

            long long position = cur_candidate.first;
            long long tastiness = cur_candidate.second;

            long long time_farmer_john = (position - last_position) * static_cast<long long>(rf);
            long long time_bessie = (position - last_position) * static_cast<long long>(rb);

            max_tastiness += (time_farmer_john - time_bessie) * tastiness;
            last_position = position;
        }

        return max_tastiness;
    }
};

int main()
{
    freopen("reststops.in", "r", stdin);
    freopen("reststops.out", "w", stdout);

    long long L, N, rf, rb;
    std::cin >> L >> N >> rf >> rb;

    std::vector<std::pair<long long, long long>> rest_stops(N);
    for (long long i = 0; i < N; i++)
    {
        long long pos;
        long long tastiness;
        std::cin >> pos >> tastiness;
        rest_stops[i] = {pos, tastiness};
    }

    Solution sol;
    std::cout << sol.maxConsumptionGrass(L, N, rf, rb, rest_stops) << std::endl;

    return 0;
}