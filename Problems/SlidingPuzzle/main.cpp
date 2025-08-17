/**
https://leetcode.com/problems/sliding-puzzle/

On an 2 x 3 board, there are five tiles labeled from 1 to 5, and an empty square represented by 0. A move consists of choosing 0 and a 4-directionally adjacent number and swapping it.

The state of the board is solved if and only if the board is [[1,2,3],[4,5,0]].

Given the puzzle board board, return the least number of moves required so that the state of the board is solved. If it is impossible for the state of the board to be solved, return -1.

Example 1:

Input: board = [[1,2,3],[4,0,5]]
Output: 1
Explanation: Swap the 0 and the 5 in one move.
Example 2:

Input: board = [[1,2,3],[5,4,0]]
Output: -1
Explanation: No number of moves will make the board solved.

Example 3:

Input: board = [[4,1,2],[5,0,3]]
Output: 5
Explanation: 5 is the smallest number of moves that solves the board.
An example path:
After move 0: [[4,1,2],[5,0,3]]
After move 1: [[4,1,2],[0,5,3]]
After move 2: [[0,1,2],[4,5,3]]
After move 3: [[1,0,2],[4,5,3]]
After move 4: [[1,2,0],[4,5,3]]
After move 5: [[1,2,3],[4,5,0]]

Constraints:

board.length == 2
board[i].length == 3
0 <= board[i][j] <= 5
Each value board[i][j] is unique.
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>
#include <queue>

using namespace std;

class Solution
{
public:
    int slidingPuzzle(vector<vector<int>>& board)
    {
        std::string target = "123450";
        std::string start = std::to_string(board[0][0])
                          + std::to_string(board[0][1])
                          + std::to_string(board[0][2])
                          + std::to_string(board[1][0])
                          + std::to_string(board[1][1])
                          + std::to_string(board[1][2]);
        
        return BFS(target, start);
    }
private:
    int BFS(const std::string& target, const std::string& start)
    {
        int moves = 0;
        vector<vector<int>> directions = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};

        std::unordered_set<std::string> visited;
        std::queue<std::string> Q;
        Q.push(start);
        visited.insert(start);

        while (!Q.empty())
        {
            int N = Q.size();
            for (int i = 0; i < N; i++)
            {
                std::string cur = Q.front();
                Q.pop();

                if (cur == target)
                {
                    return moves;
                }

                int zero_idx = cur.find('0');
                if (zero_idx < 3)
                {
                    std::string temp = cur;
                    std::swap(temp[zero_idx], temp[zero_idx + 3]);
                    if (visited.find(temp) == visited.end())
                    {
                        Q.push(temp);
                        visited.insert(temp);
                    }
                }
                else
                {
                    std::string temp = cur;
                    std::swap(temp[zero_idx], temp[zero_idx - 3]);
                    if (visited.find(temp) == visited.end())
                    {
                        Q.push(temp);
                        visited.insert(temp);
                    }
                }

                if (zero_idx % 3 <= 1)
                {
                    std::string temp = cur;
                    std::swap(temp[zero_idx], temp[zero_idx + 1]);
                    if (visited.find(temp) == visited.end())
                    {
                        Q.push(temp);
                        visited.insert(temp);
                    }
                }
                
                if (zero_idx % 3 >= 1)
                {
                    std::string temp = cur;
                    std::swap(temp[zero_idx], temp[zero_idx - 1]);
                    if (visited.find(temp) == visited.end())
                    {
                        Q.push(temp);
                        visited.insert(temp);
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> board = {
        {4,1,2},
        {5,0,3}
    };
    std::cout << sol.slidingPuzzle(board) << std::endl;
    return 0;
}