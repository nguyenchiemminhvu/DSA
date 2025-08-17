/**
https://leetcode.com/problems/count-days-without-meetings/description/
 */

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int countDays(int days, vector<vector<int>>& meetings)
    {
        std::sort(meetings.begin(), meetings.end());
        std::vector<std::vector<int>> new_meetings;
        new_meetings.push_back(meetings[0]);

        for (int i = 1; i < meetings.size(); i++)
        {
            if (meetings[i][0] <= new_meetings.back()[1])
            {
                new_meetings.back()[1] = std::max(new_meetings.back()[1], meetings[i][1]);
            }
            else
            {
                new_meetings.push_back(meetings[i]);
            }
        }

        int count = 0;
        int prev = 1;
        for (int i = 0; i < new_meetings.size(); i++)
        {
            if (prev < new_meetings[i][0])
            {
                count += new_meetings[i][0] - prev;
            }

            prev = new_meetings[i][1] + 1;
        }

        if (prev <= days)
        {
            count += days - prev + 1;
        }
        return count;
    }
};

int main()
{
    Solution sol;
    int days = 10;
    vector<vector<int>> meetings = {{1, 2}, {4, 5}, {7, 8}};
    cout << "Days without meetings: " << sol.countDays(days, meetings) << endl;

    // Example Input:
    // days = 10
    // meetings = {{1, 2}, {4, 5}, {7, 8}}
    // Output:
    // Days without meetings: 4
    return 0;
}