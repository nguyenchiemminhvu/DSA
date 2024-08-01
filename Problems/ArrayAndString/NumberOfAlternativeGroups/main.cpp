/**
https://leetcode.com/problems/alternating-groups-i/

There is a circle of red and blue tiles. You are given an array of integers colors. The color of tile i is represented by colors[i]:

colors[i] == 0 means that tile i is red.
colors[i] == 1 means that tile i is blue.
Every 3 contiguous tiles in the circle with alternating colors (the middle tile has a different color from its left and right tiles) is called an alternating group.

Return the number of alternating groups.
Note that since colors represents a circle, the first and the last tiles are considered to be next to each other.

Example 1:

Input: colors = [1,1,1]
Output: 0

Example 2:

Input: colors = [0,1,0,0,1]
Output: 3

Constraints:

3 <= colors.length <= 100
0 <= colors[i] <= 1
*/

#include <iostream>
#include <vector>

class Solution
{
public:
    int numberOfAlternatingGroups(std::vector<int>& colors)
    {
        int count = 0;
        int n = colors.size();
        for (int i = 0; i < n; i++)
        {
            if (colors[i] != colors[left_idx(n, i)] && colors[i] != colors[right_idx(n, i)])
            {
                count++;
            }
        }

        return count;
    }
private:
    int left_idx(int n, int i)
    {
        i = ((i + n) - 1) % n;
        return i;
    }

    int right_idx(int n, int i)
    {
        i = (i + 1) % n;
        return i;
    }
};

int main()
{
    Solution sol;
    std::vector<int> input;
    std::cout << sol.numberOfAlternatingGroups(input) << std::endl;
    
    return 0;
}