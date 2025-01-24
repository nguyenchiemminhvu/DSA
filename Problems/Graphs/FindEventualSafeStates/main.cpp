/**
https://leetcode.com/problems/find-eventual-safe-states/description/

There is a directed graph of n nodes with each node labeled from 0 to n - 1. The graph is represented by a 0-indexed 2D integer array graph where graph[i] is an integer array of nodes adjacent to node i, meaning there is an edge from node i to each node in graph[i].

A node is a terminal node if there are no outgoing edges. A node is a safe node if every possible path starting from that node leads to a terminal node (or another safe node).

Return an array containing all the safe nodes of the graph. The answer should be sorted in ascending order.

Example 1:

Illustration of graph
Input: graph = [[1,2],[2,3],[5],[0],[5],[],[]]
Output: [2,4,5,6]
Explanation: The given graph is shown above.
Nodes 5 and 6 are terminal nodes as there are no outgoing edges from either of them.
Every path starting at nodes 2, 4, 5, and 6 all lead to either node 5 or 6.

Example 2:

Input: graph = [[1,2,3,4],[1,2],[3,4],[0,4],[]]
Output: [4]
Explanation:
Only node 4 is a terminal node, and every path starting at node 4 leads to node 4.

Constraints:

n == graph.length
1 <= n <= 104
0 <= graph[i].length <= n
0 <= graph[i][j] <= n - 1
graph[i] is sorted in a strictly increasing order.
The graph may contain self-loops.
The number of edges in the graph will be in the range [1, 4 * 104].
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_set>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<int> eventualSafeNodes(vector<vector<int>>& graph)
    {
        std::unordered_set<int> safe_set;
        std::vector<int> visited(graph.size(), 0); // 0 = unvisited, 1 = visiting, 2 = visited

        for (int i = 0; i < graph.size(); i++)
        {
            if (DFS(graph, i, visited))
            {
                safe_set.insert(i);
            }
        }

        std::vector<int> safe_nodes(safe_set.begin(), safe_set.end());
        std::sort(safe_nodes.begin(), safe_nodes.end());
        return safe_nodes;
    }

private:
    bool DFS(const std::vector<std::vector<int>>& graph, int start, std::vector<int>& visited)
    {
        if (visited[start] == 1) // Node is currently being visited (cycle found)
        {
            return false;
        }

        if (visited[start] == 2) // Node has been completely processed
        {
            return true;
        }

        visited[start] = 1;
        for (int adj : graph[start])
        {
            if (!DFS(graph, adj, visited))
            {
                return false;
            }
        }
        visited[start] = 2;

        return true;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> graph = {{1, 2}, {2, 3}, {5}, {0}, {5}, {}, {}};
    std::vector<int> res = sol.eventualSafeNodes(graph);
    for (int node : res)
    {
        std::cout << node << " ";
    }
    std::cout << std::endl;
    return 0;
}