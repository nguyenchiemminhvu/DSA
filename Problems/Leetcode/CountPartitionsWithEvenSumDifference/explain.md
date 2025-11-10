## Problem

https://leetcode.com/problems/count-partitions-with-even-sum-difference/description/

```
You are given an integer array nums of length n.

A partition is defined as an index i where 0 <= i < n - 1, splitting the array into two non-empty subarrays such that:

Left subarray contains indices [0, i].
Right subarray contains indices [i + 1, n - 1].
Return the number of partitions where the difference between the sum of the left and right subarrays is even.

Example 1:

Input: nums = [10,10,3,7,6]

Output: 4

Explanation:

The 4 partitions are:

[10], [10, 3, 7, 6] with a sum difference of 10 - 26 = -16, which is even.
[10, 10], [3, 7, 6] with a sum difference of 20 - 16 = 4, which is even.
[10, 10, 3], [7, 6] with a sum difference of 23 - 13 = 10, which is even.
[10, 10, 3, 7], [6] with a sum difference of 30 - 6 = 24, which is even.

Example 2:

Input: nums = [1,2,2]

Output: 0

Explanation:

No partition results in an even sum difference.

Example 3:

Input: nums = [2,4,6,8]

Output: 3

Explanation:

All partitions result in an even sum difference.

Constraints:

2 <= n == nums.length <= 100
1 <= nums[i] <= 100
```

## Observations

1. **Problem Understanding:**
   - We need to find partitions where the difference between left and right subarray sums is even
   - A partition at index i creates: left = [0...i], right = [i+1...n-1]
   - We need to count how many such valid partitions exist

2. **Mathematical Insight:**
   - For a partition at index i: `left_sum - right_sum` should be even
   - If `total_sum = left_sum + right_sum`, then `right_sum = total_sum - left_sum`
   - So we need: `left_sum - (total_sum - left_sum) = 2 * left_sum - total_sum` to be even
   - This means: `2 * left_sum - total_sum ≡ 0 (mod 2)`
   - Since `2 * left_sum` is always even, we need `total_sum` to be even for the difference to be even
   - Actually, let's think differently: `left_sum - right_sum ≡ 0 (mod 2)` means `left_sum ≡ right_sum (mod 2)`

3. **Key Insight:**
   - The difference is even if and only if both sums have the same parity (both even or both odd)
   - Since `left_sum + right_sum = total_sum`, if they have the same parity, then `total_sum` must be even
   - Conversely, if `total_sum` is even and `left_sum` has parity P, then `right_sum` has the same parity P

4. **Algorithm Approach:**
   - Use prefix sums for efficient calculation
   - For each possible partition point, check if the difference is even
   - Time complexity: O(n) after preprocessing
   - Space complexity: O(1) if we modify input, O(n) otherwise

## Solution

**Algorithm:**
1. **Preprocessing:** Convert the array to prefix sums for O(1) range sum queries
2. **Iterate through partitions:** For each valid partition index i (0 to n-2):
   - Calculate left_sum = prefix[i] 
   - Calculate right_sum = total_sum - left_sum
   - Check if (left_sum - right_sum) is even
3. **Count valid partitions:** Increment counter for each valid partition

**Example Walkthrough (nums = [10,10,3,7,6]):**
- Original: [10,10,3,7,6]
- Prefix sums: [10,20,23,30,36]
- Total sum: 36

Partitions:
1. i=0: left=10, right=36-10=26, diff=10-26=-16 (even) ✓
2. i=1: left=20, right=36-20=16, diff=20-16=4 (even) ✓  
3. i=2: left=23, right=36-23=13, diff=23-13=10 (even) ✓
4. i=3: left=30, right=36-30=6, diff=30-6=24 (even) ✓

Result: 4 valid partitions

**Time Complexity:** O(n) - single pass for prefix sum + single pass for counting
**Space Complexity:** O(1) - modifying input array in-place

# Tags

Array, Prefix Sum, Math, Parity

