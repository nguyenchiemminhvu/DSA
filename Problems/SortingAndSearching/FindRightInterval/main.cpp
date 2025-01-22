/**
https://leetcode.com/problems/find-right-interval/description/

You are given an array of intervals, where intervals[i] = [starti, endi] and each starti is unique.

The right interval for an interval i is an interval j such that startj >= endi and startj is minimized. Note that i may equal j.

Return an array of right interval indices for each interval i. If no right interval exists for interval i, then put -1 at index i.

Example 1:

Input: intervals = [[1,2]]
Output: [-1]
Explanation: There is only one interval in the collection, so it outputs -1.

Example 2:

Input: intervals = [[3,4],[2,3],[1,2]]
Output: [-1,0,1]
Explanation: There is no right interval for [3,4].
The right interval for [2,3] is [3,4] since start0 = 3 is the smallest start that is >= end1 = 3.
The right interval for [1,2] is [2,3] since start1 = 2 is the smallest start that is >= end2 = 2.

Example 3:

Input: intervals = [[1,4],[2,3],[3,4]]
Output: [-1,2,-1]
Explanation: There is no right interval for [1,4] and [3,4].
The right interval for [2,3] is [3,4] since start2 = 3 is the smallest start that is >= end1 = 3.

Constraints:

1 <= intervals.length <= 2 * 104
intervals[i].length == 2
-106 <= starti <= endi <= 106
The start point of each interval is unique.
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>
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
    vector<int> findRightInterval(vector<vector<int>>& intervals)
    {
        std::vector<int> res;

        std::vector<std::pair<int, int>> starts;
        for (int i = 0; i < intervals.size(); i++)
        {
            starts.push_back({intervals[i][0], i});
        }

        std::sort(starts.begin(), starts.end());

        for (int i = 0; i < intervals.size(); i++)
        {
            int end = intervals[i][1];

            int found = -1;
            int left = 0;
            int right = intervals.size() - 1;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;

                if (starts[mid].first >= end)
                {
                    found = starts[mid].second;
                    right = mid - 1;
                }
                else
                {
                    left = mid + 1;
                }
            }

            if (found != -1)
            {
                res.push_back(found);
            }
            else
            {
                res.push_back(-1);
            }
        }

        return res;    
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> intervals = {{1, 2}, {2, 3}, {3, 4}};
    std::vector<int> res = sol.findRightInterval(intervals);
    for (int i : res)
    {
        std::cout << i << " ";
    }
    std::cout << std::endl;
    return 0;
}