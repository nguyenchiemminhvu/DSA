## Problem

https://leetcode.com/problems/minimum-operations-to-make-array-values-equal-to-k/description/

```
You are given an integer array nums and an integer k.

An integer h is called valid if all values in the array that are strictly greater than h are identical.

For example, if nums = [10, 8, 10, 8], a valid integer is h = 9 because all nums[i] > 9 are equal to 10, but 5 is not a valid integer.

You are allowed to perform the following operation on nums:

Select an integer h that is valid for the current values in nums.
For each index i where nums[i] > h, set nums[i] to h.
Return the minimum number of operations required to make every element in nums equal to k. If it is impossible to make all elements equal to k, return -1.

Example 1:

Input: nums = [5,2,5,4,5], k = 2

Output: 2

Explanation:

The operations can be performed in order using valid integers 4 and then 2.

Example 2:

Input: nums = [2,1,2], k = 2

Output: -1

Explanation:

It is impossible to make all the values equal to 2.

Example 3:

Input: nums = [9,7,5,3], k = 1

Output: 4

Explanation:

The operations can be performed using valid integers in the order 7, 5, 3, and 1.

Constraints:

1 <= nums.length <= 100 
1 <= nums[i] <= 100
1 <= k <= 100
```

## Observations

1. **Problem Understanding**: We need to make all elements in the array equal to `k` using operations where we select a valid height `h` and set all elements greater than `h` to `h`.

2. **Key Insight - Valid Height**: A height `h` is valid if all elements strictly greater than `h` are identical. This means we can only "compress" groups of identical values that are the largest remaining values.

3. **Impossible Case**: If any element is less than `k`, it's impossible since we can only decrease values, never increase them.

4. **Minimum Operations Strategy**: 
   - We need to reduce all unique values greater than `k` down to `k`
   - Each operation eliminates exactly one unique value (the current maximum)
   - If the minimum value is already `k`, we need one less operation
   - If the minimum value is greater than `k`, we need an extra operation to reduce it to `k`

5. **Mathematical Formula**:
   - Base operations needed: `len(set(nums)) - 1` (reduce all unique values to one)
   - Additional operation if minimum > k: `+1` to go from minimum to `k`
   - Total: `len(set(nums)) - 1 + int(min(nums) > k)`

## Solution

1. **Check Feasibility**: If `min(nums) < k`, return -1 since we cannot increase values.

2. **Count Unique Values**: `len(set(nums))` gives us the number of distinct values in the array.

3. **Calculate Operations**:
   - We need `len(set(nums)) - 1` operations to reduce all unique values to a single value
   - If that single value (minimum) is greater than `k`, we need one additional operation to reach `k`

**Example Walkthrough**:

For `nums = [5,2,5,4,5], k = 2`:
- Unique values: {2, 4, 5} → 3 unique values
- Minimum: 2 (equals k)
- Operations: 3 - 1 + 0 = 2
- Process: [5,2,5,4,5] → [4,2,4,4,4] → [2,2,2,2,2]

For `nums = [9,7,5,3], k = 1`:
- Unique values: {3, 5, 7, 9} → 4 unique values  
- Minimum: 3 (greater than k=1)
- Operations: 4 - 1 + 1 = 4
- Process: [9,7,5,3] → [7,7,5,3] → [5,5,5,3] → [3,3,3,3] → [1,1,1,1]

**Time Complexity**: O(n) - single pass to create set and find minimum
**Space Complexity**: O(n) - for the set of unique values

# Tags

Array, Hash Set, Greedy, Math

