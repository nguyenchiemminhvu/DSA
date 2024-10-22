/**
https://leetcode.com/problems/largest-values-from-labels/

You are given n item's value and label as two integer arrays values and labels. You are also given two integers numWanted and useLimit.

Your task is to find a subset of items with the maximum sum of their values such that:

The number of items is at most numWanted.
The number of items with the same label is at most useLimit.
Return the maximum sum.

Example 1:

Input: values = [5,4,3,2,1], labels = [1,1,2,2,3], numWanted = 3, useLimit = 1

Output: 9

Explanation:

The subset chosen is the first, third, and fifth items with the sum of values 5 + 3 + 1.

Example 2:

Input: values = [5,4,3,2,1], labels = [1,3,3,3,2], numWanted = 3, useLimit = 2

Output: 12

Explanation:

The subset chosen is the first, second, and third items with the sum of values 5 + 4 + 3.

Example 3:

Input: values = [9,8,8,7,6], labels = [0,0,0,1,1], numWanted = 3, useLimit = 1

Output: 16

Explanation:

The subset chosen is the first and fourth items with the sum of values 9 + 7.

Constraints:

n == values.length == labels.length
1 <= n <= 2 * 104
0 <= values[i], labels[i] <= 2 * 104
1 <= numWanted, useLimit <= n
*/

#include <iostream>
#include <unordered_map>
#include <algorithm>
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
    int largestValsFromLabels(vector<int>& values, vector<int>& labels, int numWanted, int useLimit)
    {
        int res = 0;

        std::vector<std::pair<int, int>> pairs;
        for (int i = 0; i < values.size(); i++)
        {
            pairs.push_back({values[i], labels[i]});
        }
        std::sort(pairs.begin(), pairs.end(), std::greater<std::pair<int, int>>());

        std::unordered_map<int, int> count_used_label;
        for (int i = 0; i < pairs.size() && numWanted > 0; i++)
        {
            if (count_used_label[pairs[i].second] < useLimit)
            {
                count_used_label[pairs[i].second]++;
                res += pairs[i].first;
                numWanted--;
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> values = {5,4,3,2,1};
    std::vector<int> labels = {1,3,3,3,2};
    int wanted = 3;
    int useLimit = 2;
    std::cout << sol.largestValsFromLabels(values, labels, wanted, useLimit) << std::endl;
    return 0;
}