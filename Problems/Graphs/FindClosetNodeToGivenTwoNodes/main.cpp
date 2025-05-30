// https://leetcode.com/problems/find-closest-node-to-given-two-nodes/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int closestMeetingNode(vector<int>& edges, int node1, int node2)
    {
        auto f_shortest_path = [&](int start) -> std::vector<int>
        {
            std::vector<int> dist(edges.size(), INT_MAX);
            dist[start] = 0;

            std::queue<int> q;
            q.push(start);
            
            while (!q.empty())
            {
                int node = q.front();
                q.pop();
                int next_node = edges[node];
                if (next_node != -1 && dist[next_node] == INT_MAX)
                {
                    dist[next_node] = std::min(dist[next_node], dist[node] + 1);
                    q.push(next_node);
                }
            }

            return dist;
        };

        std::vector<int> dist_1 = f_shortest_path(node1);
        std::vector<int> dist_2 = f_shortest_path(node2);

        int min_max_dist = INT_MAX;
        int result_node = -1;
        for (int i = 0; i < edges.size(); i++)
        {
            if (dist_1[i] != INT_MAX && dist_2[i] != INT_MAX)
            {
                int max_dist = std::max(dist_1[i], dist_2[i]);
                if (max_dist < min_max_dist)
                {
                    min_max_dist = max_dist;
                    result_node = i;
                }
                else if (max_dist == min_max_dist && i < result_node)
                {
                    result_node = i;
                }
            }
        }

        return result_node;
    }
};

int main()
{
    Solution solution;
    vector<int> edges = {2, 2, 3, -1, 5, 0};
    int node1 = 0;
    int node2 = 1;
    int result = solution.closestMeetingNode(edges, node1, node2);
    cout << "Closest meeting node: " << result << endl;
    return 0;
}