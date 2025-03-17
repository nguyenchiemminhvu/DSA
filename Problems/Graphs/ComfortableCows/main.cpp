/**
https://vjudge.net/contest/691177#problem/J
https://usaco.guide/problems/usaco-1108/user-solutions
 */

#include <iostream>
#include <vector>

using namespace std;

std::vector<int> dir_r = {0, 0, 1, -1};
std::vector<int> dir_c = {1, -1, 0, 0};

int OFF_SET = 1001;

int main()
{
    int n;
    std::cin >> n;

    std::vector<std::vector<int>> adj_count(2025, std::vector<int>(2025, 0));
    std::vector<std::vector<bool>> has_cow(2025, std::vector<bool>(2025, false));
    
    int need_cows = 0;
    for (int i = 0; i < n; i++)
    {
        int r, c;
        std::cin >> r >> c;

        r += OFF_SET;
        c += OFF_SET;

        has_cow[r][c] = true;
        for (int j = 0; j < 4; j++)
        {
            int next_r = r + dir_r[j];
            int next_c = c + dir_c[j];

            if (has_cow[next_r][next_c])
            {
                adj_count[r][c]++;
                if (adj_count[r][c] == 3)
                {
                    need_cows++;
                }
                if (adj_count[r][c] == 4)
                {
                    need_cows--;
                }

                adj_count[next_r][next_c]++;
                if (adj_count[next_r][next_c] == 3)
                {
                    need_cows++;
                }
                if (adj_count[next_r][next_c] == 4)
                {
                    need_cows--;
                }
            }
        }

        std::cout << need_cows << std::endl;
    }

    return 0;
}