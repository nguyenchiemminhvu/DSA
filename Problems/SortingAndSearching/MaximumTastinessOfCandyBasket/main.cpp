/**
https://leetcode.com/problems/maximum-tastiness-of-candy-basket/

You are given an array of positive integers price where price[i] denotes the price of the ith candy and a positive integer k.

The store sells baskets of k distinct candies. The tastiness of a candy basket is the smallest absolute difference of the prices of any two candies in the basket.

Return the maximum tastiness of a candy basket.

Example 1:

Input: price = [13,5,1,8,21,2], k = 3
Output: 8
Explanation: Choose the candies with the prices [13,5,21].
The tastiness of the candy basket is: min(|13 - 5|, |13 - 21|, |5 - 21|) = min(8, 8, 16) = 8.
It can be proven that 8 is the maximum tastiness that can be achieved.

Example 2:

Input: price = [1,3,1], k = 2
Output: 2
Explanation: Choose the candies with the prices [1,3].
The tastiness of the candy basket is: min(|1 - 3|) = min(2) = 2.
It can be proven that 2 is the maximum tastiness that can be achieved.

Example 3:

Input: price = [7,7,7,7], k = 2
Output: 0
Explanation: Choosing any two distinct candies from the candies we have will result in a tastiness of 0.

Constraints:

2 <= k <= price.length <= 105
1 <= price[i] <= 109
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    int maximumTastiness(vector<int>& price, int k)
    {
        int res = 0;

        std::sort(price.begin(), price.end());

        int diff_left = 0;
        int diff_right = price.back() - price[0];

        while (diff_left <= diff_right)
        {
            int diff_mid = diff_left + (diff_right - diff_left) / 2;

            if (checking(price, k, diff_mid))
            {
                res = std::max(res, diff_mid);
                diff_left = diff_mid + 1;
            }
            else
            {
                diff_right = diff_mid - 1;
            }
        }

        return res;
    }
private:
    bool checking(const std::vector<int> price, int k, int min_diff)
    {
        int count = 1;
        int last_selected = price[0];

        for (int i = 1; i < price.size(); ++i)
        {
            if (price[i] - last_selected >= min_diff)
            {
                count++;
                last_selected = price[i];

                if (count >= k)
                {
                    return true;
                }
            }
        }

        return false;
    }
};

int main()
{
    Solution sol;
    std::vector<int> price = {1, 3, 1};
    int k = 2;
    std::cout << sol.maximumTastiness(price, k) << std::endl;
    return 0;
}