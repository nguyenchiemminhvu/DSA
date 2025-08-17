/**
https://leetcode.com/problems/maximum-candies-allocated-to-k-children/description/

You are given a 0-indexed integer array candies. Each element in the array denotes a pile of candies of size candies[i]. You can divide each pile into any number of sub piles, but you cannot merge two piles together.

You are also given an integer k. You should allocate piles of candies to k children such that each child gets the same number of candies. Each child can be allocated candies from only one pile of candies and some piles of candies may go unused.

Return the maximum number of candies each child can get.

Example 1:

Input: candies = [5,8,6], k = 3
Output: 5
Explanation: We can divide candies[1] into 2 piles of size 5 and 3, and candies[2] into 2 piles of size 5 and 1. We now have five piles of candies of sizes 5, 5, 3, 5, and 1. We can allocate the 3 piles of size 5 to 3 children. It can be proven that each child cannot receive more than 5 candies.

Example 2:

Input: candies = [2,5], k = 11
Output: 0
Explanation: There are 11 children but only 7 candies in total, so it is impossible to ensure each child receives at least one candy. Thus, each child gets no candy and the answer is 0.

Constraints:

1 <= candies.length <= 105
1 <= candies[i] <= 107
1 <= k <= 1012
 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <utility>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int maximumCandies(vector<int>& candies, long long k)
    {
        int low = 0;
        int high = *std::max_element(candies.begin(), candies.end());
        int res = low;
        while (low <= high)
        {
            long long mid = low + (high - low) / 2;
            if (testing(candies, k, mid))
            {
                res = mid;
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }
        }

        return res;
    }
private:
    bool testing(const std::vector<int> candies, long long k, long long mid)
    {
        if (mid == 0)
        {
            return true;
        }

        long long total_children_get_candies = 0LL;
        for (int i = 0; i < candies.size(); i++)
        {
            long long num_children = candies[i] / mid;
            total_children_get_candies += num_children;
            if (total_children_get_candies >= k)
            {
                return true;
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;
    vector<int> candies = {5, 8, 6};
    long long k = 3;
    cout << sol.maximumCandies(candies, k) << endl;

    candies = {2, 5};
    k = 11;
    cout << sol.maximumCandies(candies, k) << endl;
    return 0;
}