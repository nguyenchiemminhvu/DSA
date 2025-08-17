/**
https://leetcode.com/problems/koko-eating-bananas/description/

Koko loves to eat bananas. There are n piles of bananas, the ith pile has piles[i] bananas. The guards have gone and will come back in h hours.

Koko can decide her bananas-per-hour eating speed of k. Each hour, she chooses some pile of bananas and eats k bananas from that pile. If the pile has less than k bananas, she eats all of them instead and will not eat any more bananas during this hour.

Koko likes to eat slowly but still wants to finish eating all the bananas before the guards return.

Return the minimum integer k such that she can eat all the bananas within h hours.

Example 1:

Input: piles = [3,6,7,11], h = 8
Output: 4

Example 2:

Input: piles = [30,11,23,4,20], h = 5
Output: 30

Example 3:

Input: piles = [30,11,23,4,20], h = 6
Output: 23

Constraints:

1 <= piles.length <= 104
piles.length <= h <= 109
1 <= piles[i] <= 109
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int minEatingSpeed(vector<int>& piles, int h)
    {
        int left = 1;
        int right = *std::max_element(piles.begin(), piles.end());
        int res = right;
        while (left <= right)
        {
            int mid = left + (right - left) / 2;

            if (testing(piles, h, mid))
            {
                res = std::min(res, mid);
                right = mid - 1;
            }
            else
            {
                left = mid + 1;
            }
        }

        return res;
    }

private:
    bool testing(const std::vector<int>& piles, int h, int speed)
    {
        int consume_time = 0;
        for (int banana : piles)
        {
            int duration = (banana / speed) + ((banana % speed) > 0);
            consume_time += duration;
            if (consume_time > h)
            {
                return false;
            }
        }

        return consume_time <= h;
    }
};

int main()
{
    Solution sol;
    std::vector<int> piles = {3, 6, 7, 11};
    int h = 8;
    std::cout << sol.minEatingSpeed(piles, h) << std::endl;
    return 0;
}