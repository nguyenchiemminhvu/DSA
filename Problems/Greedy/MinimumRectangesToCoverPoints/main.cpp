/**
https://leetcode.com/problems/minimum-rectangles-to-cover-points/description/

You are given a 2D integer array points, where points[i] = [xi, yi]. You are also given an integer w. Your task is to cover all the given points with rectangles.

Each rectangle has its lower end at some point (x1, 0) and its upper end at some point (x2, y2), where x1 <= x2, y2 >= 0, and the condition x2 - x1 <= w must be satisfied for each rectangle.

A point is considered covered by a rectangle if it lies within or on the boundary of the rectangle.

Return an integer denoting the minimum number of rectangles needed so that each point is covered by at least one rectangle.

Note: A point may be covered by more than one rectangle.

Input: points = [[2,1],[1,0],[1,4],[1,8],[3,5],[4,6]], w = 1

Output: 2

Explanation:

The image above shows one possible placement of rectangles to cover the points:

A rectangle with a lower end at (1, 0) and its upper end at (2, 8)
A rectangle with a lower end at (3, 0) and its upper end at (4, 8)

Constraints:

1 <= points.length <= 105
points[i].length == 2
0 <= xi == points[i][0] <= 109
0 <= yi == points[i][1] <= 109
0 <= w <= 109
All pairs (xi, yi) are distinct.
*/

#include <iostream>
#include <vector>
#include <unordered_set>
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
    int minRectanglesToCoverPoints(vector<vector<int>>& points, int w)
    {
        std::vector<int> columns;
        
        {
            std::unordered_set<int> us;
            for (const std::vector<int>& point : points)
            {
                if (us.find(point[0]) == us.end())
                {
                    columns.push_back(point[0]);
                    us.insert(point[0]);
                }
            }
        }

        std::sort(columns.begin(), columns.end());

        int res = columns.size();
        int left = 0;
        for (int i = 1; i < columns.size(); i++)
        {
            if (columns[i] - columns[left] <= w)
            {
                res--;
            }
            else
            {
                left = i;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> points = {
        {0,0},{1,1},{2,2},{3,3},{4,4},{5,5},{6,6}
    };
    int w = 2;
    std::cout << sol.minRectanglesToCoverPoints(points, w) << std::endl;
    return 0;
}