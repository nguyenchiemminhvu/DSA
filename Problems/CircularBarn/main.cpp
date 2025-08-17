/**
https://vjudge.net/contest/690982#problem/G
https://usaco.org/index.php?page=viewproblem2&cpid=616
 */

#include <iostream>
#include <vector>
#include <climits>

using namespace std;

class Solution
{
public:
    int circular_barn(const std::vector<int> rooms)
    {
        int res = INT_MAX;

        int n = rooms.size();
        for (int i = 0; i < n; i++)
        {
            res = std::min(res, get_distance(rooms, i));
        }

        return res;
    }
private:
    int get_distance(const std::vector<int>& rooms, int start)
    {
        int n = rooms.size();
        int dist = 0;
        for (int i = 0; i < n; i++)
        {
            dist += rooms[((i + start) % n)] * i;
        }

        return dist;
    }
};

int main()
{
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<int> rooms(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> rooms[i];
    }

    Solution sol;
    std::cout << sol.circular_barn(rooms) << std::endl;

    return 0;
}