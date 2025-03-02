/**
https://vjudge.net/contest/690993#problem/B
https://usaco.guide/problems/usaco-694-hoof-paper-scissors/solution

You have probably heard of the game "Rock, Paper, Scissors". The cows like to play a similar game they call "Hoof, Paper, Scissors".
The rules of "Hoof, Paper, Scissors" are simple. Two cows play against each-other. They both count to three and then each simultaneously makes a gesture that represents either a hoof, a piece of paper, or a pair of scissors. Hoof beats scissors (since a hoof can smash a pair of scissors), scissors beats paper (since scissors can cut paper), and paper beats hoof (since the hoof can get a papercut). For example, if the first cow makes a "hoof" gesture and the second a "paper" gesture, then the second cow wins. Of course, it is also possible to tie, if both cows make the same gesture.

Unfortunately, Bessie, being a cow, is also very lazy. As a result, she tends to play the same gesture multiple times in a row. In fact, she is only willing to switch gestures at most once over the entire set of games.

Given the sequence of gestures FJ will be playing, please determine the maximum number of games that Bessie can win.
 */

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int maxGamesBessieCanWin(const std::vector<char>& choices)
    {
        int n = choices.size();

        std::unordered_map<int, char> indexToChoice = {{0, 'H'}, {1, 'P'}, {2, 'S'}};
        std::vector<std::vector<int>> prefix_win(3, std::vector<int>(n, 0)); // 0: H, 1: P, 2: S

        for (int i = 0; i < n; i++)
        {
            for (int c = 0; c < 3; c++)
            {
                char rep = indexToChoice[c];
                prefix_win[c][i] = (int)is_win(rep, choices[i]);

                if (i > 0)
                {
                    // calculate prefix sum of the winning choices
                    prefix_win[c][i] += prefix_win[c][i - 1];
                }
            }
        }

        int res = 0;

        // max of winning choices without switching
        for (int c = 0; c < 3; c++)
        {
            res = std::max(res, prefix_win[c][n - 1]);
        }

        // max of winning choices with switching after index i-th
        for (int i = 0; i < n; i++)
        {
            for (int c = 0; c < 3; c++)
            {
                int next_switch = ((c + 1) % 3);
                res = std::max(res, prefix_win[c][i] + prefix_win[next_switch][n - 1] - prefix_win[next_switch][i]);

                next_switch = ((c + 2) % 3);
                res = std::max(res, prefix_win[c][i] + prefix_win[next_switch][n - 1] - prefix_win[next_switch][i]);
            }
        }

        return res;
    }
private:
    bool is_win(char a, char b)
    {
        // function to check if a is win over b
        if (a == 'H')
        {
            return b == 'S';
        }
        if (a == 'P')
        {
            return b == 'H';
        }
        if (a == 'S')
        {
            return b == 'P';
        }

        return false;
    }
};

int main()
{
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);

    int n;
    std::cin >> n;

    std::vector<char> choices(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> choices[i];
    }

    Solution sol;
    std::cout << sol.maxGamesBessieCanWin(choices) << std::endl;

    return 0;
}