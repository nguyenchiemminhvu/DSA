## Problem

https://leetcode.com/problems/smallest-missing-integer-greater-than-sequential-prefix-sum/description/

```
You are given a 0-indexed array of positive integers nums.

A prefix nums[0..i] is sequential if, for all 1 <= j <= i, nums[j] = nums[j - 1] + 1. 
In particular, the prefix consisting only of nums[0] is sequential.

Return the smallest integer x missing from nums such that x is greater than or equal to the 
sum of the longest sequential prefix.
```

## Observations

1. **Sequential Prefix**: We need to find the longest prefix where each element is exactly 1 more than the previous element (e.g., [1, 2, 3, 4] or [37, 38, 39])

2. **Sum Calculation**: Once we find this longest sequential prefix, we calculate its sum

3. **Missing Integer**: Starting from the sum, we need to find the smallest integer that doesn't exist in the array

4. **Edge Cases**: 
   - Array with only one element (sequential prefix is just that element)
   - Sequential prefix might be the entire array
   - Need to handle duplicates in the array

## Solution

1. **Create a Set** (`s = set(nums)`): Store all numbers in a set for O(1) lookup when checking if a number exists

2. **Append Sentinel Value** (`nums.append(100)`): Add a value that breaks the sequence to ensure the loop terminates. This handles the edge case where the entire array is sequential

3. **Find Sequential Prefix**:
   - Loop from index 1 to n
   - Check if `nums[i] != nums[i-1] + 1` (sequence is broken)
   - When broken, calculate sum of prefix `nums[0:i]`
   - Use `min(longest_sum, sum(...))` though practically only one sum is calculated due to `break`

4. **Find Missing Integer**:
   - Start from `longest_sum`
   - Keep incrementing while the value exists in the set
   - Return the first missing value

### Time Complexity: O(n)
- Creating set: O(n)
- Finding sequential prefix: O(n) worst case
- Calculating sum: O(n) worst case
- Finding missing integer: O(n) worst case (in rare cases where we need to skip many values)

### Space Complexity: O(n)
- Set storage: O(n)

# Tags
#array #prefix-sum #sequential #hash-set #greedy

