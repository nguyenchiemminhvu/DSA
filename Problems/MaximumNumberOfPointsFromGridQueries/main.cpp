/**
https://leetcode.com/problems/maximum-number-of-points-from-grid-queries

You are given an m x n integer matrix grid and an array queries of size k.

Find an array answer of size k such that for each integer queries[i] you start in the top left cell of the matrix and repeat the following process:

If queries[i] is strictly greater than the value of the current cell that you are in, then you get one point if it is your first time visiting this cell, and you can move to any adjacent cell in all 4 directions: up, down, left, and right.
Otherwise, you do not get any points, and you end this process.
After the process, answer[i] is the maximum number of points you can get. Note that for each query you are allowed to visit the same cell multiple times.

Return the resulting array answer.

Example 1:

Input: grid = [[1,2,3],[2,5,7],[3,5,1]], queries = [5,6,2]
Output: [5,8,1]
Explanation: The diagrams above show which cells we visit to get points for each query.

Example 2:

Input: grid = [[5,2,1],[1,1,2]], queries = [3]
Output: [0]
Explanation: We can not get any points because the value of the top left cell is already greater than or equal to 3.

Constraints:

m == grid.length
n == grid[i].length
2 <= m, n <= 1000
4 <= m * n <= 105
k == queries.length
1 <= k <= 104
1 <= grid[i][j], queries[i] <= 106
 */

#include <iostream>
#include <vector>
#include <algoritm>
#include <queue>

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

using pii = std::pair<int, int>;
using pipii = std::pair<int, std::pair<int, int>>;

class Solution
{
public:
    vector<int> maxPoints(vector<vector<int>>& grid, vector<int>& queries)
    {
        int m = grid.size();
        int n = grid[0].size();
        std::vector<int> dir_r = {-1, 1, 0, 0}; // Row changes: up, down
        std::vector<int> dir_c = {0, 0, -1, 1}; // Column changes: left, right

        vector<int> result(queries.size(), 0);

        std::vector<pii> pair_queries;
        for (int i = 0; i < queries.size(); i++)
        {
            pair_queries.push_back({queries[i], i});
        }
        std::sort(pair_queries.begin(), pair_queries.end());

        std::priority_queue<pipii, std::vector<pipii>, std::greater<pipii>> pq;
        pq.push({grid[0][0], {0, 0}});

        std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
        visited[0][0] = true;

        int point = 0;
        for (const pii& pair_query : pair_queries)
        {
            while (!pq.empty() && pq.top().first < pair_query.first)
            {
                auto [grid_val, cur_pos] = pq.top();
                pq.pop();

                int r = cur_pos.first;
                int c = cur_pos.second;

                point++;

                for (int i = 0; i < 4; i++)
                {
                    int next_r = r + dir_r[i];
                    int next_c = c + dir_c[i];
                    if (next_r >= 0 && next_r < m && next_c >= 0 && next_c < n)
                    {
                        if (!visited[next_r][next_c])
                        {
                            visited[next_r][next_c] = true;
                            pq.push({grid[next_r][next_c], {next_r, next_c}});
                        }               
                    }
                }
            }

            result[pair_query.second] = point;
        }

        return result;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> grid = {{1, 2, 3}, {2, 5, 7}, {3, 5, 1}};
    std::vector<int> queries = {5, 6, 2};
    std::vector<int> res = sol.maxPoints(grid, queries);
    for (int i : res)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;

    return 0;
}