/**
https://leetcode.com/problems/course-schedule-iv/description/

There are a total of numCourses courses you have to take, labeled from 0 to numCourses - 1. You are given an array prerequisites where prerequisites[i] = [ai, bi] indicates that you must take course ai first if you want to take course bi.

For example, the pair [0, 1] indicates that you have to take course 0 before you can take course 1.
Prerequisites can also be indirect. If course a is a prerequisite of course b, and course b is a prerequisite of course c, then course a is a prerequisite of course c.

You are also given an array queries where queries[j] = [uj, vj]. For the jth query, you should answer whether course uj is a prerequisite of course vj or not.

Return a boolean array answer, where answer[j] is the answer to the jth query.

Example 1:

Input: numCourses = 2, prerequisites = [[1,0]], queries = [[0,1],[1,0]]
Output: [false,true]
Explanation: The pair [1, 0] indicates that you have to take course 1 before you can take course 0.
Course 0 is not a prerequisite of course 1, but the opposite is true.

Example 2:

Input: numCourses = 2, prerequisites = [], queries = [[1,0],[0,1]]
Output: [false,false]
Explanation: There are no prerequisites, and each course is independent.

Example 3:

Input: numCourses = 3, prerequisites = [[1,2],[1,0],[2,0]], queries = [[1,0],[1,2]]
Output: [true,true]

Constraints:

2 <= numCourses <= 100
0 <= prerequisites.length <= (numCourses * (numCourses - 1) / 2)
prerequisites[i].length == 2
0 <= ai, bi <= numCourses - 1
ai != bi
All the pairs [ai, bi] are unique.
The prerequisites graph has no cycles.
1 <= queries.length <= 104
0 <= ui, vi <= numCourses - 1
ui != vi
 */

#include <iostream>
#include <vector>
#include <algorithm>
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
    vector<bool> checkIfPrerequisite(int numCourses, vector<vector<int>>& prerequisites, vector<vector<int>>& queries)
    {
        std::vector<bool> res;

        std::vector<std::vector<int>> graph(numCourses, std::vector<int>(numCourses, 0));
        for (const std::vector<int>& pre : prerequisites)
        {
            graph[pre[0]][pre[1]] = 1;
        }

        for (int mid = 0; mid < numCourses; mid++)
        {
            for (int i = 0; i < numCourses; i++)
            {
                if (graph[i][mid] == 0)
                {
                    continue;
                }

                for (int j = 0; j < numCourses; j++)
                {
                    if (graph[mid][j] == 0)
                    {
                        continue;
                    }

                    graph[i][j] = 1;
                }
            }
        }

        for (const std::vector<int>& query : queries)
        {
            res.push_back(graph[query[0]][query[1]]);
        }

        return res;        
    }
};

int main()
{
    Solution sol;
    int n = 3;
    std::vector<std::vector<int>> pre = {{1, 2}, {1, 0}, {2, 0}};
    std::vector<std::vector<int>> queries = {{1, 0}, {1, 2}};
    std::vector<bool> res = sol.checkIfPrerequisite(n, pre, queries);
    for (bool b : res)
    {
        std::cout << b << " ";
    }
    return 0;
}