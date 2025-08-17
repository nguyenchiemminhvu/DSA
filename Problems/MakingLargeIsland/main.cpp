/**
https://leetcode.com/problems/making-a-large-island/description/

You are given an n x n binary matrix grid. You are allowed to change at most one 0 to be 1.

Return the size of the largest island in grid after applying this operation.

An island is a 4-directionally connected group of 1s.

Example 1:

Input: grid = [[1,0],[0,1]]
Output: 3
Explanation: Change one 0 to 1 and connect two 1s, then we get an island with area = 3.

Example 2:

Input: grid = [[1,1],[1,0]]
Output: 4
Explanation: Change the 0 to 1 and make the island bigger, only one island with area = 4.

Example 3:

Input: grid = [[1,1],[1,1]]
Output: 4
Explanation: Can't change any 0 to 1, only one island with area = 4.

Constraints:

n == grid.length
n == grid[i].length
1 <= n <= 500
grid[i][j] is either 0 or 1.
 */

#include <iostream>
#include <vector>
#include <algorithm
#include <unordered_set>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

std::vector<int> dir_r = {0, -1, 0, 1};
std::vector<int> dir_c = {-1, 0, 1, 0};

class UnionFind
{
public:
    UnionFind(int n) : parent(n * n), size(n * n, 1)
    {
        for (int i = 0; i < n * n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (size[rootX] < size[rootY])
            {
                std::swap(rootX, rootY);
            }
            parent[rootY] = rootX;
            size[rootX] += size[rootY];
        }
    }

    int getSize(int x)
    {
        return size[find(x)];
    }

private:
    std::vector<int> parent;
    std::vector<int> size;
};

class Solution
{
public:
    int largestIsland(vector<vector<int>>& grid)
    {
        int n = grid.size();
        UnionFind uf(n);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 1)
                {
                    for (int dir = 0; dir < 4; dir++)
                    {
                        int next_r = i + dir_r[dir];
                        int next_c = j + dir_c[dir];
                        if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < n && grid[next_r][next_c] == 1)
                        {
                            uf.unite(i * n + j, next_r * n + next_c);
                        }
                    }
                }
            }
        }

        int res = 0;
        bool has_zero = false;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (grid[i][j] == 0)
                {
                    has_zero = true;
                    std::unordered_set<int> visited_roots;
                    int potential_size = 1; // Start with the flipped cell itself

                    for (int dir = 0; dir < 4; dir++)
                    {
                        int next_r = i + dir_r[dir];
                        int next_c = j + dir_c[dir];
                        if (next_r >= 0 && next_r < n && next_c >= 0 && next_c < n && grid[next_r][next_c] == 1)
                        {
                            int root = uf.find(next_r * n + next_c);
                            if (visited_roots.find(root) == visited_roots.end())
                            {
                                visited_roots.insert(root);
                                potential_size += uf.getSize(root);
                            }
                        }
                    }

                    res = std::max(res, potential_size);
                }
            }
        }

        return has_zero ? res : n * n;
    }
};

int main()
{
    Solution sol;
    vector<vector<int>> grid = {{1, 0}, {0, 1}};
    std::cout << sol.largestIsland(grid) << std::endl;
    return 0;
}