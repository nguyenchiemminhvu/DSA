// https://leetcode.com/problems/count-of-interesting-subarrays/description/

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k)
    {
        long long res = 0LL;
        int prefix_mod = 0;
        std::unordered_map<int, int> freq;
        freq[0] = 1;
        for (int n : nums)
        {
            if (n % modulo == k)
            {
                prefix_mod++;
            }

            int remain = (((prefix_mod   % modulo) + modulo) % modulo);
            int target_remain = ((remain - k) + modulo) % modulo;
            res += freq[target_remain];

            freq[remain]++;
        }

        return res;
    }
};

int main()
{
    Solution s;
    vector<int> nums = {1, 2, 3, 4, 5};
    int modulo = 2;
    int k = 1;
    cout << s.countInterestingSubarrays(nums, modulo, k) << endl;
    return 0;
}