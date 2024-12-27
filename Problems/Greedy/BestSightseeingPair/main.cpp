/**
https://leetcode.com/problems/best-sightseeing-pair/description/

You are given an integer array values where values[i] represents the value of the ith sightseeing spot. Two sightseeing spots i and j have a distance j - i between them.

The score of a pair (i < j) of sightseeing spots is values[i] + values[j] + i - j: the sum of the values of the sightseeing spots, minus the distance between them.

Return the maximum score of a pair of sightseeing spots.

Example 1:

Input: values = [8,1,5,2,6]
Output: 11
Explanation: i = 0, j = 2, values[i] + values[j] + i - j = 8 + 5 + 0 - 2 = 11

Example 2:

Input: values = [1,2]
Output: 2

Constraints:

2 <= values.length <= 5 * 104
1 <= values[i] <= 1000
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int maxScoreSightseeingPair(vector<int>& values)
    {
        std::vector<int> cur_max(values.begin(), values.end());
        for (int i = 1; i < cur_max.size(); i++)
        {
            cur_max[i] += i;
            cur_max[i] = std::max(cur_max[i], cur_max[i - 1]);
        }

        int res = 0;
        for (int i = 1; i < values.size(); i++)
        {
            res = std::max(res, values[i] - i + cur_max[i - 1]);
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> values = { 8,1,5,2,6 };
    std::cout << sol.maxScoreSightseeingPair(values) << std::endl;
    return 0;
}