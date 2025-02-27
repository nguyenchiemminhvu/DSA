/**
https://vjudge.net/contest/690986#problem/C
https://usaco.org/index.php?page=viewproblem2&cpid=1011

Farmer John would like to create a triangular pasture for his cows.
There are N fence posts (3≤N≤100) at distinct points on the 2D map of his farm. He can choose three of them to form the vertices of the triangular pasture as long as one of the sides of the triangle is parallel to the x-axis and another side is parallel to the y-axis.

What is the maximum area of a pasture that Farmer John can form? It is guaranteed that at least one valid triangular pasture exists.

INPUT FORMAT (file triangles.in):
The first line of the input contains the integer N. Each of the next N lines contains two integers 
OUTPUT FORMAT (file triangles.out):
As the area itself is not necessarily an integer, output two times the maximum area of a valid triangle formed by the fence posts.
 */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdio>
#include <unordered_map>
#include <utility>
#include <algorithm>
#include <tuple>

using namespace std;

class Solution
{
public:
    int trianglePasture(const std::vector<std::pair<int, int>>& points)
    {
        int n = points.size();
        int res = 0;

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                for (int k = 0; k < n; k++)
                {
                    if (i == j || j == k)
                    {
                        continue;
                    }

                    if (points[i].second == points[j].second && points[i].first == points[k].first)
                    {
                        int area = abs((points[j].first - points[i].first) * (points[k].second - points[i].second));
                        res = max(res, area);
                    }
                }
            }
        }

        return res;
    }
};

int main()
{
    freopen("triangles.in", "r", stdin);
    freopen("triangles.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<std::pair<int, int>> points(n);
    for (int i = 0; i < n; i++)
    {
        int x, y;
        std::cin >> x >> y;
        points[i] = {x, y};
    }

    Solution sol;
    std::cout << sol.trianglePasture(points) << std::endl;

    return 0;
}