/**
https://leetcode.com/problems/previous-permutation-with-one-swap/

Given an array of positive integers arr (not necessarily distinct), return the lexicographically largest permutation that is smaller than arr, that can be made with exactly one swap. If it cannot be done, then return the same array.

Note that a swap exchanges the positions of two numbers arr[i] and arr[j]

Example 1:

Input: arr = [3,2,1]
Output: [3,1,2]
Explanation: Swapping 2 and 1.

Example 2:

Input: arr = [1,1,5]
Output: [1,1,5]
Explanation: This is already the smallest permutation.

Example 3:

Input: arr = [1,9,4,6,7]
Output: [1,7,4,6,9]
Explanation: Swapping 9 and 7.

Constraints:

1 <= arr.length <= 104
1 <= arr[i] <= 104
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
    vector<int> prevPermOpt1(vector<int>& arr)
    {
        bool is_sorted = true;
        for (int i = 1; i < arr.size(); i++)
        {
            if (arr[i] < arr[i - 1])
            {
                is_sorted = false;
                break;
            }
        }

        if (is_sorted)
        {
            return arr;
        }

        int j = arr.size() - 2;
        while (j >= 0 && arr[j] <= arr[j + 1])
        {
            j--;
        }
        
        int i = arr.size() - 1;
        int pivot_idx = i;
        int max_val = 0;
        while (i > j)
        {
            if (arr[i] < arr[j] && arr[i] >= max_val)
            {
                pivot_idx = i;
                max_val = arr[i];
            }
            i--;
        }

        std::swap(arr[j], arr[pivot_idx]);

        return arr;
    }
};

int main()
{
    Solution sol;
    std::vector<int> arr = {1,9,4,6,7};
    std::vector<int> res = sol.prevPermOpt1(arr);
    for (int val : res)
    {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    return 0;
}