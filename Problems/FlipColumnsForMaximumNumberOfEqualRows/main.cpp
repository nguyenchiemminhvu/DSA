/**
https://leetcode.com/problems/flip-columns-for-maximum-number-of-equal-rows

You are given an m x n binary matrix matrix.

You can choose any number of columns in the matrix and flip every cell in that column (i.e., Change the value of the cell from 0 to 1 or vice versa).

Return the maximum number of rows that have all values equal after some number of flips.

Example 1:

Input: matrix = [[0,1],[1,1]]
Output: 1
Explanation: After flipping no values, 1 row has all values equal.

Example 2:

Input: matrix = [[0,1],[1,0]]
Output: 2
Explanation: After flipping values in the first column, both rows have equal values.

Example 3:

Input: matrix = [[0,0,0],[0,0,1],[1,1,0]]
Output: 2
Explanation: After flipping values in the first two columns, the last two rows have equal values.
 

Constraints:

m == matrix.length
n == matrix[i].length
1 <= m, n <= 300
matrix[i][j] is either 0 or 1.
*/

#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int maxEqualRowsAfterFlips(vector<vector<int>>& matrix)
    {
        int res = 1;
        std::unordered_map<std::string, int> pattern_freq;

        for (const std::vector<int>& row : matrix)
        {
            std::string pattern = "";
            for (int val : row)
            {
                pattern += (val == row[0] ? '0' : '1');
            }

            pattern_freq[pattern]++;
            res = std::max(res, pattern_freq[pattern]);
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> mat = {
        {0, 1},
        {1, 0}
    };
    std::cout << sol.maxEqualRowsAfterFlips(mat) << std::endl;
    return 0;
}