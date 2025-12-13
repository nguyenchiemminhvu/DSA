## Problem

https://leetcode.com/problems/subsets-ii/description/

```
Given an integer array nums that may contain duplicates, return all possible 
subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.

Example 1:
Input: nums = [1,2,2]
Output: [[],[1],[1,2],[1,2,2],[2],[2,2]]

Example 2:
Input: nums = [0]
Output: [[],[0]]

Constraints:
- 1 <= nums.length <= 10
- -10 <= nums[i] <= 10
```

## Observations

1. **Power Set Generation**: For an array of length `n`, there are $2^n$ possible subsets (including the empty set).

2. **Duplicate Handling**: Since the input array may contain duplicates, we need to avoid generating duplicate subsets. For example, if `nums = [1,2,2]`, we should not generate `[1,2]` twice.

3. **Sorting is Key**: By sorting the array first, duplicate elements will be adjacent, making it easier to handle duplicates consistently.

4. **Bit Manipulation Approach**: We can represent each subset using a bitmask where bit `i` indicates whether to include `nums[i]` in the subset.

5. **Set for Deduplication**: Converting subsets to tuples and storing them in a set automatically eliminates duplicates.

## Solution

1. **Calculate total subsets**: `nn = 1 << n` computes $2^n$, the total number of possible subsets.

2. **Sort the array**: `nums.sort()` ensures that duplicate elements are adjacent, so identical subsets will have the same representation.

3. **Generate all subsets using bitmasks**:
   - For each number from `0` to `2^n - 1`, we use it as a bitmask
   - Each bit position `i` represents whether to include `nums[i]`
   - If bit `i` is set (1), we include `nums[i]` in the current subset

4. **Use set to eliminate duplicates**: 
   - Convert each subset to a tuple (since lists aren't hashable)
   - Add to set, which automatically handles deduplication
   - For `nums = [1,2,2]`, both mask `110` (binary) and another mask might generate `[1,2]`, but the set keeps only one

5. **Convert back to lists**: Return the final result as a list of lists.

**Example walkthrough** with `nums = [1,2,2]`:
- After sorting: `[1,2,2]`
- mask = 0 (binary: 000) → `[]`
- mask = 1 (binary: 001) → `[1]`
- mask = 2 (binary: 010) → `[2]`
- mask = 3 (binary: 011) → `[1,2]`
- mask = 4 (binary: 100) → `[2]` (duplicate, removed by set)
- mask = 5 (binary: 101) → `[1,2]` (duplicate, removed by set)
- mask = 6 (binary: 110) → `[2,2]`
- mask = 7 (binary: 111) → `[1,2,2]`

**Complexity:**
- **Time**: $O(n \cdot 2^n)$ - We generate $2^n$ subsets, each taking $O(n)$ time to build
- **Space**: $O(n \cdot 2^n)$ - Storing all subsets plus the set overhead

# Tags

`Backtracking` `Bit Manipulation` `Array` `Subsets`

