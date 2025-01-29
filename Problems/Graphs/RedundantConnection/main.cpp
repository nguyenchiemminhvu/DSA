/**
https://leetcode.com/problems/redundant-connection/description/

In this problem, a tree is an undirected graph that is connected and has no cycles.

You are given a graph that started as a tree with n nodes labeled from 1 to n, with one additional edge added. The added edge has two different vertices chosen from 1 to n, and was not an edge that already existed. The graph is represented as an array edges of length n where edges[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the graph.

Return an edge that can be removed so that the resulting graph is a tree of n nodes. If there are multiple answers, return the answer that occurs last in the input.

Example 1:

Input: edges = [[1,2],[1,3],[2,3]]
Output: [2,3]
Example 2:

Input: edges = [[1,2],[2,3],[3,4],[1,4],[1,5]]
Output: [1,4]

Constraints:

n == edges.length
3 <= n <= 1000
edges[i].length == 2
1 <= ai < bi <= edges.length
ai != bi
There are no repeated edges.
The given graph is connected.
 */

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class DSU
{
private:
    std::vector<int> parent;
    std::vector<int> rank;

public:
    DSU(int n)
    {
        parent.resize(n);
        rank.resize(n, 1);
        for (int i = 0; i < n; ++i)
        {
            parent[i] = i;
        }
    }

    int Find(int x)
    {
        if (parent[x] != x)
        {
            parent[x] = Find(parent[x]);
        }
        return parent[x];
    }

    void Union(int x, int y)
    {
        int rootX = Find(x);
        int rootY = Find(y);

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
                rank[rootX] += 1; // Increase rank if ranks are equal
            }
        }
    }

    bool Connected(int x, int y)
    {
        return Find(x) == Find(y);
    }
};

class Solution
{
public:
    vector<int> findRedundantConnection(vector<vector<int>>& edges)
    {
        std::vector<int> redundant;

        int n = 0;
        for (const std::vector<int>& edge : edges)
        {
            n = std::max(n, std::max(edge[0], edge[1]));
        }
        DSU dsu(n + 1);

        for (const std::vector<int>& edge : edges)
        {
            if (!dsu.Connected(edge[0], edge[1]))
            {
                dsu.Union(edge[0], edge[1]);
            }
            else
            {
                redundant = edge;
            }
        }

        return redundant;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> edges = {
        {1, 2},
        {1, 3},
        {2, 3}
    };
    std::vector<int> redundant_edge = sol.findRedundantConnection(edges);
    for (int i = 0; i < redundant_edge.size(); ++i)
    {
        std::cout << redundant_edge[i] << " ";
    }
    return 0;
}