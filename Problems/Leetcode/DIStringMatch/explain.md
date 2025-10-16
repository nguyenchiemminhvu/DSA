## Problem

https://leetcode.com/problems/di-string-match/description/

```
A permutation perm of n + 1 integers of all the integers in the range [0, n] can be represented as a string s of length n where:

s[i] == 'I' if perm[i] < perm[i + 1], and
s[i] == 'D' if perm[i] > perm[i + 1].
Given a string s, reconstruct the permutation perm and return it. If there are multiple valid permutations perm, return any of them.

Example 1:

Input: s = "IDID"
Output: [0,4,1,3,2]

Example 2:

Input: s = "III"
Output: [0,1,2,3]

Example 3:

Input: s = "DDI"
Output: [3,2,0,1]

Constraints:

1 <= s.length <= 105
s[i] is either 'I' or 'D'.
```

## Observations

1. **Problem Understanding**: We need to construct a permutation of numbers `[0, 1, 2, ..., n]` where `n = len(s)`, such that:
   - If `s[i] == 'I'`, then `perm[i] < perm[i+1]` (increasing)
   - If `s[i] == 'D'`, then `perm[i] > perm[i+1]` (decreasing)

2. **Key Insight**: We can use a greedy approach with two pointers:
   - For 'I' (increase): use the smallest available number
   - For 'D' (decrease): use the largest available number
   - This ensures we always have flexibility for future constraints

3. **Why this works**:
   - When we see 'I', we want the next number to be larger, so we use the smallest available number now
   - When we see 'D', we want the next number to be smaller, so we use the largest available number now
   - This greedy choice always leaves us with the maximum range of options for subsequent decisions

4. **Examples walkthrough**:
   - `s = "IDID"` → `[0,4,1,3,2]`
     - 'I': use 0 (smallest), next must be larger
     - 'D': use 4 (largest), next must be smaller  
     - 'I': use 1 (smallest remaining), next must be larger
     - 'D': use 3 (largest remaining), next must be smaller
     - Final: use 2 (only remaining)

## Solution

The solution uses a **greedy two-pointer approach**:

1. **Initialize**: Create array `nums = [0, 1, 2, ..., n]` and two pointers `left=0`, `right=n`

2. **Process each character**:
   - If `s[i] == 'I'`: append `nums[left]` and increment `left`
   - If `s[i] == 'D'`: append `nums[right]` and decrement `right`

3. **Final step**: After processing all characters, append the remaining number (`nums[left]` or `nums[right]`, they're equal at this point)

**Time Complexity**: O(n) where n is the length of string s
**Space Complexity**: O(n) for the result array and the nums array

**Why it works**: The greedy strategy ensures that at each step, we make the optimal local choice that preserves the maximum flexibility for future constraints. By always using extremes (smallest for 'I', largest for 'D'), we guarantee that the remaining numbers can satisfy any subsequent pattern.

## Tags

array, string, greedy