/**
https://leetcode.com/problems/k-th-smallest-prime-fraction/description/

You are given a sorted integer array arr containing 1 and prime numbers, where all the integers of arr are unique. You are also given an integer k.

For every i and j where 0 <= i < j < arr.length, we consider the fraction arr[i] / arr[j].

Return the kth smallest fraction considered. Return your answer as an array of integers of size 2, where answer[0] == arr[i] and answer[1] == arr[j].

Example 1:

Input: arr = [1,2,3,5], k = 3
Output: [2,5]
Explanation: The fractions to be considered in sorted order are:
1/5, 1/3, 2/5, 1/2, 3/5, and 2/3.
The third fraction is 2/5.

Example 2:

Input: arr = [1,7], k = 1
Output: [1,7]

Constraints:

2 <= arr.length <= 1000
1 <= arr[i] <= 3 * 104
arr[0] == 1
arr[i] is a prime number for i > 0.
All the numbers of arr are unique and sorted in strictly increasing order.
1 <= k <= arr.length * (arr.length - 1) / 2

Follow up: Can you solve the problem with better than O(n2) complexity?
*/

#include <iostream>
#include <vector>
#include <queue>

using namespace std;

static bool fast = []() {
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<int> kthSmallestPrimeFraction(vector<int>& arr, int k)
    {
        auto comp = [&](const auto& p1, const auto& p2)
        {
            return arr[p1.first] * arr[p2.second] > arr[p2.first] * arr[p1.second];
        };
        std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)> pq(comp);
        for (int i = 0; i < arr.size(); i++)
        {
            pq.push({i, arr.size() - 1});
        }

        while (--k)
        {
            std::pair<int, int> p = pq.top();
            pq.pop();

            if (p.second - 1 > p.first)
            {
                pq.push({p.first, p.second - 1});
            }
        }

        return {arr[pq.top().first], arr[pq.top().second]};
    }
};

int main()
{
    Solution sol;
    std::vector<int> arr = {1, 2, 3, 5};
    int k = 3;
    std::vector<int> res = sol.kthSmallestPrimeFraction(arr, k);
    std::cout << res[0] << " " << res[1] << std::endl;
    return 0;
}