/**
https://leetcode.com/problems/remove-stones-to-minimize-the-total/

You are given a 0-indexed integer array piles, where piles[i] represents the number of stones in the ith pile, and an integer k. You should apply the following operation exactly k times:
Choose any piles[i] and remove floor(piles[i] / 2) stones from it.
Notice that you can apply the operation on the same pile more than once.
Return the minimum possible total number of stones remaining after applying the k operations.
floor(x) is the greatest integer that is smaller than or equal to x (i.e., rounds x down).

Example 1:

Input: piles = [5,4,9], k = 2
Output: 12
Explanation: Steps of a possible scenario are:
- Apply the operation on pile 2. The resulting piles are [5,4,5].
- Apply the operation on pile 0. The resulting piles are [3,4,5].
The total number of stones in [3,4,5] is 12.

Example 2:

Input: piles = [4,3,6,7], k = 3
Output: 12
Explanation: Steps of a possible scenario are:
- Apply the operation on pile 2. The resulting piles are [4,3,3,7].
- Apply the operation on pile 3. The resulting piles are [4,3,3,4].
- Apply the operation on pile 0. The resulting piles are [2,3,3,4].
The total number of stones in [2,3,3,4] is 12.

Constraints:

1 <= piles.length <= 10^5
1 <= piles[i] <= 10^4
1 <= k <= 10^5
 */

#include <iostream>
#include <vector>
#include <queue>
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
    int minStoneSum(vector<int>& piles, int k)
    {
        std::priority_queue<int> pq;
        for (int p : piles)
        {
            pq.push(p);
        }

        for (int t = 0; t < k; t++)
        {
            int cur = pq.top();
            pq.pop();

            pq.push(cur - std::floor(cur / 2));
        }

        int res = 0;
        while (!pq.empty())
        {
            res += pq.top();
            pq.pop();
        }
        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {4, 3, 6, 7};
    std::cout << sol.minStoneSum(nums, 3) << std::endl;
    return 0;
}