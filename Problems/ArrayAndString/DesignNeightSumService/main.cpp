/**
https://leetcode.com/problems/design-neighbor-sum-service/description/

You are given a n x n 2D array grid containing distinct elements in the range [0, n2 - 1].

Implement the neighborSum class:

- neighborSum(int [][]grid) initializes the object.
- int adjacentSum(int value) returns the sum of elements which are adjacent neighbors of value, that is either to the top, left, right, or bottom of value in grid.
- int diagonalSum(int value) returns the sum of elements which are diagonal neighbors of value, that is either to the top-left, top-right, bottom-left, or bottom-right of value in grid.

Example 1:

Input:

["neighborSum", "adjacentSum", "adjacentSum", "diagonalSum", "diagonalSum"]

[[[[0, 1, 2], [3, 4, 5], [6, 7, 8]]], [1], [4], [4], [8]]

Output: [null, 6, 16, 16, 4]

Example 2:

Input:

["neighborSum", "adjacentSum", "diagonalSum"]

[[[[1, 2, 0, 3], [4, 7, 15, 6], [8, 9, 10, 11], [12, 13, 14, 5]]], [15], [9]]

Output: [null, 23, 45]

Constraints:

3 <= n == grid.length == grid[0].length <= 10
0 <= grid[i][j] <= n2 - 1
All grid[i][j] are distinct.
value in adjacentSum and diagonalSum will be in the range [0, n2 - 1].
At most 2 * n2 calls will be made to adjacentSum and diagonalSum.
*/

#include <iostream>
#include <vector>
#include <unordered_map>

class neighborSum
{
public:
    neighborSum(std::vector<std::vector<int>>& grid)
    {
        m_grid.swap(grid);

        for (int i = 0; i < m_grid.size(); i++)
        {
            for (int j = 0; j < m_grid[i].size(); j++)
            {
                m_sum_adj[m_grid[i][j]] = left(i, j) + right(i, j) + top(i, j) + bot(i, j);
                m_sum_diag[m_grid[i][j]] = top_left(i, j) + top_right(i, j) + bot_left(i, j) + bot_right(i, j);
            }
        }
    }
    
    int adjacentSum(int value)
    {
        return m_sum_adj[value];
    }
    
    int diagonalSum(int value)
    {
        return m_sum_diag[value];
    }
private:
    int top_left(int i, int j)
    {
        return (i > 0 && j > 0) ? m_grid[i - 1][j - 1] : 0;
    }

    int top(int i, int j)
    {
        return (i > 0) ? m_grid[i - 1][j] : 0;
    }

    int top_right(int i, int j)
    {
        return (i > 0 && j < m_grid[i].size() - 1) ? m_grid[i - 1][j + 1] : 0;
    }

    int left(int i, int j)
    {
        return (j > 0) ? m_grid[i][j - 1] : 0;
    }

    int right(int i, int j)
    {
        return (j < m_grid[i].size() - 1) ? m_grid[i][j + 1] : 0;
    }

    int bot_left(int i, int j)
    {
        return (i < m_grid.size() - 1 && j > 0) ? m_grid[i + 1][j - 1] : 0;
    }

    int bot(int i, int j)
    {
        return (i < m_grid.size() - 1) ? m_grid[i + 1][j] : 0;
    }

    int bot_right(int i, int j)
    {
        return (i < m_grid.size() - 1 && j < m_grid[i].size() - 1) ? m_grid[i + 1][j + 1] : 0;
    }
    
private:
    std::vector<std::vector<int>> m_grid;
    std::unordered_map<int, int> m_sum_diag;
    std::unordered_map<int, int> m_sum_adj;
};

/**
 * Your neighborSum object will be instantiated and called as such:
 * neighborSum* obj = new neighborSum(grid);
 * int param_1 = obj->adjacentSum(value);
 * int param_2 = obj->diagonalSum(value);
 */

int main()
{
    std::vector<std::vector<int>> grid = {
        {0, 1, 2},
        {3, 4, 5},
        {6, 7, 8},
    };
    neighborSum obj(grid);
    std::cout << obj.adjacentSum(1) << std::endl;
    std::cout << obj.adjacentSum(4) << std::endl;
    std::cout << obj.diagonalSum(4) << std::endl;
    std::cout << obj.diagonalSum(8) << std::endl;

    return 0;
}