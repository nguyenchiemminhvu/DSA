/**
https://leetcode.com/problems/shortest-distance-after-road-addition-queries-i/description/

You are given an integer n and a 2D integer array queries.

There are n cities numbered from 0 to n - 1. Initially, there is a unidirectional road from city i to city i + 1 for all 0 <= i < n - 1.

queries[i] = [ui, vi] represents the addition of a new unidirectional road from city ui to city vi. After each query, you need to find the length of the shortest path from city 0 to city n - 1.

Return an array answer where for each i in the range [0, queries.length - 1], answer[i] is the length of the shortest path from city 0 to city n - 1 after processing the first i + 1 queries.

Example 1:

Input: n = 5, queries = [[2,4],[0,2],[0,4]]

Output: [3,2,1]

Explanation:

After the addition of the road from 2 to 4, the length of the shortest path from 0 to 4 is 3.

After the addition of the road from 0 to 2, the length of the shortest path from 0 to 4 is 2.

After the addition of the road from 0 to 4, the length of the shortest path from 0 to 4 is 1.

Example 2:

Input: n = 4, queries = [[0,3],[0,2]]

Output: [1,1]

Explanation:

After the addition of the road from 0 to 3, the length of the shortest path from 0 to 3 is 1.

After the addition of the road from 0 to 2, the length of the shortest path remains 1.

Constraints:

3 <= n <= 500
1 <= queries.length <= 500
queries[i].length == 2
0 <= queries[i][0] < queries[i][1] < n
1 < queries[i][1] - queries[i][0]
There are no repeated roads among the queries.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return 0;
}();

class Solution
{
public:
    vector<int> shortestDistanceAfterQueries(int n, vector<vector<int>>& queries)
    {
        std::vector<int> res;

        std::unordered_map<int, std::vector<int>> adj_map;
        for (int i = 1; i < n; i++)
        {
            adj_map[i - 1].push_back(i);
        }

        for (const std::vector<int>& query : queries)
        {
            adj_map[query[0]].push_back(query[1]);
            res.push_back(min_distance(0, n - 1, adj_map));
        }

        return res;
    }
private:
    int min_distance(int start, int end, std::unordered_map<int, std::vector<int>>& adj_map)
    {
        int moves = 0;
        std::queue<int> q;
        q.push(start);

        std::unordered_map<int, bool> visited;
        visited[start] = true;

        while (!q.empty())
        {
            int n = q.size();
            for (int i = 0; i < n; i++)
            {
                int cur = q.front();
                q.pop();

                if (cur == end)
                {
                    return moves;
                }

                for (const int& next : adj_map[cur])
                {
                    if (!visited[next])
                    {
                        visited[next] = true;
                        q.push(next);
                    }
                }
            }

            moves++;
        }

        return -1;
    }
};

int main()
{
    Solution sol;
    int n = 5;
    std::vector<std::vector<int>> queries = {
        {2, 4},
        {0, 2},
        {0, 4}
    };
    std::vector<int> res = sol.shortestDistanceAfterQueries(n, queries);
    for (int n : res)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}