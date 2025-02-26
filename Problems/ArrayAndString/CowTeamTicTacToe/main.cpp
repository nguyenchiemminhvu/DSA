/**
https://vjudge.net/contest/690982#problem/I
 */

#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <unordered_set>

using namespace std;

class Solution
{
public:
    std::pair<int, int> teamTicTacToe(const std::vector<std::string>& grid)
    {
        std::set<char> individual_winner;
        std::set<std::pair<char, char>> couple_winner;

        // check rows
        for (int i = 0; i < 3; i++)
        {
            std::unordered_set<char> s(grid[i].begin(), grid[i].end());
            if (s.size() == 1)
            {
                individual_winner.insert(*s.begin());
            }
            else if (s.size() == 2)
            {
                char mi = std::min(grid[i][0], std::min(grid[i][1], grid[i][2]));
                char ma = std::max(grid[i][0], std::max(grid[i][1], grid[i][2]));
                couple_winner.insert({mi, ma});
            }
        }

        // check columns
        for (int i = 0; i < 3; i++)
        {
            std::unordered_set<char> s;
            for (int j = 0; j < 3; j++)
            {
                s.insert(grid[j][i]);
            }

            if (s.size() == 1)
            {
                individual_winner.insert(*s.begin());
            }
            else if (s.size() == 2)
            {
                char mi = std::min(grid[0][i], std::min(grid[1][i], grid[2][i]));
                char ma = std::max(grid[0][i], std::max(grid[1][i], grid[2][i]));
                couple_winner.insert({mi, ma});
            }
        }

        // check diagonals
        std::unordered_set<char> s1, s2;
        for (int i = 0; i < 3; i++)
        {
            s1.insert(grid[i][i]);
            s2.insert(grid[i][2 - i]);
        }

        if (s1.size() == 1)
        {
            individual_winner.insert(*s1.begin());
        }
        else if (s1.size() == 2)
        {
            char mi = std::min(grid[0][0], std::min(grid[1][1], grid[2][2]));
            char ma = std::max(grid[0][0], std::max(grid[1][1], grid[2][2]));
            couple_winner.insert({mi, ma});
        }

        if (s2.size() == 1)
        {
            individual_winner.insert(*s2.begin());
        }
        else if (s2.size() == 2)
        {
            char mi = std::min(grid[0][2], std::min(grid[1][1], grid[2][0]));
            char ma = std::max(grid[0][2], std::max(grid[1][1], grid[2][0]));
            couple_winner.insert({mi, ma});
        }

        return {individual_winner.size(), couple_winner.size()};
    }
};

int main()
{
    freopen("tttt.in", "r", stdin);
    freopen("tttt.out", "w", stdout);

    std::vector<std::string> grid(3);
    for (int i = 0; i < 3; ++i)
    {
        std::cin >> grid[i];
    }

    Solution sol;
    std::pair<int, int> res = sol.teamTicTacToe(grid);
    std::cout << res.first << std::endl;
    std::cout << res.second << std::endl;
    return 0;
}