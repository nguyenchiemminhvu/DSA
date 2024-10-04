/**
https://leetcode.com/problems/maximum-subsequence-score/description/


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
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k)
    {
        std::vector<std::pair<int, int>> vec;
        for (int i = 0; i < nums1.size(); i++)
        {
            vec.push_back({nums2[i], nums1[i]});
        }

        std::sort(vec.begin(), vec.end(), std::greater<std::pair<int, int>>());

        long long res = 0LL;
        long long sum1 = 0;
        std::priority_queue<int, std::vector<int>, std::greater<int>> minHeap;
        for (int i = 0; i < vec.size(); i++)
        {
            sum1 += vec[i].second;
            minHeap.push(vec[i].second);

            if (minHeap.size() > k)
            {
                sum1 -= minHeap.top();
                minHeap.pop();
            }

            if (minHeap.size() == k)
            {
                res = std::max(res, sum1 * vec[i].first);
            }
        }

        return res;
    }
};

int main()
{
    Solution sol;
    std::vector<int> a = {1,3,3,2};
    std::vector<int> b = {2,1,3,4};
    int k = 3;
    std::cout << sol.maxScore(a, b, k) << std::endl;
    return 0;
}