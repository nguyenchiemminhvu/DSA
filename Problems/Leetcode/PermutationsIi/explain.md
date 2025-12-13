## Problem

https://leetcode.com/problems/permutations-ii/description/

```
Given a collection of numbers, nums, that might contain duplicates, return all possible unique permutations in any order.

Example 1:
Input: nums = [1,1,2]
Output: [[1,1,2], [1,2,1], [2,1,1]]

Example 2:
Input: nums = [1,2,3]
Output: [[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]

Constraints:
- 1 <= nums.length <= 8
- -10 <= nums[i] <= 10
```

## Observations

- This is a permutation problem with duplicates in the input array
- We need to generate all unique permutations, avoiding duplicate permutations
- The key challenge is handling duplicate elements in the input to avoid generating duplicate permutations
- Classic backtracking problem where we need to explore all possible arrangements
- Using a set to store tuples is a simple approach to automatically eliminate duplicate permutations

## Solution

1. **Data Structures:**
   - `s`: A set to store unique permutations as tuples (sets automatically handle duplicates)
   - `tmp`: Current permutation being built
   - `visited`: Boolean array to track which elements have been used in the current permutation

2. **Backtracking Process:**
   - The `generating(idx)` function builds permutations position by position
   - At each position `idx`, we try placing each unused element from `nums`
   - When we've placed `n` elements (idx >= n), we have a complete permutation

3. **Key Steps:**
   - For each position, iterate through all elements in `nums`
   - If an element hasn't been visited in the current path:
     - Mark it as visited
     - Add it to the current permutation
     - Recursively generate the next position
     - Backtrack: remove the element and mark as unvisited
   
4. **Duplicate Handling:**
   - Convert each complete permutation to a tuple and add to set
   - The set automatically eliminates duplicate permutations
   - For example, with [1,1,2], different paths might generate [1,1,2] multiple times, but the set keeps only one

5. **Complexity:**
   - **Time:** O(n! × n) - generating all permutations plus set operations
   - **Space:** O(n! × n) - storing all unique permutations

**Note:** While this solution works correctly, a more optimized approach would be to sort the array first and skip duplicates during the backtracking process itself, avoiding the need for a set. This would reduce both time and space overhead.

# Tags
`backtracking` `permutation` `recursion` `set` `array` `deduplication`

