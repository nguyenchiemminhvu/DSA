/**
https://leetcode.com/problems/number-of-ways-to-arrive-at-destination/description/

You are in a city that consists of n intersections numbered from 0 to n - 1 with bi-directional roads between some intersections. The inputs are generated such that you can reach any intersection from any other intersection and that there is at most one road between any two intersections.

You are given an integer n and a 2D integer array roads where roads[i] = [ui, vi, timei] means that there is a road between intersections ui and vi that takes timei minutes to travel. You want to know in how many ways you can travel from intersection 0 to intersection n - 1 in the shortest amount of time.

Return the number of ways you can arrive at your destination in the shortest amount of time. Since the answer may be large, return it modulo 109 + 7.

Example 1:

Input: n = 7, roads = [[0,6,7],[0,1,2],[1,2,3],[1,3,3],[6,3,3],[3,5,1],[6,5,1],[2,5,1],[0,4,5],[4,6,2]]
Output: 4
Explanation: The shortest amount of time it takes to go from intersection 0 to intersection 6 is 7 minutes.
The four ways to get there in 7 minutes are:
- 0 ➝ 6
- 0 ➝ 4 ➝ 6
- 0 ➝ 1 ➝ 2 ➝ 5 ➝ 6
- 0 ➝ 1 ➝ 3 ➝ 5 ➝ 6

Example 2:

Input: n = 2, roads = [[1,0,10]]
Output: 1
Explanation: There is only one way to go from intersection 0 to intersection 1, and it takes 10 minutes.
 */

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MOD (1000000007)
using ll = long long;
using pii = std::pair<int, int>;
using pll = std::pair<long long, long long>;

class Solution
{
public:
    int countPaths(int n, vector<vector<int>>& roads)
    {
        std::unordered_map<int, std::vector<pll>> graph;
        for (const std::vector<int>& road : roads)
        {
            graph[road[0]].push_back(std::make_pair(road[2], road[1]));
            graph[road[1]].push_back(std::make_pair(road[2], road[0]));
        }

        std::vector<ll> dist(n, LONG_MAX);
        std::vector<ll> ways(n, 0);
        dist[0] = 0;
        ways[0] = 1;

        std::priority_queue<pll, std::vector<pll>, std::greater<pll>> pq;
        pq.push({0, 0});

        while (!pq.empty())
        {
            pii cur = pq.top();
            pq.pop();

            if (cur.first > dist[cur.second])
            {
                continue;
            }

            const std::vector<pll>& adj_nodes = graph[cur.second];
            for (const pll& node : adj_nodes)
            {
                if (dist[cur.second] + node.first < dist[node.second])
                {
                    dist[node.second] = dist[cur.second] + node.first;
                    ways[node.second] = ways[cur.second];
                    pq.push({dist[node.second], node.second});
                }
                else if (dist[cur.second] + node.first == dist[node.second])
                {
                    ways[node.second] = (ways[cur.second] % MOD + ways[node.second] % MOD) % MOD;
                }
            }
        }

        // for (int i = 0; i < n; i++)
        //     std::cout << i << " ";
        // std::cout << std::endl;

        // for (int val : dist)
        //     std::cout << val << " ";
        // std::cout << std::endl;

        // for (int val : ways)
        //     std::cout << val << " ";
        // std::cout << std::endl;

        return ways[n - 1];
    }
};

int main()
{
    Solution sol;
    int n = 7;
    vector<vector<int>> roads = {
        {0, 6, 7}, {0, 1, 2}, {1, 2, 3}, {1, 3, 3}, {6, 3, 3},
        {3, 5, 1}, {6, 5, 1}, {2, 5, 1}, {0, 4, 5}, {4, 6, 2}};
    cout << "Number of ways: " << sol.countPaths(n, roads) << endl;
    return 0;
}