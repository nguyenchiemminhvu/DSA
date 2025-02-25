/**
https://vjudge.net/contest/690982#problem/C
 */

#include <iostream>
#include <cstdio>
#include <cmath>

using namespace std;

class Solution
{
public:
    int solve(int x, int y)
    {
        int dist = 0;
        int dir = 1;
        int steps = 1;
        while (true)
        {
            int next_pos = x + steps * dir;
            dist += std::abs(next_pos - x);

            bool found = false;
            if (dir == 1 && y >= x && y <= next_pos)
            {
                found = true;
            }
            else if (dir == -1 && y <= x && y >= next_pos)
            {
                found = true;
            }

            if (found)
            {
                dist -= std::abs(next_pos - y);
                break;
            }
            else
            {
                dist += std::abs(next_pos - x);
            }

            dir *= -1;
            steps *= 2;
        }

        return dist;
    }
};

int main()
{
    freopen("lostcow.in", "r", stdin);
    freopen("lostcow.out", "w", stdout);

    int x, y;
    std::cin >> x >> y;

    Solution sol;
    std::cout << sol.solve(x, y) << std::endl;

    return 0;
}