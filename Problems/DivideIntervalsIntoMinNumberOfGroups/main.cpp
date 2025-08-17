/**
You are given a 2D integer array intervals where intervals[i] = [lefti, righti] represents the inclusive interval [lefti, righti].
You have to divide the intervals into one or more groups such that each interval is in exactly one group, and no two intervals that are in the same group intersect each other.
Return the minimum number of groups you need to make.
Two intervals intersect if there is at least one common number between them. For example, the intervals [1, 5] and [5, 8] intersect.

Example 1:

Input: intervals = [[5,10],[6,8],[1,5],[2,3],[1,10]]
Output: 3
Explanation: We can divide the intervals into the following groups:
- Group 1: [1, 5], [6, 8].
- Group 2: [2, 3], [5, 10].
- Group 3: [1, 10].
It can be proven that it is not possible to divide the intervals into fewer than 3 groups.

Example 2:

Input: intervals = [[1,3],[5,6],[8,10],[11,13]]
Output: 1
Explanation: None of the intervals overlap, so we can put all of them in one group.

Constraints:

1 <= intervals.length <= 105
intervals[i].length == 2
1 <= lefti <= righti <= 106
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

static bool fastIO = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

struct Slot
{
    int id;
    int start;
    int end;
};

class Solution
{
public:
    int minGroups(vector<vector<int>>& intervals)
    {
        int res = 1;
        std::vector<Slot> slots;
        std::priority_queue<int, std::vector<int>, std::greater<int>> free_slots;
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> occupied_slots;
        for (int i = 0; i < intervals.size(); i++)
        {
            free_slots.push(i);
            slots.push_back({i, intervals[i][0], intervals[i][1]});
        }

        std::sort(slots.begin(), slots.end(), [](const auto& s1, const auto& s2) {
            return s1.start < s2.start;
        });

        for (int i = 0; i < slots.size(); i++)
        {
            int cur_timestamp = slots[i].start;
            while (!occupied_slots.empty() && occupied_slots.top().first < cur_timestamp)
            {
                free_slots.push(occupied_slots.top().second);
                occupied_slots.pop();
            }

            occupied_slots.push({slots[i].end, free_slots.top()});
            free_slots.pop();

            res = std::max(res, (int)occupied_slots.size());
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<std::vector<int>> intervals = {
        {5,10},{6,8},{1,5},{2,3},{1,10}
    };
    std::cout << sol.minGroups(intervals) << std::endl;
    return 0;
}