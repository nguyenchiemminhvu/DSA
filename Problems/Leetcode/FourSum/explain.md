## Problem

https://leetcode.com/problems/4sum/

```
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:

0 <= a, b, c, d < n
a, b, c, and d are distinct.
nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.

Example 1:

Input: nums = [1,0,-1,0,-2,2], target = 0
Output: [[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

Example 2:

Input: nums = [2,2,2,2,2], target = 8
Output: [[2,2,2,2]]

Constraints:

1 <= nums.length <= 200
-109 <= nums[i] <= 109
-109 <= target <= 109
```

## Observations

We need to find all unique quadruplets in the array that sum up to the `target`.

The quadruplets must have distinct indices.

The array can contain duplicates, but the result should not have duplicate quadruplets.

The problem is similar to `2Sum` and `3Sum`, but with four numbers.

## Solution

- Sort the Array: Sorting helps to easily skip duplicates and use the two-pointer technique.
- Fix the First Two Numbers: Use two nested loops to pick the first `(i)` and second `(j)` numbers.
  - Skip duplicate values for both `i` and `j` to avoid repeated quadruplets.
- Two-Pointer Search for Remaining Two Numbers:
  - For each pair (i, j), use two pointers (left and right) to find pairs that sum to the remaining value (target - nums[i] - nums[j]).
  - If the sum matches, add the quadruplet to the result set.
  - Move pointers and skip duplicates to ensure uniqueness.
- **Return Results**: Convert the set of tuples to a list of lists for the final answer.

## Tags

array, hash table, two pointers