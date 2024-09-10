/**
https://leetcode.com/problems/maximum-bags-with-full-capacity-of-rocks/description/

You have n bags numbered from 0 to n - 1. You are given two 0-indexed integer arrays capacity and rocks.
The ith bag can hold a maximum of capacity[i] rocks and currently contains rocks[i] rocks.
You are also given an integer additionalRocks, the number of additional rocks you can place in any of the bags.
Return the maximum number of bags that could have full capacity after placing the additional rocks in some bags.

Example 1:

Input: capacity = [2,3,4,5], rocks = [1,2,4,4], additionalRocks = 2
Output: 3

Explanation:
Place 1 rock in bag 0 and 1 rock in bag 1.
The number of rocks in each bag are now [2,3,4,4].
Bags 0, 1, and 2 have full capacity.
There are 3 bags at full capacity, so we return 3.
It can be shown that it is not possible to have more than 3 bags at full capacity.
Note that there may be other ways of placing the rocks that result in an answer of 3.

Example 2:

Input: capacity = [10,2,2], rocks = [2,2,0], additionalRocks = 100
Output: 3

Explanation:
Place 8 rocks in bag 0 and 2 rocks in bag 2.
The number of rocks in each bag are now [10,2,2].
Bags 0, 1, and 2 have full capacity.
There are 3 bags at full capacity, so we return 3.
It can be shown that it is not possible to have more than 3 bags at full capacity.
Note that we did not use all of the additional rocks.

Constraints:

n == capacity.length == rocks.length
1 <= n <= 5 * 104
1 <= capacity[i] <= 109
0 <= rocks[i] <= capacity[i]
1 <= additionalRocks <= 109
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Solution
{
public:
    int maximumBags(vector<int>& capacity, vector<int>& rocks, int add)
    {
        ios_base::sync_with_stdio(false);
        cin.tie(NULL), cout.tie(NULL);

        std::vector<std::pair<int, int>> pairs(rocks.size());
        for (int i = 0; i < rocks.size(); i++)
        {
            pairs[i].first = rocks[i];
            pairs[i].second = capacity[i];
        }

        std::sort(pairs.begin(), pairs.end(), [](auto a, auto b) {
            return (a.second - a.first) < (b.second - b.first);
        });

        int res = 0;
        for (int i = 0; i < pairs.size() && add > 0; i++)
        {
            if (pairs[i].first == pairs[i].second)
            {
                res++;
            }
            else
            {
                if (add >= (pairs[i].second - pairs[i].first))
                {
                    add -= (pairs[i].second - pairs[i].first);
                    res++;
                }
                else
                {
                    break;
                }
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> cap = {2,3,4,5};
    std::vector<int> rocks = {1,2,4,4};
    int additional = 2;
    std::cout << sol.maximumBags(cap, rocks, additional) << std::endl;
    return 0;
}