/**
https://leetcode.com/problems/count-servers-that-communicate/description/

You are given a map of a server center, represented as a m * n integer matrix grid, where 1 means that on that cell there is a server and 0 means that it is no server. Two servers are said to communicate if they are on the same row or on the same column.

Return the number of servers that communicate with any other server.

Example 1:

Input: grid = [[1,0],[0,1]]
Output: 0
Explanation: No servers can communicate with others.

Example 2:

Input: grid = [[1,0],[1,1]]
Output: 3
Explanation: All three servers can communicate with at least one other server.

Example 3:

Input: grid = [[1,1,0,0],[0,0,1,0],[0,0,1,0],[0,0,0,1]]
Output: 4
Explanation: The two servers in the first row can communicate with each other. The two servers in the third column can communicate with each other. The server at right bottom corner can't communicate with any other server.

Constraints:

m == grid.length
n == grid[i].length
1 <= m <= 250
1 <= n <= 250
grid[i][j] == 0 or 1
 */

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int countServers(vector<vector<int>>& grid)
    {
        std::vector<int> row_count(grid.size(), 0);
        std::vector<int> col_count(grid[0].size(), 0);

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[i].size(); j++)
            {
                row_count[i] += grid[i][j];
                col_count[j] += grid[i][j];
            }
        }

        int res = 0;

        for (int i = 0; i < grid.size(); i++)
        {
            for (int j = 0; j < grid[0].size(); j++)
            {
                if (grid[i][j] && (row_count[i] > 1 || col_count[j] > 1))
                {
                    res++;
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{1, 0}, {1, 1}};
    std::cout << sol.countServers(grid) << std::endl;
    return 0;
}