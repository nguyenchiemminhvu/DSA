/**
https://vjudge.net/contest/690993#problem/A
https://usaco.guide/problems/usaco-595-subsequences-summing-to-sevens/solution

Farmer John's N cows are standing in a row, as they have a tendency to do from time to time. Each cow is labeled with a distinct integer ID number so FJ can tell them apart. FJ would like to take a photo of a contiguous group of cows but, due to a traumatic childhood incident involving the numbers 1…6, he only wants to take a picture of a group of cows if their IDs add up to a multiple of 7.
Please help FJ determine the size of the largest group he can photograph.
 */

#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution
{
public:
    int largestGroup(const std::vector<int>& nums)
    {
        std::vector<int> mod_sum(nums.size(), 0);
        for (int i = 0; i < nums.size(); i++)
        {
            mod_sum[i] = nums[i] % 7;
            if (i > 0)
            {
                mod_sum[i] = (mod_sum[i] + mod_sum[i - 1]) % 7;
            }
        }

        int res = 0;
        std::unordered_map<int, int> first_occurrence;
        first_occurrence[0] = -1;
        for (int i = 0; i < mod_sum.size(); i++)
        {
            if (first_occurrence.find(mod_sum[i]) == first_occurrence.end())
            {
                first_occurrence[mod_sum[i]] = i;
            }
            else
            {
                res = std::max(res, i - first_occurrence[mod_sum[i]]);
            }
        }

        return res;
    }
};

int main()
{
    freopen("div7.in", "r", stdin);
    freopen("div7.out", "w", stdout);

    int n;
    std::cin >> n;
    std::vector<int> nums(n);
    for (int i = 0; i < n; i++)
    {
        std::cin >> nums[i];
    }

    Solution sol;
    std::cout << sol.largestGroup(nums) << std::endl;

    return 0;
}