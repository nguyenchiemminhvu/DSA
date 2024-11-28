/**
https://leetcode.com/problems/path-with-minimum-effort/description/

You are a hiker preparing for an upcoming hike. You are given heights, a 2D array of size rows x columns, where heights[row][col] represents the height of cell (row, col). You are situated in the top-left cell, (0, 0), and you hope to travel to the bottom-right cell, (rows-1, columns-1) (i.e., 0-indexed). You can move up, down, left, or right, and you wish to find a route that requires the minimum effort.

A route's effort is the maximum absolute difference in heights between two consecutive cells of the route.

Return the minimum effort required to travel from the top-left cell to the bottom-right cell.

Example 1:

Input: heights = [[1,2,2],[3,8,2],[5,3,5]]
Output: 2
Explanation: The route of [1,3,5,3,5] has a maximum absolute difference of 2 in consecutive cells.
This is better than the route of [1,2,2,2,5], where the maximum absolute difference is 3.

Example 2:

Input: heights = [[1,2,3],[3,8,4],[5,3,5]]
Output: 1
Explanation: The route of [1,2,3,4,5] has a maximum absolute difference of 1 in consecutive cells, which is better than route [1,3,5,3,5].

Example 3:

Input: heights = [[1,2,1,1,1],[1,2,1,2,1],[1,2,1,2,1],[1,2,1,2,1],[1,1,1,2,1]]
Output: 0
Explanation: This route does not require any effort.

Constraints:

rows == heights.length
columns == heights[i].length
1 <= rows, columns <= 100
1 <= heights[i][j] <= 106
*/

#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int minimumEffortPath(vector<vector<int>>& heights)
    {
        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};

        int rows = heights.size();
        int cols = heights[0].size();

        std::vector<std::vector<int>> efforts(rows, std::vector<int>(cols, INT_MAX));
        efforts[0][0] = 0;

        std::priority_queue<std::vector<int>, std::vector<std::vector<int>>, std::greater<std::vector<int>>> pq;
        pq.push({0, 0, 0});

        while (!pq.empty())
        {
            std::vector<int> cur = pq.top();
            pq.pop();

            int cur_effort = cur[0];
            int r = cur[1];
            int c = cur[2];

            if (r == rows - 1 && c == cols - 1)
            {
                return cur_effort;
            }

            for (int i = 0; i < 4; i++)
            {
                int next_r = r + dx[i];
                int next_c = c + dy[i];

                if (next_r >= 0 && next_r < rows && next_c >= 0 && next_c < cols)
                {
                    int next_effort = std::max(cur_effort, std::abs(heights[next_r][next_c] - heights[r][c]));
                    if (next_effort < efforts[next_r][next_c])
                    {
                        efforts[next_r][next_c] = next_effort;
                        pq.push({next_effort, next_r, next_c});
                    }
                }
            }
        }

        return INT_MAX;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> heights = {
        {1, 2, 2},
        {3, 8, 2},
        {5, 3, 5}
    };
    std::cout << sol.minimumEffortPath(heights) << std::endl;
    return 0;
}