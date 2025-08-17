/**
https://leetcode.com/problems/rotating-the-box

You are given an m x n matrix of characters box representing a side-view of a box. Each cell of the box is one of the following:

A stone '#'
A stationary obstacle '*'
Empty '.'
The box is rotated 90 degrees clockwise, causing some of the stones to fall due to gravity. Each stone falls down until it lands on an obstacle, another stone, or the bottom of the box. Gravity does not affect the obstacles' positions, and the inertia from the box's rotation does not affect the stones' horizontal positions.

It is guaranteed that each stone in box rests on an obstacle, another stone, or the bottom of the box.

Return an n x m matrix representing the box after the rotation described above.

Example 1:

Input: box = [["#",".","#"]]
Output: [["."],
         ["#"],
         ["#"]]
Example 2:

Input: box = [["#",".","*","."],
              ["#","#","*","."]]
Output: [["#","."],
         ["#","#"],
         ["*","*"],
         [".","."]]
Example 3:

Input: box = [["#","#","*",".","*","."],
              ["#","#","#","*",".","."],
              ["#","#","#",".","#","."]]
Output: [[".","#","#"],
         [".","#","#"],
         ["#","#","*"],
         ["#","*","."],
         ["#",".","*"],
         ["#",".","."]]

Constraints:

m == box.length
n == box[i].length
1 <= m, n <= 500
box[i][j] is either '#', '*', or '.'.
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    std::vector<std::vector<char>> rotateTheBox(std::vector<std::vector<char>>& box)
    {
        for (auto& row : box)
        {
            int emptySlot = row.size() - 1;
            for (int col = row.size() - 1; col >= 0; --col)
            {
                if (row[col] == '#')
                {
                    std::swap(row[col], row[emptySlot]);
                    --emptySlot;
                }
                else if (row[col] == '*')
                {
                    emptySlot = col - 1;
                }
            }
        }

        return rotateMatrix90Clockwise(box);
    }

private:
    std::vector<std::vector<char>> rotateMatrix90Clockwise(const std::vector<std::vector<char>>& matrix)
    {
        int m = matrix.size();
        int n = matrix[0].size();

        std::vector<std::vector<char>> rotatedMatrix(n, std::vector<char>(m));

        for (int i = 0; i < m; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                rotatedMatrix[j][m - 1 - i] = matrix[i][j];
            }
        }

        return rotatedMatrix;
    }
};

int main()
{
    return 0;
}