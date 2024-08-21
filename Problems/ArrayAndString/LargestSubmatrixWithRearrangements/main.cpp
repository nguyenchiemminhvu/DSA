/**
https://leetcode.com/problems/largest-submatrix-with-rearrangements

You are given a binary matrix matrix of size m x n, and you are allowed to rearrange the columns of the matrix in any order.
Return the area of the largest submatrix within matrix where every element of the submatrix is 1 after reordering the columns optimally.

Example 1:

Input: matrix = [[0,0,1],[1,1,1],[1,0,1]]
Output: 4
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 4.

Example 2:

Input: matrix = [[1,0,1,0,1]]
Output: 3
Explanation: You can rearrange the columns as shown above.
The largest submatrix of 1s, in bold, has an area of 3.

Example 3:

Input: matrix = [[1,1,0],[1,0,1]]
Output: 2
Explanation: Notice that you must rearrange entire columns, and there is no way to make a submatrix of 1s larger than an area of 2.

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m * n <= 105
matrix[i][j] is either 0 or 1.
*/

#include <iostream>
#include <vector>
#include <algorithm>

class Solution
{
public:
    int largestSubmatrix(std::vector<std::vector<int>>& matrix)
    {
        std::ios::sync_with_stdio(false);
        std::cin.tie(nullptr);
        std::cout.tie(nullptr);

        int m = matrix.size();
        int n = matrix[0].size();
        
        for (int r = 1; r < m; r++)
        {
            for (int c = 0; c < n; c++)
            {
                if (matrix[r][c] == 1)
                {
                    matrix[r][c] += matrix[r - 1][c];
                }
            }
        }

        int res = 0;

        for (std::vector<int>& row : matrix)
        {
            std::sort(row.begin(), row.end(), std::greater<int>());
            for (int i = 0; i < row.size(); i++)
            {
                res = std::max(res, row[i] * (i + 1));
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> input = {
        {0,0,1},
        {1,1,1},
        {1,0,1}
    };
    std::cout << sol.largestSubmatrix(input) << std::endl;
    return 0;
}