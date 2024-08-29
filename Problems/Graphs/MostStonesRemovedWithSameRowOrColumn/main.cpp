/**
https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/

On a 2D plane, we place n stones at some integer coordinate points. Each coordinate point may have at most one stone.
A stone can be removed if it shares either the same row or the same column as another stone that has not been removed.
Given an array stones of length n where stones[i] = [xi, yi] represents the location of the ith stone, return the largest possible number of stones that can be removed.

Example 1:

Input: stones = [[0,0],[0,1],[1,0],[1,2],[2,1],[2,2]]
Output: 5
Explanation: One way to remove 5 stones is as follows:
1. Remove stone [2,2] because it shares the same row as [2,1].
2. Remove stone [2,1] because it shares the same column as [0,1].
3. Remove stone [1,2] because it shares the same row as [1,0].
4. Remove stone [1,0] because it shares the same column as [0,0].
5. Remove stone [0,1] because it shares the same row as [0,0].
Stone [0,0] cannot be removed since it does not share a row/column with another stone still on the plane.

Example 2:

Input: stones = [[0,0],[0,2],[1,1],[2,0],[2,2]]
Output: 3
Explanation: One way to make 3 moves is as follows:
1. Remove stone [2,2] because it shares the same row as [2,0].
2. Remove stone [2,0] because it shares the same column as [0,0].
3. Remove stone [0,2] because it shares the same row as [0,0].
Stones [0,0] and [1,1] cannot be removed since they do not share a row/column with another stone still on the plane.

Example 3:

Input: stones = [[0,0]]
Output: 0
Explanation: [0,0] is the only stone on the plane, so you cannot remove it.

Constraints:

1 <= stones.length <= 1000
0 <= xi, yi <= 104
No two stones are at the same coordinate point.
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>

using namespace std;

class UnionFind
{
public:
    UnionFind(int n) : parent(n), rank(n, 0)
    {
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = find(parent[x]); // Path compression
        }
        return parent[x];
    }

    void unite(int x, int y)
    {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY)
        {
            if (rank[rootX] > rank[rootY])
            {
                parent[rootY] = rootX;
            }
            else if (rank[rootX] < rank[rootY])
            {
                parent[rootX] = rootY;
            }
            else
            {
                parent[rootY] = rootX;
                rank[rootX]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

class Solution
{
public:
    int removeStones(vector<vector<int>>& coordinates)
    {
        int res = 0;
        int n = coordinates.size();
        UnionFind uf(n);

        unordered_map<int, vector<int>> rowMap, colMap;

        for (int i = 0; i < n; ++i)
        {
            int row = coordinates[i][0];
            int col = coordinates[i][1];
            rowMap[row].push_back(i);
            colMap[col].push_back(i);
        }

        for (const auto& row : rowMap)
        {
            for (int i = 1; i < row.second.size(); ++i)
            {
                uf.unite(row.second[0], row.second[i]);
            }
        }

        for (const auto& col : colMap)
        {
            for (int i = 1; i < col.second.size(); ++i)
            {
                uf.unite(col.second[0], col.second[i]);
            }
        }

        unordered_map<int, vector<std::vector<int>>> clusters;
        for (int i = 0; i < n; ++i)
        {
            int root = uf.find(i);
            clusters[root].push_back(coordinates[i]);
        }

        for (const auto& cluster : clusters)
        {
            res += cluster.second.size() - 1;
        }
        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> stones = {
        {0,0},
        {0,1},
        {1,0},
        {1,2},
        {2,1},
        {2,2}
    };
    std::cout << sol.removeStones(stones) << std::endl;
    return 0;
}