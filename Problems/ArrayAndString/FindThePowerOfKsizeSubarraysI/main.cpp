/**
https://leetcode.com/problems/find-the-power-of-k-size-subarrays-i/

You are given an array of integers nums of length n and a positive integer k.

The power of an array is defined as:

Its maximum element if all of its elements are consecutive and sorted in ascending order, -1 otherwise.

You need to find the power of all subarrays of nums of size k.

Return an integer array results of size n - k + 1, where results[i] is the power of nums[i..(i + k - 1)].

Example 1:

Input: nums = [1,2,3,4,3,2,5], k = 3

Output: [3,4,-1,-1,-1]

Explanation:

There are 5 subarrays of nums of size 3:

[1, 2, 3] with the maximum element 3.
[2, 3, 4] with the maximum element 4.
[3, 4, 3] whose elements are not consecutive.
[4, 3, 2] whose elements are not sorted.
[3, 2, 5] whose elements are not consecutive.

Example 2:

Input: nums = [2,2,2,2,2], k = 4

Output: [-1,-1]

Example 3:

Input: nums = [3,2,3,2,3,2], k = 2

Output: [-1,3,-1,3,-1]

Constraints:

1 <= n == nums.length <= 500
1 <= nums[i] <= 105
1 <= k <= n
*/

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class Solution
{
public:
    vector<int> resultsArray(vector<int>& nums, int k)
    {
        std::vector<int> res;
        if (k == 1)
        {
            res.push_back(nums[0]);
        }

        std::vector<int> power(nums.size(), 1);
        for (int i = 1; i < nums.size(); i++)
        {
            if (nums[i] == nums[i - 1] + 1)
            {
                power[i] = power[i - 1] + 1;
            }

            if (i >= k - 1)
            {
                res.push_back((power[i] >= k) ? nums[i] : -1);
            }
        }

        return res;
    }
};

int main()
{
	Solution sol;
	std::vector<int> nums = {1,2,3,4,3,2,5};
	int k = 3;
	std::vector<int> res = sol.resultsArray(nums, k);
	for (int n : res)
	{
		std::cout << n << " ";
	}
	std::cout << std::endl;
	return 0;
}
