## Problem

https://leetcode.com/problems/largest-positive-integer-that-exists-with-its-negative/description/

```
Given an integer array nums that does not contain any zeros, find the largest positive integer k such that -k also exists in the array.

Return the positive integer k. If there is no such integer, return -1.

Example 1:

Input: nums = [-1,2,-3,3]
Output: 3
Explanation: 3 is the only valid k we can find in the array.

Example 2:

Input: nums = [-1,10,6,7,-7,1]
Output: 7
Explanation: Both 1 and 7 have their corresponding negative values in the array. 7 has a larger value.

Example 3:

Input: nums = [-10,8,6,7,-2,-3]
Output: -1
Explanation: There is no a single valid k, we return -1.

Constraints:

1 <= nums.length <= 1000
-1000 <= nums[i] <= 1000
nums[i] != 0
```

## Observations

1. **Problem Goal**: Find the largest positive integer `k` such that both `k` and `-k` exist in the array.

2. **Key Insights**:
   - We need to find pairs of numbers where one is the negative of the other
   - Among all such pairs, we want the one with the largest positive value
   - If no such pair exists, return -1

3. **Approach Analysis**:
   - Sort the array to process negative numbers first (they come before positive numbers after sorting)
   - Use a set for O(1) lookup to check if the complement exists
   - Iterate through negative numbers and check if their positive counterpart exists
   - Since we process from most negative to least negative, the first match we find will be the largest positive value

4. **Why this approach works**:
   - After sorting: `[-7, -3, -1, 1, 2, 6, 7, 10]`
   - We iterate through negative numbers: `-7, -3, -1`
   - For each negative number `val`, we check if `-val` (its positive counterpart) exists
   - The loop breaks when `val >= 0`, ensuring we only check negative numbers
   - Since we iterate from most negative to least negative, when we find a match, it's automatically the largest possible positive value

## Solution

**Time Complexity**: O(n log n) due to sorting
**Space Complexity**: O(n) for the set

**Step-by-step walkthrough** with Example 2: `nums = [-1,10,6,7,-7,1]`

1. Sort: `[-7, -1, 1, 6, 7, 10]`
2. Create set: `{-7, -1, 1, 6, 7, 10}`
3. Check `val = -7`: Is `7` in set? Yes! Return `7`

The algorithm efficiently finds the answer because:
- Sorting ensures we check larger absolute values first among negatives
- The set provides constant-time lookup
- Early termination when we reach non-negative numbers

# Tags

- Array
- Hash Set
- Sorting
- Two Pointers

