/**
https://leetcode.com/problems/minimum-time-to-repair-cars/

You are given an integer array ranks representing the ranks of some mechanics. ranksi is the rank of the ith mechanic. A mechanic with a rank r can repair n cars in r * n2 minutes.

You are also given an integer cars representing the total number of cars waiting in the garage to be repaired.

Return the minimum time taken to repair all the cars.

Note: All the mechanics can repair the cars simultaneously.

Example 1:

Input: ranks = [4,2,3,1], cars = 10
Output: 16
Explanation: 
- The first mechanic will repair two cars. The time required is 4 * 2 * 2 = 16 minutes.
- The second mechanic will repair two cars. The time required is 2 * 2 * 2 = 8 minutes.
- The third mechanic will repair two cars. The time required is 3 * 2 * 2 = 12 minutes.
- The fourth mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
It can be proved that the cars cannot be repaired in less than 16 minutes.​​​​​

Example 2:

Input: ranks = [5,1,8], cars = 6
Output: 16
Explanation: 
- The first mechanic will repair one car. The time required is 5 * 1 * 1 = 5 minutes.
- The second mechanic will repair four cars. The time required is 1 * 4 * 4 = 16 minutes.
- The third mechanic will repair one car. The time required is 8 * 1 * 1 = 8 minutes.
It can be proved that the cars cannot be repaired in less than 16 minutes.​​​​​

Constraints:

1 <= ranks.length <= 105
1 <= ranks[i] <= 100
1 <= cars <= 106
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
    long long repairCars(std::vector<int>& ranks, int cars)
    {
        long long res = LLONG_MAX;

        long long left = 1;
        long long right = *std::max_element(ranks.begin(), ranks.end()) * (static_cast<long long>(cars) * cars);
        while (left <= right)
        {
            long long mid = left + (right - left) / 2;
            if (testing(ranks, cars, mid))
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
    bool testing(const std::vector<int>& ranks, int cars, long long minutes)
    {
        long long totalCars = 0LL;
        for (const int rank : ranks)
        {
            totalCars += static_cast<long long>(std::sqrt(minutes / rank));
            if (totalCars >= cars)
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
    std::vector<int> ranks = {4, 2, 3, 1};
    int cars = 10;
    std::cout << sol.repairCars(ranks, cars) << std::endl;
    return 0;
}