/**
https://leetcode.com/problems/maximum-matrix-sum/description/

You are given an n x n integer matrix. You can do the following operation any number of times:

Choose any two adjacent elements of matrix and multiply each of them by -1.
Two elements are considered adjacent if and only if they share a border.

Your goal is to maximize the summation of the matrix's elements. Return the maximum sum of the matrix's elements using the operation mentioned above.

Example 1:

Input: matrix = [[1,-1],[-1,1]]
Output: 4
Explanation: We can follow the following steps to reach sum equals 4:
- Multiply the 2 elements in the first row by -1.
- Multiply the 2 elements in the first column by -1.

Example 2:

Input: matrix = [[1,2,3],[-1,-2,-3],[1,2,3]]
Output: 16
Explanation: We can follow the following step to reach sum equals 16:
- Multiply the 2 last elements in the second row by -1.

Constraints:

n == matrix.length == matrix[i].length
2 <= n <= 250
-105 <= matrix[i][j] <= 105
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    long long maxMatrixSum(vector<vector<int>>& matrix) 
    {
        long long abs_sum = 0LL;
        int abs_min = INT_MAX;
        int count_neg = 0;
        for (const std::vector<int>& row : matrix)
        {
            for (const int& val : row)
            {
                abs_sum += std::abs(val);
                abs_min = std::min(abs_min, std::abs(val));
                count_neg += (val < 0);
            }
        }

        if (count_neg % 2 == 0)
        {
            return abs_sum;
        }
        else
        {
            return abs_sum - 2 * abs_min;
        }
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> mat = {
        {1, -1},
        {-1, 1}
    };
    std::cout << sol.maxMatrixSum(mat) << std::endl;
    return 0;
}