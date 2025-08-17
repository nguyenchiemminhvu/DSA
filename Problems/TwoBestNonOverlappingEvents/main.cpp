/**
https://leetcode.com/problems/two-best-non-overlapping-events/description/

You are given a 0-indexed 2D integer array of events where events[i] = [startTimei, endTimei, valuei]. The ith event starts at startTimei and ends at endTimei, and if you attend this event, you will receive a value of valuei. You can choose at most two non-overlapping events to attend such that the sum of their values is maximized.

Return this maximum sum.

Note that the start time and end time is inclusive: that is, you cannot attend two events where one of them starts and the other ends at the same time. More specifically, if you attend an event with end time t, the next event must start at or after t + 1.

Example 1:

Input: events = [[1,3,2],[4,5,2],[2,4,3]]
Output: 4
Explanation: Choose the green events, 0 and 1 for a sum of 2 + 2 = 4.

Example 2:

Example 1 Diagram
Input: events = [[1,3,2],[4,5,2],[1,5,5]]
Output: 5
Explanation: Choose event 2 for a sum of 5.

Example 3:


Input: events = [[1,5,3],[1,5,1],[6,6,5]]
Output: 8
Explanation: Choose events 0 and 2 for a sum of 3 + 5 = 8.

Constraints:

2 <= events.length <= 105
events[i].length == 3
1 <= startTimei <= endTimei <= 109
1 <= valuei <= 106
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
    int maxTwoEvents(vector<vector<int>>& events)
    {
        std::sort(
            events.begin(),
            events.end(),
            [](const auto& a, const auto& b)
            {
                return a[1] < b[1];
            }
        );

        std::vector<int> max_values(events.size(), 0);
        max_values[0] = events[0][2];
        for (int i = 1; i < events.size(); i++)
        {
            max_values[i] = std::max(max_values[i - 1], events[i][2]);
        }

        int res = 0;
        for (int i = 0; i < events.size(); i++)
        {
            res = std::max(res, events[i][2]);

            int start_time = events[i][0];
            int left = 0;
            int right = i - 1;
            int pick_idx = -1;
            while (left <= right)
            {
                int mid = left + (right - left) / 2;

                if (events[mid][1] < start_time)
                {
                    pick_idx = mid;
                    left = mid + 1;
                }
                else
                {
                    right = mid - 1;
                }
            }

            if (pick_idx != -1)
            {
                res = std::max(res, events[i][2] + max_values[pick_idx]);
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> events = {
        {1,5,3},
        {1,5,1},
        {6,6,5}
    };
    std::cout << sol.maxTwoEvents(events) << std::endl;
    return 0;
}