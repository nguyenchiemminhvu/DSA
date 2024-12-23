/**
https://leetcode.com/problems/minimum-numbers-of-function-calls-to-make-target-array/

You are given an integer array nums. You have an integer array arr of the same length with all values set to 0 initially. You also have the following modify function:

void modify(std::vector<int>& arr, int op, int idx)
{
    if (op == 0)
    {
        arr[idx]++;
    }
    else if (op == 1)
    {
        for (int i = 0; i < arr.size(); i++)
        {
            arr[i] *= 2;
        }
    }
}

You want to use the modify function to convert arr to nums using the minimum number of calls.

Return the minimum number of function calls to make nums from arr.

The test cases are generated so that the answer fits in a 32-bit signed integer.

 

Example 1:

Input: nums = [1,5]
Output: 5
Explanation: Increment by 1 (second element): [0, 0] to get [0, 1] (1 operation).
Double all the elements: [0, 1] -> [0, 2] -> [0, 4] (2 operations).
Increment by 1 (both elements)  [0, 4] -> [1, 4] -> [1, 5] (2 operations).
Total of operations: 1 + 2 + 2 = 5.
Example 2:

Input: nums = [2,2]
Output: 3
Explanation: Increment by 1 (both elements) [0, 0] -> [0, 1] -> [1, 1] (2 operations).
Double all the elements: [1, 1] -> [2, 2] (1 operation).
Total of operations: 2 + 1 = 3.
Example 3:

Input: nums = [4,2,5]
Output: 6
Explanation: (initial)[0,0,0] -> [1,0,0] -> [1,0,1] -> [2,0,2] -> [2,1,2] -> [4,2,4] -> [4,2,5](nums).
 

Constraints:

1 <= nums.length <= 105
0 <= nums[i] <= 109
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
    int minOperations(vector<int>& nums)
    {
        int max_division = 0;
        int count_odd = 0;
        for (int n : nums)
        {
            apply_operations(n, max_division, count_odd);
        }

        return max_division + count_odd;
    }
private:
    void apply_operations(int n, int& max_div, int& count_odd)
    {
        int count_div = 0;
        while (n)
        {
            if (n & 1)
            {
                n--;
                count_odd++;
            }
            else
            {
                n /= 2;
                count_div++;
            }
        }

        max_div = std::max(max_div, count_div);
    }
};

int main()
{
    Solution sol;
    std::vector<int> nums = {4,2,5};
    std::cout << sol.minOperations(nums) << std::endl;

    return 0;
}