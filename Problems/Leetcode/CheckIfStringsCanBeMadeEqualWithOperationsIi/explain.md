## Problem

https://leetcode.com/problems/check-if-strings-can-be-made-equal-with-operations-ii/description/

Given two strings `s1` and `s2` of equal length `n`, consisting of lowercase English letters.

You can perform the following operation on any string any number of times:
- Choose indices `i` and `j` such that `i < j` and `(j - i)` is even
- Swap the characters at positions `i` and `j`

**Return:** `true` if you can make `s1` equal to `s2`, `false` otherwise.

**Example 1:**
- Input: `s1 = "abcdba"`, `s2 = "cabdab"`
- Output: `true`
- Explanation: 
  - Swap indices 0, 2: `"abcdba"` → `"cbadba"`
  - Swap indices 2, 4: `"cbadba"` → `"cbbdaa"`
  - Swap indices 1, 5: `"cbbdaa"` → `"cabdab"` = `s2`

**Example 2:**
- Input: `s1 = "abe"`, `s2 = "bea"`
- Output: `false`

**Constraints:**
- `1 <= n <= 10^5`
- `s1` and `s2` consist only of lowercase English letters

## Observations

1. **Index Parity Principle:** The constraint `j - i` is even means indices `i` and `j` have the same parity (both even or both odd).

2. **Partition into Disconnected Groups:** 
   - Characters at even indices (0, 2, 4, ...) can only be swapped among themselves
   - Characters at odd indices (1, 3, 5, ...) can only be swapped among themselves
   - No operation can move a character from an even index to an odd index, or vice versa

3. **Complete Reachability Within Groups:** Within the same parity group, any permutation is achievable through a series of swaps. This is because:
   - We can use bubble-sort-like operations to achieve any permutation
   - For example, to move a character from index 0 to index 4: swap(0,2) → swap(2,4)
   - Any permutation of even indices can be achieved, and same for odd indices

4. **Sufficient Condition:** Two strings can be made equal if and only if:
   - The sorted characters at even indices of `s1` match those at even indices of `s2`
   - The sorted characters at odd indices of `s1` match those at odd indices of `s2`## Solution

**Approach:** Compare sorted subsequences of same-parity indices

**Algorithm:**
1. Extract characters at even indices (0, 2, 4, ...) from both strings → `sub1` and `sub3`
2. Extract characters at odd indices (1, 3, 5, ...) from both strings → `sub2` and `sub4`
3. Sort all four subsequences
4. Check if `sub1 == sub3` and `sub2 == sub4`
   - If both conditions are true, we can rearrange `s1` to match `s2`
   - Otherwise, it's impossible

**Why it works:**
- Sorting the subsequences removes the need to explicitly check all permutations
- If sorted subsequences match, it means both strings have the exact same characters at even positions and odd positions
- Since any permutation within each parity group is achievable, we can rearrange `s1` to match `s2`

**Complexity Analysis:**
- **Time:** $O(n \log n)$ - dominated by sorting two subsequences each of size $\approx n/2$
- **Space:** $O(n)$ - storing four subsequences

**Implementation Notes:**
- List comprehension with `range(0, n, 2)` and `range(1, n, 2)` efficiently extracts even/odd indexed characters
- Sorting is crucial to normalize both strings' characters at each parity level
- Direct equality comparison works because sorted lists compare element-by-element# Tags

- String Manipulation
- Sorting
- Parity Analysis
- Index Partitioning
- Graph Connectivity (underlying concept: permutation reachability)
- Difficulty: Medium
