/**
https://leetcode.com/problems/find-the-number-of-winning-players/

You are given an integer n representing the number of players in a game and a 2D array pick where pick[i] = [xi, yi] represents that the player xi picked a ball of color yi.

Player i wins the game if they pick strictly more than i balls of the same color. In other words,

Player 0 wins if they pick any ball.
Player 1 wins if they pick at least two balls of the same color.
...
Player i wins if they pick at leasti + 1 balls of the same color.
Return the number of players who win the game.

Note that multiple players can win the game.

Example 1:

Input: n = 4, pick = [[0,0],[1,0],[1,0],[2,1],[2,1],[2,0]]

Output: 2

Explanation:

Player 0 and player 1 win the game, while players 2 and 3 do not win.

Example 2:

Input: n = 5, pick = [[1,1],[1,2],[1,3],[1,4]]

Output: 0

Explanation:

No player wins the game.

Example 3:

Input: n = 5, pick = [[1,1],[2,4],[2,4],[2,4]]

Output: 1

Explanation:

Player 2 wins the game by picking 3 balls with color 4.

Constraints:

2 <= n <= 10
1 <= pick.length <= 100
pick[i].length == 2
0 <= xi <= n - 1 
0 <= yi <= 10
 */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class Solution
{
public:
    int winningPlayerCount(int n, std::vector<std::vector<int>>& pick)
    {
        std::unordered_set<int> win_set;
        std::vector<std::unordered_map<int, int>> pick_map(n);
        for (const std::vector<int>& p : pick)
        {
            pick_map[p[0]][p[1]]++;
            if (pick_map[p[0]][p[1]] > p[0])
            {
                win_set.insert(p[0]);
            }
        }

        return win_set.size();
    }
};

int main()
{
    Solution sol;
    int n = 4;
    std::vector<std::vector<int>> pick = {
        {0, 0},
        {1, 0},
        {1, 0},
        {2, 1},
        {2, 1},
        {2, 0},
    };
    std::cout << sol.winningPlayerCount(n, pick) << std::endl;
    return 0;
}