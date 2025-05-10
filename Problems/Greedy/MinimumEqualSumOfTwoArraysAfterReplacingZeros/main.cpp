// https://leetcode.com/problems/minimum-equal-sum-of-two-arrays-after-replacing-zeros/description/

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
    long long minSum(vector<int>& nums1, vector<int>& nums2)
    {
        int n1 = nums1.size();
        int n2 = nums2.size();
        long long s1 = 0;
        long long s2 = 0;
        long long z1 = 0;
        long long z2 = 0;
        for (int i = 0; i < n1; i++)
        {
            s1 += nums1[i];
            z1 += (nums1[i] == 0);
        }
        for (int i = 0; i < n2; i++)
        {
            s2 += nums2[i];
            z2 += (nums2[i] == 0);
        }

        long long target = std::max(s1 + z1, s2 + z2);
        if (s1 + z1 < target && z1 == 0)
        {
            return -1;
        }
        if (s2 + z2 < target && z2 == 0)
        {
            return -1;
        }
        return target;
    }
};

int main()
{
    Solution sol;
    vector<int> nums1 = {1, 2, 0};
    vector<int> nums2 = {0, 3, 4};
    cout << sol.minSum(nums1, nums2) << endl; // Output: 10

    return 0;
}