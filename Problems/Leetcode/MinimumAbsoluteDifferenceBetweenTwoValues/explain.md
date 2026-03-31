## Problem

https://leetcode.com/problems/minimum-absolute-difference-between-two-values/description/

Given an integer array `nums` consisting only of 0, 1, and 2, a pair of indices `(i, j)` is called valid if `nums[i] == 1` and `nums[j] == 2`.

**Task:** Return the minimum absolute difference between i and j among all valid pairs. If no valid pair exists, return -1.

**Constraints:**
- 1 <= nums.length <= 100
- 0 <= nums[i] <= 2

## Observations

1. We only care about pairs where one element is 1 and the other is 2. All other elements (0s) are irrelevant.

2. To minimize the absolute difference between indices, we want to find a 1 and 2 that are as close as possible to each other.

3. As we scan left-to-right, whenever we encounter a 1 or 2, we should check the most recent occurrence of the other value (2 or 1 respectively). This gives us the closest pair ending at the current position.

4. The key insight: We only need to track the **last seen index** of 1 and 2, not all occurrences, because the closest pair involving the current element will always use the most recently seen complementary element.

5. All valid pairs across the entire array have their minimum difference represented by checking at each step.

## Solution

**Algorithm:**
1. Maintain a dictionary `last_idx` to store the most recent index of each value (1 and 2).
2. Iterate through the array from left to right.
3. When we encounter a `1`:
   - If we've seen a `2` before, calculate the difference between current index and the last seen `2`
   - Update the result if this difference is smaller
   - Update the last seen index of `1`
4. When we encounter a `2`:
   - If we've seen a `1` before, calculate the difference between current index and the last seen `1`
   - Update the result if this difference is smaller
   - Update the last seen index of `2`
5. Return the minimum difference, or -1 if no valid pair was found.

**Why this works:**
- As we move forward in the array, the most recently seen complementary element is always the closest candidate to pair with the current element.
- By tracking both values, we capture all possible minimum differences in a single pass.
- The solution avoids nested loops by leveraging the property that we only need the nearest opposite value.

**Time Complexity:** O(n) - single pass through the array
**Space Complexity:** O(1) - dictionary stores at most 2 keys (for values 1 and 2)

# Tags
Single-pass, Hash Map, Index Tracking

