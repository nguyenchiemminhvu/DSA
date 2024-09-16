/**
https://leetcode.com/problems/the-two-sneaky-numbers-of-digitville/

In the town of Digitville, there was a list of numbers called nums containing integers from 0 to n - 1. Each number was supposed to appear exactly once in the list, however, two mischievous numbers sneaked in an additional time, making the list longer than usual.
As the town detective, your task is to find these two sneaky numbers. Return an array of size two containing the two numbers (in any order), so peace can return to Digitville.

Example 1:

Input: nums = [0,1,1,0]

Output: [0,1]

Explanation:

The numbers 0 and 1 each appear twice in the array.

Example 2:

Input: nums = [0,3,2,1,3,2]

Output: [2,3]

Explanation:

The numbers 2 and 3 each appear twice in the array.

Example 3:

Input: nums = [7,1,5,4,3,4,6,0,9,5,8,2]

Output: [4,5]

Explanation:

The numbers 4 and 5 each appear twice in the array.

Constraints:

2 <= n <= 100
nums.length == n + 2
0 <= nums[i] < n
The input is generated such that nums contains exactly two repeated elements.

*/

#include <iostream>
#include <vector>

using namespace std;

class Solution
{
public:
    vector<int> getSneakyNumbers(vector<int>& nums)
    {
        int n = nums.size() - 2;
        int xor_all = 0;
        int xor_nums = 0;

        // XOR all numbers from 0 to n-1
        for (int i = 0; i < n; ++i)
        {
            xor_all ^= i;
        }

        // XOR all numbers in the nums array
        for (int num : nums)
        {
            xor_nums ^= num;
        }

        // XOR of xor_all and xor_nums gives us xor of the two duplicate numbers
        int xor_dup = xor_all ^ xor_nums;

        // Find a set bit in xor_dup (this bit is different in the two duplicate numbers)
        int set_bit = xor_dup & ~(xor_dup - 1);

        int num1 = 0, num2 = 0;

        // Divide numbers into two groups based on the set bit and XOR within each group
        for (int i = 0; i < n; ++i)
        {
            if (i & set_bit)
            {
                num1 ^= i;
            }
            else
            {
                num2 ^= i;
            }
        }

        for (int num : nums)
        {
            if (num & set_bit)
            {
                num1 ^= num;
            }
            else
            {
                num2 ^= num;
            }
        }

        return {num1, num2};
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {0,3,2,1,3,2};
    std::vector<int> res = sol.getSneakyNumbers(nums);
    for (int n : res)
    {
        std::cout << n << " ";
    }
    std::cout << std::endl;
    return 0;
}