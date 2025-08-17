/**
https://vjudge.net/contest/691177#problem/J
https://usaco.guide/problems/usaco-1108/user-solutions
 */

#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <algorithm>

using namespace std;

std::vector<int> dir_r = {1, -1, 0, 0};
std::vector<int> dir_c = {0, 0, -1, 1};

int main()
{
    int n;
    std::cin >> n;

    std::map<std::pair<int, int>, bool> cows;
    int need_more_cows = 0;

    std::function<bool(int, int)> f_has_cow_here = [&](int r, int c) -> bool
    {
        return cows[{r, c}] > 0;
    };

    std::function<bool(int, int)> f_is_comfortable = [&](int r, int c) -> bool
    {
        if (!f_has_cow_here(r, c))
        {
            return false;
        }

        int count = 0;
        for (int i = 0; i < 4; i++)
        {
            count += (f_has_cow_here(r + dir_r[i], c + dir_c[i]));
        }
        return count == 3;
    };

    std::function<void(int, int)> f_place_a_cow = [&](int r, int c) -> void
    {
        if (f_has_cow_here(r, c))
        {
            return;
        }

        cows[{r, c}] = true;
        need_more_cows++;

        if (f_is_comfortable(r, c))
        {
            for (int i = 0; i < 4; i++)
            {
                int next_r = r + dir_r[i];
                int next_c = c + dir_c[i];
                if (!f_has_cow_here(next_r, next_c))
                {
                    f_place_a_cow(next_r, next_c);
                }
            }
        }

        for (int i = 0; i < 4; i++)
        {
            int next_r = r + dir_r[i];
            int next_c = c + dir_c[i];
            if (f_is_comfortable(next_r, next_c))
            {
                for (int j = 0; j < 4; j++)
                {
                    int next_next_r = next_r + dir_r[j];
                    int next_next_c = next_c + dir_c[j];
                    if (!f_has_cow_here(next_next_r, next_next_c))
                    {
                        f_place_a_cow(next_next_r, next_next_c);
                    }
                }
            }
        }
    };

    for (int i = 0; i < n; i++)
    {
        int r, c;
        std::cin >> r >> c;
        f_place_a_cow(r, c);
        need_more_cows--;
        std::cout << need_more_cows << std::endl;
    }

    return 0;
}