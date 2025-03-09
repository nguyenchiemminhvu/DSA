/**
https://leetcode.com/problems/alternating-groups-ii/

There is a circle of red and blue tiles. You are given an array of integers colors and an integer k. The color of tile i is represented by colors[i]:

colors[i] == 0 means that tile i is red.
colors[i] == 1 means that tile i is blue.
An alternating group is every k contiguous tiles in the circle with alternating colors (each tile in the group except the first and last one has a different color from its left and right tiles).

Return the number of alternating groups.

Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.

Example 1:

Input: colors = [0,1,0,1,0], k = 3

Output: 3

Example 2:

Input: colors = [0,1,0,0,1,0,1], k = 6

Output: 2

Example 3:

Input: colors = [1,1,0,1], k = 4

Output: 0

Constraints:

3 <= colors.length <= 105
0 <= colors[i] <= 1
3 <= k <= colors.length
 */

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int numberOfAlternatingGroups(vector<int>& colors, int k)
    {
        colors.insert(colors.end(), colors.begin(), colors.begin() + k - 1);

        std::vector<int> prefix(colors.size(), 1);
        for (int i = 1; i < colors.size(); i++)
        {
            if (colors[i] != colors[i - 1])
            {
                prefix[i] = prefix[i - 1] + 1;
            }
        }

        int count = 0;
        for (int i = 0; i < colors.size(); i++)
        {
            if (prefix[i] >= k)
            {
                count++;
            }
        }

        return count;
    }
};

int main()
{
    Solution sol;
    std::vector<int> colors = {0, 1, 0, 1, 0};
    int k = 3;
    std::cout << sol.numberOfAlternatingGroups(colors, k) << std::endl;
    return 0;
}