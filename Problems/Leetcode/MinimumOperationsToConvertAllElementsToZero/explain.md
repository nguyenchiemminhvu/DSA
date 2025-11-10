## Problem

https://leetcode.com/problems/minimum-operations-to-convert-all-elements-to-zero/description/

```
You are given an array nums of size n, consisting of non-negative integers. Your task is to apply some (possibly zero) operations on the array so that all elements become 0.

In one operation, you can select a subarray [i, j] (where 0 <= i <= j < n) and set all occurrences of the minimum non-negative integer in that subarray to 0.

Return the minimum number of operations required to make all elements in the array 0.

Example 1:

Input: nums = [0,2]

Output: 1

Explanation:

Select the subarray [1,1] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0].
Thus, the minimum number of operations required is 1.

Example 2:

Input: nums = [3,1,2,1]

Output: 3

Explanation:

Select subarray [1,3] (which is [1,2,1]), where the minimum non-negative integer is 1. Setting all occurrences of 1 to 0 results in [3,0,2,0].
Select subarray [2,2] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [3,0,0,0].
Select subarray [0,0] (which is [3]), where the minimum non-negative integer is 3. Setting all occurrences of 3 to 0 results in [0,0,0,0].
Thus, the minimum number of operations required is 3.

Example 3:

Input: nums = [1,2,1,2,1,2]

Output: 4

Explanation:

Select subarray [0,5] (which is [1,2,1,2,1,2]), where the minimum non-negative integer is 1. Setting all occurrences of 1 to 0 results in [0,2,0,2,0,2].
Select subarray [1,1] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,2,0,2].
Select subarray [3,3] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,0,0,2].
Select subarray [5,5] (which is [2]), where the minimum non-negative integer is 2. Setting all occurrences of 2 to 0 results in [0,0,0,0,0,0].
Thus, the minimum number of operations required is 4.

Constraints:

1 <= n == nums.length <= 105
0 <= nums[i] <= 105
```

## Observations

1. **Key Insight**: Each operation eliminates all occurrences of the minimum value in a selected subarray. This means we need to think about which values can be eliminated together and in what order.

2. **Stack-based Approach**: The solution uses a monotonic stack to simulate the process. The stack maintains elements in non-decreasing order from bottom to top.

3. **When to Perform Operations**: 
   - When we encounter a value smaller than the top of the stack, we need to perform operations to remove larger values first
   - After processing all elements, we may still have elements in the stack that need operations

4. **Operation Logic**: 
   - We can only eliminate a value if it's the minimum in some subarray
   - If we have values [a, b] where a > b, we must eliminate a before we can eliminate b in an optimal solution
   - All consecutive identical values can be eliminated in a single operation

5. **Edge Case**: Values of 0 don't need operations (they're already the target), so we stop when we encounter 0.

## Solution

The algorithm works in two phases:

**Phase 1 - Processing the array**:
- Use a monotonic stack to maintain non-decreasing order
- When encountering a smaller value, perform operations to remove all larger values from the stack
- Each operation removes all consecutive identical values from the top of the stack

**Phase 2 - Cleanup**:
- After processing the array, remove any remaining non-zero values from the stack
- Each group of identical values requires one operation

**Time Complexity**: O(n) - each element is pushed and popped at most once
**Space Complexity**: O(n) - for the stack

**Example Walkthrough** (nums = [3,1,2,1]):
1. Process 3: stack = [3]
2. Process 1: 1 < 3, so remove all 3s (operation 1), then add 1: stack = [1]
3. Process 2: 2 > 1, so add 2: stack = [1,2] 
4. Process 1: 1 < 2, so remove all 2s (operation 2), stack = [1], add 1: stack = [1,1]
5. Cleanup: remove all 1s (operation 3)
6. Total: 3 operations

# Tags

- Array
- Stack
- Monotonic Stack
- Greedy
- Simulation

