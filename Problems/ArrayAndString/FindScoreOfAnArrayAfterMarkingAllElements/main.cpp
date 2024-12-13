/**
https://leetcode.com/problems/find-score-of-an-array-after-marking-all-elements/description/

You are given an array nums consisting of positive integers.

Starting with score = 0, apply the following algorithm:

Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
Add the value of the chosen integer to score.
Mark the chosen element and its two adjacent elements if they exist.
Repeat until all the array elements are marked.
Return the score you get after applying the above algorithm.

Example 1:

Input: nums = [2,1,3,4,5,2]
Output: 7
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
- 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
- 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
Our score is 1 + 2 + 4 = 7.

Example 2:

Input: nums = [2,3,5,1,3,2]
Output: 5
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,3,5,1,3,2].
- 2 is the smallest unmarked element, since there are two of them, we choose the left-most one, so we mark the one at index 0 and its right adjacent element: [2,3,5,1,3,2].
- 2 is the only remaining unmarked element, so we mark it: [2,3,5,1,3,2].
Our score is 1 + 2 + 2 = 5.

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 106
 */

#include <iostream>
#include <vector>
#include <queue>
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
    long long findScore(vector<int>& nums)
    {
        long long score = 0LL;

        std::vector<bool> marked(nums.size(), false);

        struct Compare {
            bool operator()(const std::pair<int, int>& a, const std::pair<int, int>& b) const {
                if (a.first != b.first)
                    return a.first > b.first;
                return a.second > b.second;
            }
        };

        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, Compare> pq;
        for (int i = 0; i < nums.size(); i++)
        {
            pq.push({nums[i], i});
        }

        while (!pq.empty())
        {
            std::pair<int, int> cur = pq.top();
            pq.pop();

            if (!marked[cur.second])
            {
                marked[cur.second] = true;
                marked[std::max(0, cur.second - 1)] = true;
                marked[std::min((int)nums.size() - 1, cur.second + 1)] = true;

                score += cur.first;
            }
        }

        return score;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {2,3,5,1,3,2};
    std::cout << sol.findScore(nums) << std::endl;

    return 0;
}