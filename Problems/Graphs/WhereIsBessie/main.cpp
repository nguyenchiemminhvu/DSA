/**
https://vjudge.net/contest/691177#problem/G
https://usaco.guide/problems/usaco-740-wheres-bessie/solution

Always known for being quite tech-savy, Farmer John is testing out his new automated drone-mounted cow locator camera, which supposedly can take a picture of his field and automatically figure out the location of cows. Unfortunately, the camera does not include a very good algorithm for finding cows, so FJ needs your help developing a better one.
The overhead image of his farm taken by the camera is described by an N×N grid of characters, each in the range A…Z, representing one of 26 possible colors. Farmer John figures the best way to define a potential cow location (PCL) is as follows: A PCL is a rectangular sub-grid (possibly the entire image) with sides parallel to the image sides, not contained within any other PCL (so no smaller subset of a PCL is also a PCL). Furthermore, a PCL must satisfy the following property: focusing on just the contents of the rectangle and ignoring the rest of the image, exactly two colors must be present, one forming a contiguous region and one forming two or more contiguous regions.

For example, a rectangle with contents

AAAAA
ABABA
AAABB
would constitute a PCL, since the A's form a single contiguous region and the B's form more than one contiguous region. The interpretation is a cow of color A with spots of color B.

A region is "contiguous" if you can traverse the entire region by moving repeatedly from one cell in the region to another cell in the region taking steps up, down, left, or right.

Given the image returned by FJ's camera, please count the number of PCLs.
 */

#include <iostream>
#include <cstdio>
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <set>
#include <tuple>

using namespace std;

void BFS(const std::vector<std::string>& grid, int start_r, int start_c, char color, std::vector<std::vector<bool>>& visited)
{
    std::vector<int> dir_r = {-1, 1, 0, 0};
    std::vector<int> dir_c = {0, 0, -1, 1};

    int m = grid.size();
    int n = grid[0].size();

    std::queue<std::pair<int, int>> Q;
    Q.push({start_r, start_c});
    visited[start_r][start_c] = true;
    while (!Q.empty())
    {
        std::pair<int, int> cur = Q.front();
        Q.pop();

        int r = cur.first;
        int c = cur.second;

        for (int i = 0; i < 4; i++)
        {
            int next_r = r + dir_r[i];
            int next_c = c + dir_c[i];

            if (next_r >= 0 && next_r < m && next_c >= 0 && next_c < n && !visited[next_r][next_c] && grid[next_r][next_c] == color)
            {
                visited[next_r][next_c] = true;
                Q.push({next_r, next_c});
            }
        }
    }
}

int count_region(const std::vector<std::string>& grid, char color)
{
    int count = 0;

    int m = grid.size();
    int n = grid[0].size();

    std::vector<std::vector<bool>> visited(m, std::vector<bool>(n, false));
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (!visited[i][j] && grid[i][j] == color)
            {
                BFS(grid, i, j, color, visited);
                count++;
            }
        }
    }

    return count;
}

bool is_subgrid(int start_r, int end_r, int start_c, int end_c, const std::tuple<int, int, int, int>& pcl)
{
    int sr, er, sc, ec;
    std::tie(sr, er, sc, ec) = pcl;
    if (start_r >= sr && end_r <= er && start_c >= sc && end_c <= ec)
    {
        return true;
    }

    return false;
}

int main()
{
    freopen("where.in", "r", stdin);
    freopen("where.out", "w", stdout);

    int n;
    std::cin >> n;

    std::vector<std::string> grid(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> grid[i];
    }

    std::vector<std::tuple<int, int, int, int>> pcl_set;

    // Consider all possible subgrid sizes
    for (int start_r = 0; start_r < n; start_r++)
    {
        for (int end_r = start_r; end_r < n; end_r++)
        {
            for (int start_c = 0; start_c < n; start_c++)
            {
                for (int end_c = start_c; end_c < n; end_c++)
                {
                    vector<string> subgrid;
                    for (int i = start_r; i <= end_r; i++)
                    {
                        subgrid.push_back(grid[i].substr(start_c, end_c - start_c + 1));
                    }

                    std::unordered_set<char> set_colors;
                    for (const std::string row : subgrid)
                    {
                        for (char c : row)
                        {
                            set_colors.insert(c);
                        }
                    }

                    if (set_colors.size() != 2)
                    {
                        continue;
                    }

                    char color1;
                    char color2;
                    auto it = set_colors.begin();
                    color1 = *it;
                    ++it;
                    color2 = *it;

                    int count_region_1 = count_region(subgrid, color1);
                    int count_region_2 = count_region(subgrid, color2);

                    if ((count_region_1 == 1 && count_region_2 >= 2) || (count_region_1 >= 2 && count_region_2 == 1))
                    {
                        pcl_set.push_back({start_r, end_r, start_c, end_c});
                    }
                }
            }
        }
    }

    int count_pcl = 0;
    for (int i = 0; i < pcl_set.size(); i++)
    {
        bool valid_pcl = true;
        for(int j = 0; j < pcl_set.size(); j++)
        {
            if (i == j)
            {
                continue;
            }

            if (is_subgrid(std::get<0>(pcl_set[i]), std::get<1>(pcl_set[i]), std::get<2>(pcl_set[i]), std::get<3>(pcl_set[i]), pcl_set[j]))
            {
                valid_pcl = false;
            }
        }

        count_pcl += valid_pcl;
    }
    std::cout << count_pcl << std::endl;

    return 0;
}