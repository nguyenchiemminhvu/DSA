/**
https://leetcode.com/problems/minimum-time-difference/

Given a list of 24-hour clock time points in "HH:MM" format, return the minimum minutes difference between any two time-points in the list.

Example 1:

Input: timePoints = ["23:59","00:00"]
Output: 1

Example 2:

Input: timePoints = ["00:00","23:59","00:00"]
Output: 0

Constraints:

2 <= timePoints.length <= 2 * 104
timePoints[i] is in the format "HH:MM".
*/

#include <iostream>
#include <string>
#include <vector>
#include <climits>
#include <algorithm>

using namespace std;

auto init = []() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    return 'c';
}();

class Solution
{
public:
    int findMinDifference(vector<string>& timePoints)
    {
        int res = INT_MAX;

        std::vector<int> timestamps(timePoints.size(), 0);
        for (int i = 0; i < timePoints.size(); i++)
        {
            timestamps[i] = toTimestamp(timePoints[i]);
        }

        std::sort(timestamps.begin(), timestamps.end());

        for (int i = 1; i < timestamps.size(); i++)
        {
            res = std::min(res, timestamps[i] - timestamps[i - 1]);
        }

        res = std::min(res, 1440 - (timestamps.back() - timestamps.front()));

        return res;
    }
private:
    int toTimestamp(const std::string& s)
    {
        int hh = std::stoi(s.substr(0, 2));
        int mm = std::stoi(s.substr(3, 2));
        return hh * 60 + mm;
    }
};

int main()
{
    Solution sol;
    std::vector<std::string> timePoints = {
        "00:00",
        "23:59",
        "00:00"
    };
    std::cout << sol.findMinDifference(timePoints) << std::endl;
    return 0;
}