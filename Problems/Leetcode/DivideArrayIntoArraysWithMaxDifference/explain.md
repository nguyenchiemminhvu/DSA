## Problem

https://leetcode.com/problems/divide-array-into-arrays-with-max-difference/description/

```
You are given an integer array nums of size n where n is a multiple of 3 and a positive integer k.

Divide the array nums into n / 3 arrays of size 3 satisfying the following condition:

The difference between any two elements in one array is less than or equal to k.
Return a 2D array containing the arrays. If it is impossible to satisfy the conditions, return an empty array. And if there are multiple answers, return any of them.

Example 1:

Input: nums = [1,3,4,8,7,9,3,5,1], k = 2

Output: [[1,1,3],[3,4,5],[7,8,9]]

Explanation:

The difference between any two elements in each array is less than or equal to 2.

Example 2:

Input: nums = [2,4,2,2,5,2], k = 2

Output: []

Explanation:

Different ways to divide nums into 2 arrays of size 3 are:

[[2,2,2],[2,4,5]] (and its permutations)
[[2,2,4],[2,2,5]] (and its permutations)
Because there are four 2s there will be an array with the elements 2 and 5 no matter how we divide it. since 5 - 2 = 3 > k, the condition is not satisfied and so there is no valid division.

Example 3:

Input: nums = [4,2,9,8,2,12,7,12,10,5,8,5,5,7,9,2,5,11], k = 14

Output: [[2,2,2],[4,5,5],[5,5,7],[7,8,8],[9,9,10],[11,12,12]]

Explanation:

The difference between any two elements in each array is less than or equal to 14.

Constraints:

n == nums.length
1 <= n <= 105
n is a multiple of 3
1 <= nums[i] <= 105
1 <= k <= 105
```

## Observations

1. **Problem Requirements:**
   - Divide array into groups of exactly 3 elements
   - Maximum difference between any two elements in a group must be ≤ k
   - If impossible, return empty array

2. **Key Insights:**
   - Sorting is crucial: if we can't form valid groups with sorted elements, we definitely can't with unsorted ones
   - In a sorted group of 3 elements [a, b, c], we only need to check if `c - a ≤ k` (since `c - b ≤ c - a` and `b - a ≤ c - a`)
   - Greedy approach works: take elements in sorted order, group them in sets of 3

3. **Why Sorting Works:**
   - After sorting, consecutive elements have minimal differences
   - If we can't form a valid group with 3 consecutive sorted elements, we can't form it with any other combination
   - The maximum difference in a group of 3 sorted elements is always between the first and last element

4. **Edge Cases:**
   - Array length not multiple of 3 (guaranteed by constraints)
   - All elements same (difference = 0 ≤ k, always valid)
   - Large differences that exceed k

## Solution

1. **Sort the array** - This ensures that when we group consecutive elements, we minimize the maximum difference within each group.

2. **Iterate through groups of 3** - Use `range(0, len(nums), 3)` to process every 3 elements.

3. **Check validity** - For each group of 3 elements `[nums[i], nums[i+1], nums[i+2]]`, only check if `nums[i+2] - nums[i] > k`. Since the array is sorted:
   - `nums[i] ≤ nums[i+1] ≤ nums[i+2]`
   - The maximum difference is always between first and last element
   - If this check passes, all pairwise differences are ≤ k

4. **Early termination** - If any group fails the condition, return empty array immediately (impossible case).

5. **Build result** - If all groups are valid, return the list of groups.

**Time Complexity:** O(n log n) - dominated by sorting
**Space Complexity:** O(1) - excluding output array, only constant extra space used

**Why This Greedy Approach Works:**
- After sorting, the optimal strategy is to group consecutive elements
- Any other grouping would result in larger maximum differences
- If consecutive sorted elements can't form a valid group, no other arrangement can

## Tags

`Array` `Sorting` `Greedy` `Math`

