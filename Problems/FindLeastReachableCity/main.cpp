/**
https://leetcode.com/problems/find-the-city-with-the-smallest-number-of-neighbors-at-a-threshold-distance/

There are n cities numbered from 0 to n-1. Given the array edges where edges[i] = [fromi, toi, weighti] represents a bidirectional and weighted edge between cities fromi and toi, and given the integer distanceThreshold.
Return the city with the smallest number of cities that are reachable through some path and whose distance is at most distanceThreshold, If there are multiple such cities, return the city with the greatest number.
Notice that the distance of a path connecting cities i and j is equal to the sum of the edges' weights along that path.

Example 1:

Input: n = 4, edges = [[0,1,3],[1,2,1],[1,3,4],[2,3,1]], distanceThreshold = 4
Output: 3
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 4 for each city are:
City 0 -> [City 1, City 2] 
City 1 -> [City 0, City 2, City 3] 
City 2 -> [City 0, City 1, City 3] 
City 3 -> [City 1, City 2] 
Cities 0 and 3 have 2 neighboring cities at a distanceThreshold = 4, but we have to return city 3 since it has the greatest number.

Example 2:

Input: n = 5, edges = [[0,1,2],[0,4,8],[1,2,3],[1,4,2],[2,3,1],[3,4,1]], distanceThreshold = 2
Output: 0
Explanation: The figure above describes the graph. 
The neighboring cities at a distanceThreshold = 2 for each city are:
City 0 -> [City 1] 
City 1 -> [City 0, City 4] 
City 2 -> [City 3, City 4] 
City 3 -> [City 2, City 4]
City 4 -> [City 1, City 2, City 3] 
The city 0 has 1 neighboring city at a distanceThreshold = 2.

Constraints:

2 <= n <= 100
1 <= edges.length <= n * (n - 1) / 2
edges[i].length == 3
0 <= fromi < toi < n
1 <= weighti, distanceThreshold <= 10^4
All pairs (fromi, toi) are distinct.
*/

#include <iostream>
#include <climits>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>

class Solution
{
public:
    int findTheCity(int n, std::vector<std::vector<int>>& edges, int distanceThreshold)
    {
        std::unordered_map<int, std::vector<std::pair<int, int>>> adj_list;
        for (const std::vector<int>& edge : edges)
        {
            adj_list[edge[0]].push_back({edge[2], edge[1]});
            adj_list[edge[1]].push_back({edge[2], edge[0]});
        }

        int res = -1;
        int min_count = INT_MAX;
        for (int i = 0; i < n; i++)
        {
            int count = count_reachable(n, adj_list, i, distanceThreshold);
            if (min_count > count)
            {
                min_count = count;
                res = i;
            }
            else if (min_count == count)
            {
                res = i;
            }
        }

        return res;
    }

private:
    int count_reachable(int n, std::unordered_map<int, std::vector<std::pair<int, int>>>& adj_list, int source, int limited)
    {
        std::unordered_set<int> res;

        std::vector<int> v_dist(n, INT_MAX);
        v_dist[source] = 0;

        std::priority_queue<std::pair<int, int>,
                            std::vector<std::pair<int, int>>,
                            std::greater<std::pair<int, int>>> PQ;
        PQ.push({0, source});

        while (!PQ.empty())
        {
            std::pair<int, int> cur = PQ.top();
            PQ.pop();

            if (cur.first > std::min(limited, v_dist[cur.second]))
            {
                continue;
            }

            res.insert(cur.second);

            const std::vector<std::pair<int, int>>& adj_with_cur = adj_list[cur.second];
            for (const std::pair<int, int>& next : adj_with_cur)
            {
                if (v_dist[next.second] > cur.first + next.first)
                {
                    v_dist[next.second] = cur.first + next.first;
                    PQ.push({v_dist[next.second], next.second});
                }
            }
        }

        return res.size();
    }
};

int main()
{
    Solution sol;
    int n = 4;
    std::vector<std::vector<int>> edges = {
        {0,1,3},
        {1,2,1},
        {1,3,4},
        {2,3,1}
    };
    std::cout << sol.findTheCity(n, edges, 4) << std::endl;
    return 0;
}