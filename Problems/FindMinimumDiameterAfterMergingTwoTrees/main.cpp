/**
https://leetcode.com/problems/find-minimum-diameter-after-merging-two-trees/description/

There exist two undirected trees with n and m nodes, numbered from 0 to n - 1 and from 0 to m - 1, respectively. You are given two 2D integer arrays edges1 and edges2 of lengths n - 1 and m - 1, respectively, where edges1[i] = [ai, bi] indicates that there is an edge between nodes ai and bi in the first tree and edges2[i] = [ui, vi] indicates that there is an edge between nodes ui and vi in the second tree.

You must connect one node from the first tree with another node from the second tree with an edge.

Return the minimum possible diameter of the resulting tree.

The diameter of a tree is the length of the longest path between any two nodes in the tree.

Example 1:

Input: edges1 = [[0,1],[0,2],[0,3]], edges2 = [[0,1]]

Output: 3

Explanation:

We can obtain a tree of diameter 3 by connecting node 0 from the first tree with any node from the second tree.

Example 2:

Input: edges1 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]], edges2 = [[0,1],[0,2],[0,3],[2,4],[2,5],[3,6],[2,7]]

Output: 5

Explanation:

We can obtain a tree of diameter 5 by connecting node 0 from the first tree with node 0 from the second tree.

Constraints:

1 <= n, m <= 105
edges1.length == n - 1
edges2.length == m - 1
edges1[i].length == edges2[i].length == 2
edges1[i] = [ai, bi]
0 <= ai, bi < n
edges2[i] = [ui, vi]
0 <= ui, vi < m
The input is generated such that edges1 and edges2 represent valid trees.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <queue>
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
    int minimumDiameterAfterMerge(std::vector<std::vector<int>>& edges1, std::vector<std::vector<int>>& edges2)
    {
        std::vector<std::vector<int>> graph1(edges1.size() + 1);
        std::vector<std::vector<int>> graph2(edges2.size() + 1);

        for (const std::vector<int>& edge : edges1)
        {
            graph1[edge[0]].push_back(edge[1]);
            graph1[edge[1]].push_back(edge[0]);
        }

        for (const std::vector<int>& edge : edges2)
        {
            graph2[edge[0]].push_back(edge[1]);
            graph2[edge[1]].push_back(edge[0]);
        }

        int d1 = diameter(graph1);
        int d2 = diameter(graph2);

        int res = std::max(d1, d2);
        res = std::max(res, (d1 + 1) / 2 + (d2 + 1) / 2 + 1);
        return res;
    }

private:
    int diameter(const std::vector<std::vector<int>>& graph)
    {
        if (graph.size() <= 1)
            return 0;

        std::pair<int, int> farthest = bfs(graph, 0);
        std::pair<int, int> farthestFromFarthest = bfs(graph, farthest.first);

        return farthestFromFarthest.second;
    }

    std::pair<int, int> bfs(const std::vector<std::vector<int>>& graph, int start)
    {
        std::pair<int, int> res = {start, 0};

        std::queue<int> Q;
        Q.push(start);

        std::vector<bool> visited(graph.size(), false);
        visited[start] = true;

        int distance = 0;

        while (!Q.empty())
        {
            int q_size = Q.size();
            for (int i = 0; i < q_size; i++)
            {
                int cur = Q.front();
                Q.pop();

                for (int adj : graph[cur])
                {
                    if (!visited[adj])
                    {
                        visited[adj] = true;
                        Q.push(adj);
                        res = {adj, distance + 1};
                    }
                }
            }

            distance++;
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> edges1 = {
        {0,1},
        {0,2},
        {0,3},
    };
    std::vector<std::vector<int>> edges2 = {
        {0,1}
    };
    std::cout << sol.minimumDiameterAfterMerge(edges1, edges2) << std::endl;

    return 0;   
}