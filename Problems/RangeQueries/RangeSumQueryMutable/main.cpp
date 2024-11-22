/**
https://leetcode.com/problems/range-sum-query-mutable/

Given an integer array nums, handle multiple queries of the following types:

Update the value of an element in nums.
Calculate the sum of the elements of nums between indices left and right inclusive where left <= right.
Implement the NumArray class:

NumArray(int[] nums) Initializes the object with the integer array nums.
void update(int index, int val) Updates the value of nums[index] to be val.
int sumRange(int left, int right) Returns the sum of the elements of nums between indices left and right inclusive (i.e. nums[left] + nums[left + 1] + ... + nums[right]).

Example 1:

Input
["NumArray", "sumRange", "update", "sumRange"]
[[[1, 3, 5]], [0, 2], [1, 2], [0, 2]]
Output
[null, 9, null, 8]

Explanation
NumArray numArray = new NumArray([1, 3, 5]);
numArray.sumRange(0, 2); // return 1 + 3 + 5 = 9
numArray.update(1, 2);   // nums = [1, 2, 5]
numArray.sumRange(0, 2); // return 1 + 2 + 5 = 8

Constraints:

1 <= nums.length <= 3 * 104
-100 <= nums[i] <= 100
0 <= index < nums.length
-100 <= val <= 100
0 <= left <= right < nums.length
At most 3 * 104 calls will be made to update and sumRange.
*/

#include <iostream>
#include <vector>

using namespace std;

static bool fast = []()
{
    std::cin.tie(0)->sync_with_stdio(false);
    return true;
}();

class BinaryIndexedTree
{
private:
    std::vector<int> bit;
    int n;

public:
    BinaryIndexedTree(int size)
    {
        n = size;
        bit.resize(n + 1, 0);
    }

    void update(int idx, int val)
    {
        idx++; // Convert 0-based index to 1-based index
        while (idx <= n)
        {
            bit[idx] += val;
            idx += idx & -idx;
        }
    }

    int query(int idx)
    {
        idx++; // Convert 0-based index to 1-based index
        int sum = 0;
        while (idx > 0)
        {
            sum += bit[idx];
            idx -= idx & -idx;
        }
        return sum;
    }

    int rangeQuery(int left, int right)
    {
        return query(right) - query(left - 1);
    }
};

class NumArray
{
private:
    BinaryIndexedTree bit;
    std::vector<int> nums;

public:
    NumArray(std::vector<int>& nums) : bit(nums.size()), nums(nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            bit.update(i, nums[i]);
        }
    }

    void update(int index, int val)
    {
        int diff = val - nums[index]; // Calculate the difference
        nums[index] = val;            // Update the original array
        bit.update(index, diff);      // Update the BIT with the difference
    }

    int sumRange(int left, int right)
    {
        return bit.rangeQuery(left, right);
    }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * obj->update(index,val);
 * int param_2 = obj->sumRange(left,right);
 */

int main()
{
    return 0;
}