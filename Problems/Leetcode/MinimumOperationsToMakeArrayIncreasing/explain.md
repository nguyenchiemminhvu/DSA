## Problem

https://leetcode.com/problems/minimum-operations-to-make-the-array-increasing/

```
You are given an integer array nums (0-indexed). In one operation, you can choose an element of the array and increment it by 1.

For example, if nums = [1,2,3], you can choose to increment nums[1] to make nums = [1,3,3].
Return the minimum number of operations needed to make nums strictly increasing.

An array nums is strictly increasing if nums[i] < nums[i+1] for all 0 <= i < nums.length - 1. An array of length 1 is trivially strictly increasing.

Example 1:

Input: nums = [1,1,1]
Output: 3
Explanation: You can do the following operations:
1) Increment nums[2], so nums becomes [1,1,2].
2) Increment nums[1], so nums becomes [1,2,2].
3) Increment nums[2], so nums becomes [1,2,3].

Example 2:

Input: nums = [1,5,2,4,1]
Output: 14
Example 3:

Input: nums = [8]
Output: 0

Constraints:

1 <= nums.length <= 5000
1 <= nums[i] <= 104
```

## Observations

1. **Goal**: Make the array strictly increasing with minimum increment operations
2. **Key insight**: We can only increment elements, never decrement them
3. **Greedy approach**: Process the array from left to right and ensure each element is at least `previous_element + 1`
4. **Why greedy works**: Since we can only increment, if we encounter an element that violates the strictly increasing property, we should increment it to the minimum possible value (previous element + 1) to minimize total operations
5. **Edge cases**: 
   - Single element array is already strictly increasing (0 operations)
   - If current element is already greater than previous, no operation needed

## Solution

The solution uses a **greedy approach**:

1. **Initialize**: Keep track of operations count and the previous element value
2. **Iterate**: For each element from index 1 to n-1:
   - If current element ≤ previous element, it violates strictly increasing property
   - Calculate operations needed: `(previous + 1) - current`
   - Update current element to `previous + 1`
   - Add operations to total count
3. **Update**: Set previous to current element for next iteration

**Time Complexity**: O(n) - single pass through the array
**Space Complexity**: O(1) - only using constant extra space

**Example walkthrough** with `nums = [1,5,2,4,1]`:
- Start: prev = 1, operations = 0
- Index 1: nums[1] = 5 > prev(1) ✓, prev = 5
- Index 2: nums[2] = 2 ≤ prev(5) ✗, need 5+1-2 = 4 operations, nums[2] = 6, prev = 6
- Index 3: nums[3] = 4 ≤ prev(6) ✗, need 6+1-4 = 3 operations, nums[3] = 7, prev = 7  
- Index 4: nums[4] = 1 ≤ prev(7) ✗, need 7+1-1 = 7 operations, nums[4] = 8, prev = 8
- Total: 4 + 3 + 7 = 14 operations

## Tags

array, greedy