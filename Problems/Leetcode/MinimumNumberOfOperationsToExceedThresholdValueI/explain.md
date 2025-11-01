## Problem

https://leetcode.com/problems/minimum-operations-to-exceed-threshold-value-i/

```
You are given a 0-indexed integer array nums, and an integer k.

In one operation, you can remove one occurrence of the smallest element of nums.

Return the minimum number of operations needed so that all elements of the array are greater than or equal to k.

Example 1:

Input: nums = [2,11,10,1,3], k = 10
Output: 3
Explanation: After one operation, nums becomes equal to [2, 11, 10, 3].
After two operations, nums becomes equal to [11, 10, 3].
After three operations, nums becomes equal to [11, 10].
At this stage, all the elements of nums are greater than or equal to 10 so we can stop.
It can be shown that 3 is the minimum number of operations needed so that all elements of the array are greater than or equal to 10.

Example 2:

Input: nums = [1,1,2,4,9], k = 1
Output: 0
Explanation: All elements of the array are greater than or equal to 1 so we do not need to apply any operations on nums.

Example 3:

Input: nums = [1,1,2,4,9], k = 9
Output: 4
Explanation: only a single element of nums is greater than or equal to 9 so we need to apply the operations 4 times on nums.

Constraints:

1 <= nums.length <= 50
1 <= nums[i] <= 109
1 <= k <= 109
The input is generated such that there is at least one index i such that nums[i] >= k.
```

## Observations

1. **Goal**: Remove minimum number of smallest elements so that all remaining elements are ≥ k
2. **Operation**: In each operation, we can only remove one occurrence of the smallest element
3. **Key Insight**: Since we can only remove the smallest elements, we need to count how many elements are < k
4. **Optimization**: Instead of simulating the removal process, we can:
   - Sort the array to group smaller elements together
   - Count how many elements are smaller than k
   - This count equals the minimum operations needed

## Solution

The solution uses a **binary search approach** to efficiently find the position where elements become ≥ k:

### Algorithm:
1. **Sort the array** - This groups all elements < k at the beginning
2. **Use binary search** to find the first position where `nums[i] >= k`
3. **Return the position** - This represents how many elements are < k (need to be removed)

### Binary Search Implementation:
- `lower_bound(arr, target)` finds the first index where `arr[i] >= target`
- If no such element exists, it returns the array length
- The returned index equals the count of elements < k

### Example Walkthrough:
**Example 1**: `nums = [2,11,10,1,3], k = 10`
- After sorting: `[1,2,3,10,11]`
- Binary search finds first element ≥ 10 at index 3
- Elements at indices 0,1,2 are < 10, so 3 operations needed

**Example 2**: `nums = [1,1,2,4,9], k = 1`  
- After sorting: `[1,1,2,4,9]`
- Binary search finds first element ≥ 1 at index 0
- No elements < 1, so 0 operations needed

**Example 3**: `nums = [1,1,2,4,9], k = 9`
- After sorting: `[1,1,2,4,9]` 
- Binary search finds first element ≥ 9 at index 4
- Elements at indices 0,1,2,3 are < 9, so 4 operations needed

### Time Complexity: O(n log n)
- Sorting: O(n log n)
- Binary search: O(log n)

### Space Complexity: O(1)
- Only using constant extra space (excluding input modification)

## Tags

array, sorting, binary search